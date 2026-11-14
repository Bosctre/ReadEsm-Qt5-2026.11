#include "SvgDayActivity.h"
#include <QCoreApplication>

namespace {
// Protège un texte traduit pour du SVG. Les textes eux-mêmes sont écrits plus bas sous la forme
// esc(QCoreApplication::translate("SvgDayActivity", "...")) : lupdate ne repère que ces appels littéraux.
QString esc(const QString& s) { return s.toHtmlEscaped(); }
}

void SvgDayActivity::add(int from, int duration, float height,
                         const QString& color, const QString& title)
{
    if (duration <= 0) return;

    const double h = height * 80.0;
    const double x = from * 0.5;          // 1440 min -> 720 px
    const double w = duration * 0.5;
    const double y = 100.0 - h;           // axe vertical dessiné directement (pas de scale négatif)

    // QString::number : toujours un point décimal, quelle que soit la locale
    collected += QString("\t\t<rect x='%1' y='%2' width='%3' height='%4' fill='%5'><title>%6</title></rect>\n")
                     .arg(QString::number(x, 'f', 1))
                     .arg(QString::number(y, 'f', 1))
                     .arg(QString::number(w, 'f', 1))
                     .arg(QString::number(h, 'f', 1))
                     .arg(color)
                     .arg(title.toHtmlEscaped());
}

QString SvgDayActivity::toString() const
{
    QString s;
    s += "<svg xmlns='http://www.w3.org/2000/svg' width='900' height='135'>\n";
    s += "\t<g transform='translate(10,0)'>\n";

    // Activités
    s += collected;

    // Cadre
    s += "\t\t<g style='stroke:black;stroke-width:2;'>\n";
    for (int h = 0; h <= 24; ++h)
        s += QString("\t\t\t<line x1='%1' y1='100' x2='%1' y2='104'/>\n").arg(h * 30);
    s += "\t\t\t<polyline points='0,0 720,0 720,100 0,100 0,0' style='fill:none;'/>\n";
    s += "\t\t</g>\n";

    // Graduations
    s += "\t\t<g style='text-anchor:middle;font-size:16px;'>\n";
    for (int h = 0; h <= 24; ++h)
        s += QString("\t\t\t<text x='%1' y='118'>%2</text>\n").arg(h * 30).arg(h);
    s += "\t\t\t<text x='360' y='132'>" + esc(QCoreApplication::translate("SvgDayActivity", "Time of day (UTC)")) + "</text>\n";
    s += "\t\t</g>\n";

    // Légende
    s += "\t\t<g style='font-size:16px;'>\n";
    s += "\t\t\t<rect x='730' y='6'   width='30' height='16' fill='black'/><text x='765' y='20'>"  + esc(QCoreApplication::translate("SvgDayActivity", "= available"))   + "</text>\n";
    s += "\t\t\t<rect x='730' y='26'  width='30' height='16' fill='green'/><text x='765' y='40'>"  + esc(QCoreApplication::translate("SvgDayActivity", "= driving"))     + "</text>\n";
    s += "\t\t\t<rect x='730' y='46'  width='30' height='16' fill='yellow'/><text x='765' y='60'>" + esc(QCoreApplication::translate("SvgDayActivity", "= working"))     + "</text>\n";
    s += "\t\t\t<rect x='730' y='66'  width='30' height='16' fill='orange'/><text x='765' y='80'>" + esc(QCoreApplication::translate("SvgDayActivity", "= short break")) + "</text>\n";
    s += "\t\t\t<rect x='730' y='86'  width='30' height='16' fill='red'/><text x='765' y='100'>"   + esc(QCoreApplication::translate("SvgDayActivity", "= break/rest"))   + "</text>\n";
    s += "\t\t\t<rect x='730' y='106' width='30' height='16' fill='purple'/><text x='765' y='120'>" + esc(QCoreApplication::translate("SvgDayActivity", "= unknown"))    + "</text>\n";
    s += "\t\t</g>\n";

    s += "\t</g>\n</svg>\n";
    return s;
}
