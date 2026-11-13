#ifndef ACTIVITYCHANGEDETAIL_H
#define ACTIVITYCHANGEDETAIL_H

#include "DataType.h"
#include "ActivityChangeInfo.h"
#include "../Reporter/Reporter.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <QObject>
#include <QString>

/// Un changement d'activité avec sa durée, pour la liste détaillée d'un jour.
class ActivityChangeDetail : public DataType {
public:
    ActivityChangeDetail(const DataPointer& p, const ActivityChangeInfo& a, int to)
        : DataType(p),
          slot(a.getSlot()), drv(a.getDrivingStatus()), card(a.getCardStatus()),
          act(a.getActivity()), from(a.getMinutes()),
          to(to > 1440 ? 1440 : to) {}

    QString className() const override { return QStringLiteral("ActivityChangeDetail"); }
    int size() const { return 2; }

    int duration() const { return to > from ? to - from : 0; }

    QString name() const {
        const bool cardIn = (card == 0), flag = (drv != 0);
        if (!cardIn && !flag) return QStringLiteral("unknown");
        switch (act) {
        case 0:  return duration() < ActivityDrawing::SHORT_BREAK_MINUTES
                        ? QStringLiteral("short break") : QStringLiteral("break/rest");
        case 1:  return QStringLiteral("availability");
        case 2:  return QStringLiteral("work");
        default: return QStringLiteral("driving");
        }
    }
    QString timeText() const {
        return QString("from %1 to %2 (%3 h)")
            .arg(ActivityDrawing::hm(from), ActivityDrawing::hm(to), ActivityDrawing::hm(duration()));
    }
    QString slotText() const {
        const bool cardIn = (card == 0), flag = (drv != 0);
        const QString third = cardIn
            ? QString(flag ? "crew" : "single")
            : QString(flag ? "following activity manually entered" : "following activity unknown");
        return QString("%1, %2, %3")
            .arg(cardIn ? "Card inserted" : "Card not inserted or withdrawn",
                 slot ? "co-driver slot" : "driver slot", third);
    }
    /// Texte de la ligne repliable : « break/rest, from 0:00 to 4:45 (4:45 h): Card inserted, … »
    QString toString() const override {
        return QString("%1, %2: %3").arg(name(), timeText(), slotText());
    }
    /// Titre de l'élément de liste : « break/rest for 4:45 h »
    QString title() const {
        return QString("%1 for %2 h").arg(name(), ActivityDrawing::hm(duration()));
    }
    void printOn(Reporter& report) const override {
        report.tagValuePair(QObject::tr("activity"), name());
        report.tagValuePair(QObject::tr("time"), timeText());
        report.tagValuePair(QObject::tr("slot status"), slotText());
        report.tagValuePair(QObject::tr("Raw data"),
            QString("s=%1, c=%2, p=%3, a=%4, t=%5").arg(slot).arg(drv).arg(card).arg(act).arg(from));
    }

private:
    int slot, drv, card, act, from, to;
};

#endif // ACTIVITYCHANGEDETAIL_H