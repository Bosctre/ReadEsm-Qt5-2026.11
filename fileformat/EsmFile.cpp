#include "EsmFile.h"
#include "blockFactory.h"
#include "CardBlocks/Identification.h"
#include "CardBlocks/CardDriverActivity.h"
#include "CardBlocks/cardBlockFactory.h"
#include "DataTypes/ConcreteRawData.h"
#include "Reporter/Reporter.h"
#include "loadFile.h"
#include "readTypes.h"
#include <QDebug>

EsmFile::EsmFile(const QString& filename)
    : fileData(loadFile(filename)), errors()
{
    if (fileData.size() == 0) {
        errors = tr("Could not read any data from file '%1'.").arg(filename);
        return;
    }
    DataPointer fileWalker(&fileData, 0, fileData.size());

    // CardPeek .ddd : tag(2) + type(1) + length(2) + data   (type 0 = données, 1 = signature)
    bool isCardPeek = false;
    if (fileWalker.bytesLeft() >= 5) {
        const int byte2 = fileWalker[2];
        isCardPeek = (byte2 == 0x00 || byte2 == 0x01);
    }

    while (fileWalker.bytesLeft() >= 5) {
        const int type   = fileWalker[2];
        const int length = readBigEndianInt2(fileWalker + 3);

        if (!isCardPeek || (type != 0 && type != 1)) {
            // Format ESM standard
            QSharedPointer<TopLevelBlock> p(blockFactory(fileWalker));
            if (!p || p->dataBlockSize() <= 0) break;
            blocks.append(p);
            fileWalker += p->dataBlockSize();
            continue;
        }

        if (5 + length > fileWalker.bytesLeft()) break;

        if (type == 0) {
            // fileWalker pointe sur le tag : le bloc se lit directement dans le fichier
            QSharedPointer<CardBlock> cb = cardBlockFactory(fileWalker);
            if (cb) {
                QSharedPointer<TopLevelBlock> tb = qSharedPointerCast<TopLevelBlock>(cb);
                if (tb) blocks.append(tb);
            }
        }
        // type == 1 : signature, ignorée pour l'instant

        fileWalker += 5 + length;
    }
}

void EsmFile::printOn(Reporter& report) const {
    report.setTitle(suggestFileName());
    for (int j = 0; j < blocks.size(); ++j) {
        report.startBlock(blocks[j]->title());
        blocks[j]->printOn(report);
        report.endBlock();
    }
}

QString EsmFile::suggestTitle() const
{
    QString name, first, last;
    for (int i = 0; i < blocks.size(); ++i) {
        const TopLevelBlock* b = blocks[i].data();
        if (const Identification* id = dynamic_cast<const Identification*>(b)) {
            name = (id->cardHolderName.surname + " "
                    + id->cardHolderName.firstNames).simplified();
        } else if (const CardDriverActivity* act = dynamic_cast<const CardDriverActivity*>(b)) {
            act->dateRange(first, last);
        }
    }
    QString title = name;
    if (!first.isEmpty())
        title += (title.isEmpty() ? "" : " ") + first + " to " + last;
    return title.isEmpty() ? QString("ESM Data") : title;
}

QString EsmFile::suggestFileName() const { return suggestTitle(); }

QString EsmFile::errorLog() const { return errors; }


std::ostream& operator<<(std::ostream& os, const EsmFile& e) {
    if (!e.errorLog().isEmpty())
        os << e.errorLog().toStdString();
    return os;
}
