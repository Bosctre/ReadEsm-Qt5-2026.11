#ifndef ACTIVITYDRAWING_H
#define ACTIVITYDRAWING_H

#include "SvgDayActivity.h"
#include <QString>
#include <QChar>
#include <QDate>
#include <QLocale>
#include <vector>

namespace ActivityDrawing {

// Un repos plus court que ce seuil (en minutes) est dessiné en orange.
const int SHORT_BREAK_MINUTES = 15;

template <class Container>
void drawDay(SvgDayActivity& svg, const Container& acts)
{
    const int n = int(acts.size());
    for (int i = 0; i < n; ++i) {
        const int from = acts[i].getMinutes();
        int to = (i + 1 < n) ? acts[i + 1].getMinutes() : 1440;
        if (to > 1440) to = 1440;
        const int dur = to - from;
        if (dur <= 0 || from >= 1440) continue;       // doublon à la même minute

        const bool cardIn  = (acts[i].getCardStatus() == 0);
        const bool flag    = (acts[i].getDrivingStatus() != 0);

        QString color, name;
        float height;
        if (!cardIn && !flag) {                         // carte absente, activité inconnue
            color = "purple"; name = "unknown";      height = 0.20f;
        } else {
            switch (acts[i].getActivity()) {
            case 0:
                if (dur < SHORT_BREAK_MINUTES) { color = "orange"; name = "short break"; height = 0.40f; }
                else                           { color = "red";    name = "break/rest";  height = 0.30f; }
                break;
            case 1: color = "black";  name = "availability"; height = 0.15f;   break;
            case 2: color = "yellow"; name = "work";         height = 0.6875f; break;
            default: color = "green"; name = "driving";      height = 1.00f;   break;
            }
        }

        const QString third = cardIn
            ? QString(flag ? "crew" : "single")
            : QString(flag ? "following activity manually entered" : "following activity unknown");

        const QString title = name
            + QString(", from %1:%2 to %3:%4 (%5:%6 h): ")
                  .arg(from / 60).arg(from % 60, 2, 10, QChar('0'))
                  .arg(to / 60).arg(to % 60, 2, 10, QChar('0'))
                  .arg(dur / 60).arg(dur % 60, 2, 10, QChar('0'))
            + (cardIn ? "Card inserted" : "Card not inserted or withdrawn") + ", "
            + (acts[i].getSlot() ? "co-driver slot" : "driver slot") + ", " + third;

        svg.add(from, dur, height, color, title);
    }
}

// ---------------------------------------------------------------- récapitulatif

/// Totaux d'une journée, en minutes. "Inconnu" (carte absente) n'est compté nulle part ;
/// une pause courte compte comme repos (comme dans la version d'origine).
struct DayTotals {
    QDate   date;
    QString label;          // "sam. mai 24 2025"
    int driving = 0, working = 0, rest = 0, available = 0;
};

template <class Container>
DayTotals totals(const Container& acts)
{
    DayTotals t;
    const int n = int(acts.size());
    for (int i = 0; i < n; ++i) {
        const int from = acts[i].getMinutes();
        int to = (i + 1 < n) ? acts[i + 1].getMinutes() : 1440;
        if (to > 1440) to = 1440;
        const int dur = to - from;
        if (dur <= 0 || from >= 1440) continue;
        const bool cardIn = (acts[i].getCardStatus() == 0);
        const bool flag   = (acts[i].getDrivingStatus() != 0);
        if (!cardIn && !flag) continue;                 // inconnu
        switch (acts[i].getActivity()) {
        case 0:  t.rest      += dur; break;
        case 1:  t.available += dur; break;
        case 2:  t.working   += dur; break;
        default: t.driving   += dur; break;
        }
    }
    return t;
}

inline QString hm(int minutes) {
    return QString("%1:%2").arg(minutes / 60).arg(minutes % 60, 2, 10, QChar('0'));
}

/// Un tableau par mois (jours dans l'ordre reçu), ligne "Summary" comprise.
inline QString timesheetHtml(const std::vector<DayTotals>& days)
{
    QString out = "<ul>";
    size_t i = 0;
    while (i < days.size()) {
        const int year = days[i].date.year(), month = days[i].date.month();
        out += "<li>Timesheet for " + QLocale().monthName(month) + ":<table>"
               "<tr><th></th><th>Driving</th><th>Working</th><th>Rest</th><th>Available</th></tr>";
        int d = 0, w = 0, r = 0, a = 0;
        for (; i < days.size() && days[i].date.year() == year && days[i].date.month() == month; ++i) {
            const DayTotals& t = days[i];
            out += "<tr><td>" + t.label + "</td><td>" + hm(t.driving) + "</td><td>" + hm(t.working)
                 + "</td><td>" + hm(t.rest) + "</td><td>" + hm(t.available) + "</td></tr>";
            d += t.driving; w += t.working; r += t.rest; a += t.available;
        }
        out += "<tr><th>Summary</th><th>" + hm(d) + "</th><th>" + hm(w) + "</th><th>" + hm(r)
             + "</th><th>" + hm(a) + "</th></tr></table></li>";
    }
    return out + "</ul>";
}

} // namespace ActivityDrawing

#endif // ACTIVITYDRAWING_H
