#include "HtmlReporter.h"
#include "../DataTypes/DataType.h"
#include "../config.h"
#include <QCoreApplication>
#include <QStringList>

namespace {

// Les textes visibles (liens show/hide, langue) sont remplacés au moment d'écrire le document.
const char* const HEAD = R"HEAD(<html xmlns="http://www.w3.org/1999/xhtml" dir="ltr" lang="%LANG%">

<head>
	<title>%TITLE%</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf8" />
	<style type="text/css">
		body		{ font-family:sans-serif; }
		table		{ border-collapse:collapse;  border-width:2px; border-style:solid; }
		tr 		{ border-top-width:1px; border-top-style:dashed; }
		tr:hover 	{border-style:outset; background-color:#eeeeee; }
		.center	{text-align:center; }
		th		{text-align:left;vertical-align:top;}
		td,th.max,th.avg, th.min{text-align:left;border-left: 1px dotted;}
		caption		{font-size:0.5em;}
		small		{font-size:0.8em;}
	</style>
	<script type="text/javascript">
		function toggle_visibility(id) {
			var toggledContent = document.getElementById('toggled' + id);
			var link = document.getElementById('link' + id);
			if(toggledContent.style.display != 'none'){
				toggledContent.style.display = 'none';
				link.innerHTML = '%SHOW%';
			} else {
				toggledContent.style.display = 'block';
				link.innerHTML = '%HIDE%';
			}
			return false;
		}
	</script>
</head>
<body>
)HEAD";

inline QString esc(const QString& s) { return s.toHtmlEscaped(); }

// Texte traduit (contexte « HtmlReporter ») ; QCoreApplication::translate est reconnu par lupdate.
inline QString tr(const char* text) { return QCoreApplication::translate("HtmlReporter", text); }

// Même texte, protégé pour être placé entre apostrophes dans du JavaScript
inline QString jsEsc(const QString& s) {
    QString r = s;
    r.replace(QLatin1Char('\\'), QLatin1String("\\\\"));
    r.replace(QLatin1Char('\''), QLatin1String("\\'"));
    return r;
}

// Une valeur qui est déjà du HTML (graphique SVG, tableau...) est écrite telle quelle
inline bool isRawHtml(const QString& v) {
    const QString t = v.trimmed();
    return t.startsWith(QLatin1String("<svg")) || t.startsWith(QLatin1String("<ul>")) || t.startsWith(QLatin1String("<table"));
}

} // namespace

HtmlReporter::HtmlReporter(std::ostream& outStream) : outputStream(outStream) {}

void HtmlReporter::startDocument() {
    linkNumber = blockNumber = nestLevel = 0;
    titleStr.clear(); toc.clear(); collected.clear(); document.clear();
    arrayLevel.clear(); arrayCount.clear(); listOpen.clear();
}

void HtmlReporter::endDocument() {
    // « en-US » est traduit par « fr-FR », « de-DE »... dans les fichiers de traduction
    document  = QString::fromUtf8(HEAD)
                    .replace(QLatin1String("%LANG%"),  esc(tr("en-US")))
                    .replace(QLatin1String("%TITLE%"), esc(titleStr))
                    .replace(QLatin1String("%SHOW%"),  jsEsc(tr("show")))
                    .replace(QLatin1String("%HIDE%"),  jsEsc(tr("hide")));
    document += QString("<h1>%1</h1>\n").arg(esc(titleStr));
    document += QLatin1String("<h3>") + esc(tr("Content")) + QLatin1String("</h3><ul>") + toc + QLatin1String("</ul>\n");
    document += collected;
    const QString link = QStringLiteral("<a href=\"https://github.com/Bosctre/ReadEsm-Qt5-2026.11\" target=\"_blank\">Readesm</a>");
    document += QString("\n<hr />\n%1 <small>(readesm %2 (%3))</small>.\n</body>\n</html>\n")
                    .arg(tr("Report generated with %1").arg(link)).arg(VERSION).arg(VERSION_DATE);
    const QByteArray utf8 = document.toUtf8();
    outputStream.write(utf8.constData(), std::streamsize(utf8.size()));
}

void HtmlReporter::startBlock(const QString& title) {
    ++blockNumber;
    toc       += QString("<li><a href=\"#%1\">%2</a></li>").arg(blockNumber).arg(esc(title));
    collected += QString("\n<h3><a name=\"%1\">%2</a></h3><ul>").arg(blockNumber).arg(esc(title));
}

void HtmlReporter::endBlock() { collected += QLatin1String("</ul>"); }

void HtmlReporter::tagValuePair(const QString& tag, const QString& value) {
    collected += QLatin1String("\n<li>") + esc(tag) + QLatin1String(": ");
    if (isRawHtml(value)) {
        const QString t = value.trimmed();
        if (t.startsWith(QLatin1String("<svg"))) {
            // le graphique reste dans <b>, comme la référence
            collected += QLatin1String("<b>\n") + t + QLatin1String("</b>");
        } else {
            // tableaux récapitulatifs : texte normal, sans gras
            collected += t;
        }
    } else {
        collected += QLatin1String("<b>") + esc(value) + QLatin1String("</b>");
    }
    collected += QLatin1String("</li>");
}

QString HtmlReporter::openToggle(int id, bool expand) const {
    return QString("<ul name=\"toggled%1\" style=\"%2\" id=\"toggled%1\">")
            .arg(id).arg(expand ? "" : "display:none");
}

void HtmlReporter::countItem() {
    if (!arrayLevel.empty() && arrayLevel.back() == nestLevel) ++arrayCount.back();
}

void HtmlReporter::writeBlock(const DataType& block, const QString& title) {
    countItem();
    const QString ts = block.toString();
    collected += QLatin1String("\n<li>");
    if (!title.isEmpty()) collected += esc(title) + QLatin1String(": ");
    if (!ts.isEmpty()) {
        const int id = ++linkNumber;
        collected += title.isEmpty() ? esc(ts) : QLatin1String("<b>") + esc(ts) + QLatin1String("</b>");
        collected += QString(" (<a href=\"#link%1\" name=\"link%1\" onclick=\"return toggle_visibility(%1);\" id=\"link%1\">%2</a>)")
                         .arg(id).arg(esc(tr("show")));
        collected += openToggle(id, false);
    } else {
        collected += QLatin1String("<ul>");
    }
    ++nestLevel;
    block.printOn(*this);
    --nestLevel;
    collected += QLatin1String("</ul></li>");
}

void HtmlReporter::writeArray(const DataType& array, const QString& title, bool expand) {
    countItem();
    const int id    = ++linkNumber;
    const int start = collected.size();
    ++nestLevel;
    arrayLevel.push_back(nestLevel);
    arrayCount.push_back(0);
    array.printOn(*this);
    const int count = arrayCount.back();
    arrayCount.pop_back();
    arrayLevel.pop_back();
    --nestLevel;

    if (count == 0 && collected.size() == start) {      // tableau vide
        collected += QString("<li>%1</li>").arg(esc(tr("No %1.").arg(title)));
        return;
    }
    QString header = QString("\n<li>%1 %2 (<a href=\"#link%3\" name=\"link%3\" onclick=\"return toggle_visibility(%3);\" id=\"link%3\">%4</a>)")
                         .arg(count).arg(esc(title)).arg(id).arg(esc(expand ? tr("hide") : tr("show")));
    header += openToggle(id, expand);
    collected.insert(start, header);
    collected += QLatin1String("</ul></li>");
}

void HtmlReporter::beginList(const QString& title, int count, bool expand, bool collapsible) {
    countItem();
    ++nestLevel;
    if (count == 0) {
        collected += QString("<li>%1</li>").arg(esc(tr("No %1.").arg(title)));
        listOpen.push_back(false);
        return;
    }
    if (collapsible) {
        const int id = ++linkNumber;
        collected += QString("\n<li>%1 %2 (<a href=\"#link%3\" name=\"link%3\" onclick=\"return toggle_visibility(%3);\" id=\"link%3\">%4</a>)")
                         .arg(count).arg(esc(title)).arg(id).arg(esc(expand ? tr("hide") : tr("show")));
        collected += openToggle(id, expand);
    } else {
        // liste toujours visible, sans lien show/hide
        collected += QString("\n<li>%1 %2<ul>").arg(count).arg(esc(title));
    }
    listOpen.push_back(true);
}

void HtmlReporter::endList() {
    if (listOpen.empty()) return;
    if (listOpen.back()) collected += QLatin1String("</ul></li>");
    listOpen.pop_back();
    --nestLevel;
}
