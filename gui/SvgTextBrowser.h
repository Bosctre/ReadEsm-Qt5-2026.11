#ifndef SVGTEXTBROWSER_H
#define SVGTEXTBROWSER_H

#include <QTextBrowser>
#include <QTextDocument>
#include <QSvgRenderer>
#include <QImage>
#include <QPainter>
#include <QRegularExpression>
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
        expanded.clear();
        QString out;
        out.reserve(html.size());
        static const QRegularExpression re("<svg\\b.*?</svg>",
            QRegularExpression::DotMatchesEverythingOption);
        int last = 0;
        QRegularExpressionMatchIterator it = re.globalMatch(html);
        while (it.hasNext()) {
            const QRegularExpressionMatch m = it.next();
            out += html.midRef(last, m.capturedStart() - last);
            // saut de ligne : le libellé « Visualization: » reste au-dessus du graphique
            out += QString("<br/><img src=\"svg:%1\" />").arg(svgs.size());
            svgs.append(m.captured().toUtf8());
            last = m.capturedEnd();
        }
        out += html.midRef(last);
        source = out;
        refresh(false);
    }

protected:
    QVariant loadResource(int type, const QUrl& name) override {
        if (type == QTextDocument::ImageResource && name.scheme() == QLatin1String("svg")) {
            bool ok = false;
            const int idx = name.path().toInt(&ok);
            if (ok && idx >= 0 && idx < svgs.size()) {
                QSvgRenderer renderer(svgs[idx]);
                if (renderer.isValid()) {
                    QImage img(renderer.defaultSize(), QImage::Format_RGB32);
                    img.fill(Qt::white);
                    QPainter p(&img);
                    renderer.render(&p);
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

    /// Construit le HTML affiché : blocs repliés supprimés, blocs dépliés montrés.
    QString applyToggles() const {
        static const QRegularExpression open(
            "<ul name=\"toggled(\\d+)\" style=\"display:none\" id=\"toggled\\d+\">");
        QString out;
        out.reserve(source.size());
        int pos = 0;
        while (true) {
            const QRegularExpressionMatch m = open.match(source, pos);
            if (!m.hasMatch()) break;
            out += source.midRef(pos, m.capturedStart() - pos);
            const int id = m.captured(1).toInt();
            if (expanded.contains(id)) {
                out += QStringLiteral("<ul>");
                pos = m.capturedEnd();                 // le contenu est traité à la suite
            } else {
                int depth = 1, i = m.capturedEnd();    // sauter jusqu'au </ul> correspondant
                while (depth > 0 && i < source.size()) {
                    const int o = source.indexOf(QLatin1String("<ul"), i);
                    const int c = source.indexOf(QLatin1String("</ul>"), i);
                    if (c < 0) { i = source.size(); break; }
                    if (o >= 0 && o < c) { ++depth; i = o + 3; }
                    else { --depth; i = c + 5; }
                }
                pos = i;
            }
        }
        out += source.midRef(pos);
        // le texte du lien (« show » ou sa traduction) est remplacé par « hide » traduit
        const QString hide = QCoreApplication::translate("HtmlReporter", "hide").toHtmlEscaped();
        for (int id : expanded) {
            const QRegularExpression link(QString("(id=\"link%1\">)[^<]*(</a>)").arg(id));
            out.replace(link, "\\1" + hide + "\\2");
        }
        return out;
    }

    void refresh(bool keepScroll) {
        const int y = keepScroll ? verticalScrollBar()->value() : 0;
        setHtml(applyToggles());
        if (keepScroll) verticalScrollBar()->setValue(y);
    }

    QString source;
    QSet<int> expanded;
    QVector<QByteArray> svgs;
};

#endif // SVGTEXTBROWSER_H
