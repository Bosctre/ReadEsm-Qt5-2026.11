#ifndef ACTIVITYCHANGEINFO_H
#define ACTIVITYCHANGEINFO_H

#include <QCoreApplication>
#include <QString>
#include "DataType.h"
#include "../DataPointer.h"

/// Changement d'activité sur 2 octets (16 bits) :
/// bit 15 = slot, bit 14 = équipage, bit 13 = carte absente,
/// bits 12-11 = activité (0 repos, 1 disponible, 2 travail, 3 conduite),
/// bits 10-0 = minutes depuis 00:00 UTC.
class ActivityChangeInfo : public DataType {
public:
    ActivityChangeInfo(const DataPointer& start);

    int getSlot() const          { return slot; }
    int getDrivingStatus() const { return drivingStatus; }
    int getCardStatus() const    { return cardStatus; }
    int getActivity() const      { return activity; }
    int getMinutes() const       { return minutes; }

    QString className() const override { return "ActivityChangeInfo"; }
    int size() const override          { return 2; }
    void printOn(Reporter& report) const override;

private:
    quint8  slot;
    quint8  drivingStatus;
    quint8  cardStatus;
    quint8  activity;
    quint16 minutes;
};

#endif // ACTIVITYCHANGEINFO_H