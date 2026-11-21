#ifndef SVGTEXTBROWSER_H
#define SVGTEXTBROWSER_H

#include <QTextBrowser>
#include <QTextDocument>
#include <QSvgRenderer>
#include <QImage>
#include <QPainter>
#include <QRegularExpression>
#include <QStringView>
#include <QByteArray>
#include <QVector>
#include <QSet>
#include <QUrl>
#include <QScrollBar>
#include <QCoreApplication>

/// QTextBrowser n'exécute pas le JavaScript du rapport et ne gère pas les <svg> en ligne.
/// Cette classe :
///  - remplace chaque <svg>...</svg> par <img src="svg:N"> dessiné par QtSvg ;
///  - gère elle-même les liens « show / hide » : les blocs <ul style="display:none"> sont
///    retirés de l'affichage tant qu'on ne clique pas sur leur lien.
class SvgTextBrowser : public QTextBrowser {
public:
    explicit SvgTextBrowser(QWidget* parent = nullptr) : QTextBrowser(parent) {
        setOpenLinks(false);
        connect(this, &QTextBrowser::anchorClicked, this, [this](const QUrl& url) {
            const QString frag = url.fragment();
            if (frag.startsWith(QLatin1String("link"))) {
                bool ok = false;
                const int id = frag.mid(4).toInt(&ok);
                if (ok) toggle(id);
            } else if (!frag.isEmpty()) {
                scrollToAnchor(frag);                    // sommaire « Content »
            }
        });
    }

    void setHtmlWithSvg(const QString& html) {
        svgs.clear();
        images.clear();
        expanded.clear();
        QString out;
        out.reserve(html.size());
        static const QRegularExpression re("<svg\\b.*?</svg>",
            QRegularExpression::DotMatchesEverythingOption);
        int last = 0;
        QRegularExpressionMatchIterator it = re.globalMatch(html);
        while (it.hasNext()) {
            const QRegularExpressionMatch m = it.next();
            out.append(html.constData() + last, m.capturedStart() - last);
            // saut de ligne : le libellé « Visualization: » reste au-dessus du graphique
            out += QString("<br/><img src=\"svg:%1\" />").arg(svgs.size());
            svgs.append(m.captured().toUtf8());
            last = m.capturedEnd();
        }
        out.append(html.constData() + last, html.size() - last);
        source = out;
        indexToggles();
        refresh(false);
    }

protected:
    QVariant loadResource(int type, const QUrl& name) override {
        if (type == QTextDocument::ImageResource && name.scheme() == QLatin1String("svg")) {
            bool ok = false;
            const int idx = name.path().toInt(&ok);
            if (ok && idx >= 0 && idx < svgs.size()) {
                if (idx < images.size() && !images[idx].isNull()) return images[idx];
                QSvgRenderer renderer(svgs[idx]);
                if (renderer.isValid()) {
                    QImage img(renderer.defaultSize(), QImage::Format_RGB32);
                    img.fill(Qt::white);
                    QPainter p(&img);
                    renderer.render(&p);
                    p.end();
                    if (idx >= images.size()) images.resize(svgs.size());
                    images[idx] = img;
                    return img;
                }
            }
        }
        return QTextBrowser::loadResource(type, name);
    }

private:
    void toggle(int id) {
        if (expanded.contains(id)) expanded.remove(id); else expanded.insert(id);
        refresh(true);
    }

    /// Repère une seule fois, à la lecture du rapport, tous les blocs repliés
    /// <ul name="toggledN" style="display:none" ...> ... </ul> (même imbriqués).
    void indexToggles() {
        toggles.clear();
        static const QString openTag = QStringLiteral("<ul name=\"toggled");
        static const QString anyOpen = QStringLiteral("<ul");
        static const QString closeTag = QStringLiteral("</ul>");
        const int n = source.size();
        QVector<int> stack;                 // indices dans toggles des blocs repliés ouverts
        QVector<bool> isToggle;             // pour chaque <ul> ouvert : est-ce un bloc replié ?
        int i = 0;
        while (true) {
            i = source.indexOf(QLatin1Char('<'), i);
            if (i < 0) break;
            if (QStringView(source).mid(i, 5) == QStringView(closeTag)) {
                const int end = i + 5;
                if (!isToggle.isEmpty()) {
                    if (isToggle.last()) { toggles[stack.last()].closeEnd = end; stack.removeLast(); }
                    isToggle.removeLast();
                }
                i = end;
            } else if (QStringView(source).mid(i, 3) == QStringView(anyOpen) &&
                       (i + 3 < n) && (source.at(i + 3) == QLatin1Char(' ') || source.at(i + 3) == QLatin1Char('>'))) {
                const int gt = source.indexOf(QLatin1Char('>'), i);
                if (gt < 0) break;
                bool toggle = false;
                if (QStringView(source).mid(i, openTag.size()) == QStringView(openTag)) {
                    // lecture manuelle de l'identifiant (une expression régulière appliquée
                    // des milliers de fois sur tout le rapport serait très lente)
                    int d = i + openTag.size();
                    int id = 0, digits = 0;
                    while (d < n && source.at(d).isDigit() && digits < 9) {
                        id = id * 10 + source.at(d).digitValue();
                        ++d; ++digits;
                    }
                    if (digits > 0) {
                        const QString expect = QString("<ul name=\"toggled%1\" style=\"display:none\" id=\"toggled%1\">").arg(id);
                        if (QStringView(source).mid(i, expect.size()) == QStringView(expect)) {
                            Toggle t;
                            t.id = id;
                            t.openStart = i;
                            t.openEnd = i + expect.size();
                            t.closeEnd = n;
                            toggles.append(t);
                            stack.append(toggles.size() - 1);
                            toggle = true;
                        }
                    }
                }
                isToggle.append(toggle);
                i = toggle ? toggles.last().openEnd : gt + 1;
            } else {
                ++i;
            }
        }
    }

    /// Construit le HTML affiché : blocs repliés supprimés, blocs dépliés montrés.
    QString applyToggles() const {
        QString out;
        out.reserve(source.size() / 4);
        int pos = 0;
        for (const Toggle& t : toggles) {
            if (t.openStart < pos) continue;              // dans un bloc replié déjà sauté
            out.append(source.constData() + pos, t.openStart - pos);
            if (expanded.contains(t.id)) {
                out += QStringLiteral("<ul>");
                pos = t.openEnd;                          // le contenu est traité à la suite
            } else {
                pos = t.closeEnd;                         // bloc replié : supprimé
            }
        }
        out.append(source.constData() + pos, source.size() - pos);
        // le texte du lien (« show » ou sa traduction) est remplacé par « hide » traduit
        if (!expanded.isEmpty()) {
            const QString hide = QCoreApplication::translate("HtmlReporter", "hide").toHtmlEscaped();
            for (int id : expanded) {
                const QRegularExpression link(QString("(id=\"link%1\">)[^<]*(</a>)").arg(id));
                out.replace(link, "\\1" + hide + "\\2");
            }
        }
        return out;
    }

    void refresh(bool keepScroll) {
        const int y = keepScroll ? verticalScrollBar()->value() : 0;
        setHtml(applyToggles());
        if (keepScroll) verticalScrollBar()->setValue(y);
    }

    struct Toggle { int id = 0; int openStart = 0; int openEnd = 0; int closeEnd = 0; };
    QVector<Toggle> toggles;
    QString source;
    QSet<int> expanded;
    QVector<QByteArray> svgs;
    QVector<QImage> images;
};

#endif // SVGTEXTBROWSER_H
