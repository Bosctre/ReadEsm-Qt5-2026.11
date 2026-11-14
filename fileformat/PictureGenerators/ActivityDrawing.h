#ifndef ACTIVITYDRAWING_H
#define ACTIVITYDRAWING_H

#include "SvgDayActivity.h"
#include <QCoreApplication>
#include <QString>
#include <QChar>
#include <QDate>
#include <QLocale>
#include <vector>

namespace ActivityDrawing {

// Un repos plus court que ce seuil (en minutes) est dessiné en orange.
const int SHORT_BREAK_MINUTES = 15;

/// Texte traduisible (contexte « ActivityDrawing »), reconnu par lupdate.
inline QString tr(const char* text) { return QCoreApplication::translate("ActivityDrawing", text); }

inline QString hm(int minutes) {
    return QString("%1:%2").arg(minutes / 60).arg(minutes % 60, 2, 10, QChar('0'));
}

/// Nom (traduit), couleur et hauteur d'une activité.
/// cardStatus : 0 = carte insérée ; drv : bit « équipage / saisie manuelle » ; activity : 0 à 3.
inline QString classify(int cardStatus, int drv, int activity, int dur, QString& color, float& height)
{
    const bool cardIn = (cardStatus == 0), flag = (drv != 0);
    if (!cardIn && !flag) { color = "purple"; height = 0.20f; return tr("unknown"); }
    switch (activity) {
    case 0:
        if (dur < SHORT_BREAK_MINUTES) { color = "orange"; height = 0.40f; return tr("short break"); }
        color = "red"; height = 0.30f; return tr("break/rest");
    case 1:  color = "black";  height = 0.15f;   return tr("availability");
    case 2:  color = "yellow"; height = 0.6875f; return tr("work");
    default: color = "green";  height = 1.00f;   return tr("driving");
    }
}

/// « Card inserted, driver slot, single » (traduit)
inline QString slotStatus(int slot, int cardStatus, int drv)
{
    const bool cardIn = (cardStatus == 0), flag = (drv != 0);
    const QString third = cardIn
        ? (flag ? tr("crew") : tr("single"))
        : (flag ? tr("following activity manually entered") : tr("following activity unknown"));
    return (cardIn ? tr("Card inserted") : tr("Card not inserted or withdrawn")) + ", "
         + (slot ? tr("co-driver slot") : tr("driver slot")) + ", " + third;
}

/// « from 0:00 to 4:45 (4:45 h) » (traduit)
inline QString timeRange(int from, int to, int dur)
{
    return tr("from %1 to %2 (%3 h)").arg(hm(from), hm(to), hm(dur));
}

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

        QString color;
        float height;
        const QString name = classify(acts[i].getCardStatus(), acts[i].getDrivingStatus(),
                                      acts[i].getActivity(), dur, color, height);
        const QString title = name + ", " + timeRange(from, to, dur) + ": "
                            + slotStatus(acts[i].getSlot(), acts[i].getCardStatus(), acts[i].getDrivingStatus());

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

/// Un tableau par mois (jours dans l'ordre reçu), ligne "Summary" comprise.
inline QString timesheetHtml(const std::vector<DayTotals>& days)
{
    QString out = "<ul>";
    size_t i = 0;
    while (i < days.size()) {
        const int year = days[i].date.year(), month = days[i].date.month();
        out += "<li>" + tr("Timesheet for %1:").arg(QLocale().monthName(month)).toHtmlEscaped() + "<table>"
               "<tr><th></th><th>" + tr("Driving").toHtmlEscaped() + "</th><th>" + tr("Working").toHtmlEscaped()
               + "</th><th>" + tr("Rest").toHtmlEscaped() + "</th><th>" + tr("Available").toHtmlEscaped() + "</th></tr>";
        int d = 0, w = 0, r = 0, a = 0;
        for (; i < days.size() && days[i].date.year() == year && days[i].date.month() == month; ++i) {
            const DayTotals& t = days[i];
            out += "<tr><td>" + t.label + "</td><td>" + hm(t.driving) + "</td><td>" + hm(t.working)
                 + "</td><td>" + hm(t.rest) + "</td><td>" + hm(t.available) + "</td></tr>";
            d += t.driving; w += t.working; r += t.rest; a += t.available;
        }
        out += "<tr><th>" + tr("Summary").toHtmlEscaped() + "</th><th>" + hm(d) + "</th><th>" + hm(w) + "</th><th>" + hm(r)
             + "</th><th>" + hm(a) + "</th></tr></table></li>";
    }
    return out + "</ul>";
}

} // namespace ActivityDrawing

#endif // ACTIVITYDRAWING_H
