#ifndef ACTIVITYCHANGEDETAIL_H
#define ACTIVITYCHANGEDETAIL_H

#include "DataType.h"
#include "ActivityChangeInfo.h"
#include "../Reporter/Reporter.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <QCoreApplication>
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
        QString color; float height;
        return ActivityDrawing::classify(card, drv, act, duration(), color, height);
    }
    QString timeText() const { return ActivityDrawing::timeRange(from, to, duration()); }
    QString slotText() const { return ActivityDrawing::slotStatus(slot, card, drv); }

    /// Texte de la ligne repliable : « break/rest, from 0:00 to 4:45 (4:45 h): Card inserted, … »
    QString toString() const override {
        return name() + ", " + timeText() + ": " + slotText();
    }
    /// Titre de l'élément de liste : « break/rest for 4:45 h »
    QString title() const {
        return tr("%1 for %2 h").arg(name(), ActivityDrawing::hm(duration()));
    }
    void printOn(Reporter& report) const override {
        report.tagValuePair(tr("activity"), name());
        report.tagValuePair(tr("time"), timeText());
        report.tagValuePair(tr("slot status"), slotText());
        report.tagValuePair(tr("Raw data"),
            QString("s=%1, c=%2, p=%3, a=%4, t=%5").arg(slot).arg(drv).arg(card).arg(act).arg(from));
    }

private:
    // contexte de traduction « ActivityChangeDetail » (reconnu par lupdate)
    static QString tr(const char* text) { return QCoreApplication::translate("ActivityChangeDetail", text); }

    int slot, drv, card, act, from, to;
};

#endif // ACTIVITYCHANGEDETAIL_H
