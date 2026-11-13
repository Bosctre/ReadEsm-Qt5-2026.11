#ifndef CARD_BLOCK_H
#define CARD_BLOCK_H

#include "../TopLevelBlock.h"
#include "../DataPointer.h"
#include <QString>

/// Bloc générique d'une carte conducteur.
/// Sert aussi de repli (cardBlockFactory, "default") pour les tags inconnus.
class CardBlock : public TopLevelBlock {
public:
    CardBlock(const DataPointer& filewalker);
    virtual ~CardBlock() = default;

    /// "CardBlock" ; redéfini par chaque bloc généré
    virtual QString className() const;

    /// En-tête (5 octets : tag 2, type 1, longueur 2) + longueur déclarée
    virtual int size() const;

    /// Tag du bloc (ex. 0x0504 pour CardDriverActivity)
    int tag() const;

    /// Début du contenu, après l'en-tête
    virtual DataPointer payload() const;

    int dataBlockSize() const override;
    QString title() const override;
    void printOn(Reporter& report) const override;
};

#endif // CARD_BLOCK_H