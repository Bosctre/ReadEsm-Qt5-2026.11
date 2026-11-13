   #ifndef FULLCARDNUMBER_H
   #define FULLCARDNUMBER_H
   #include "RawFullCardNumber.h"

   class FullCardNumber : public RawFullCardNumber {
   public:
       FullCardNumber(const DataPointer& filewalker) : RawFullCardNumber(filewalker) {}

       bool operator==(const FullCardNumber& o) const {
           return cardType == o.cardType
               && cardIssuingMemberState == o.cardIssuingMemberState
               && cardNumber == o.cardNumber;
       }
       bool operator!=(const FullCardNumber& o) const { return !(*this == o); }

       bool isDefaultValue() const {
           if (cardType != 0 || cardIssuingMemberState != 0) return false;
           for (const QChar c : cardNumber)
               if (c != QChar(' ') && c != QChar('\0') && c != QChar('0')) return false;
           return true;
       }
   };
   #endif // FULLCARDNUMBER_H