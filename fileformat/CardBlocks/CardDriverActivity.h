#ifndef CARDDRIVERACTIVITY_H
#define CARDDRIVERACTIVITY_H

#include <QCoreApplication>
#include <QByteArray>
#include <deque>
#include <vector>
#include "RawCardDriverActivity.h"
#include "../DataTypes/CardActivityDailyRecord.h"

class CardDriverActivity : public RawCardDriverActivity {
    Q_DECLARE_TR_FUNCTIONS(CardDriverActivity)
public:
    CardDriverActivity(const DataPointer& filewalker);
    // Non copiable : les enregistrements pointent vers 'buffers'
    CardDriverActivity(const CardDriverActivity&) = delete;
    CardDriverActivity& operator=(const CardDriverActivity&) = delete;

    QString className() const override;
    QString title() const override;
    void printOn(Reporter& report) const override;

    /// Premier et dernier jour lus (pour le titre du document)
    bool dateRange(QString& first, QString& last) const {
        if (records.empty()) return false;
        first = records.front().activityRecordDate.toString();
        last  = records.back().activityRecordDate.toString();
        return true;
    }

    static const int Type = 0x0504;

private:
    std::deque<QByteArray> buffers;                  // copies contiguës, adresses stables
    std::vector<CardActivityDailyRecord> records;
};

#endif // CARDDRIVERACTIVITY_H
