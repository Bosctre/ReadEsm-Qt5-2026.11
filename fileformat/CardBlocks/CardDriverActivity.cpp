#include "CardDriverActivity.h"
#include "../Reporter/Reporter.h"
#include "../PictureGenerators/ActivityDrawing.h"
#include <QDate>
#include <algorithm>

CardDriverActivity::CardDriverActivity(const DataPointer& filewalker)
    : RawCardDriverActivity(filewalker)
{
    const DataPointer ringStart = filewalker + 9;
    const int declared = cyclicData.size();           // longueur annoncée par le bloc
    const int avail    = ringStart.bytesLeft();       // octets réellement présents
    const int ringSize = std::min(declared, avail);

    // Bloc vide, tronqué ou pointeurs hors du tampon : rien à lire
    if (ringSize < 12 || oldestRecord < 0 || oldestRecord >= ringSize
        || newestRecord < 0 || newestRecord >= ringSize)
        return;

    const QByteArray ring(ringStart.getData(), ringSize);
    auto at = [&](int i) { return quint8(ring[i % ringSize]); };   // le tampon boucle

    int pos = oldestRecord;
    int consumed = 0;
    while (consumed < ringSize) {
        if (pos == newestRecord) break;               // jour en cours (non clos) : ignoré

        const int len = (at(pos + 2) << 8) | at(pos + 3);
        if (len < 12 || len > ringSize)               // enregistrement invalide : fin de chaîne
            break;

        // Copie contiguë de l'enregistrement, même s'il chevauche la fin du tampon
        QByteArray rec;
        rec.reserve(len);
        for (int i = 0; i < len; ++i) rec.append(char(at(pos + i)));
        buffers.push_back(rec);
        records.push_back(CardActivityDailyRecord(DataPointer(&buffers.back(), 0, len)));

        pos = (pos + len) % ringSize;
        consumed += len;
    }
}

QString CardDriverActivity::className() const { return "CardDriverActivity"; }

QString CardDriverActivity::title() const { return tr("Driver Activity Data"); }

void CardDriverActivity::printOn(Reporter& report) const {
    report.tagValuePair(tr("oldestRecord"), oldestRecord);
    report.tagValuePair(tr("newestRecord"), newestRecord);

    // Liste des jours : toujours visible (pas de show/hide), un graphique par jour
    report.beginList(tr("cardActivityDailyRecords"), int(records.size()), true, false);
    for (const CardActivityDailyRecord& rec : records)
        report.writeBlock(rec, tr("Activities on %1").arg(rec.activityRecordDate.toString()));
    report.endList();

    // Récapitulatif : un tableau par mois
    std::vector<ActivityDrawing::DayTotals> days;
    for (const CardActivityDailyRecord& rec : records) {
        ActivityDrawing::DayTotals t = rec.totals();
        t.date  = rec.activityRecordDate.toDateTime().date();
        t.label = rec.activityRecordDate.toString();
        days.push_back(t);
    }
    report.tagValuePair(tr("Timesheet"), ActivityDrawing::timesheetHtml(days));
}
