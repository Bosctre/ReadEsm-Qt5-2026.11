#ifndef LARGENUMBER_H
#define LARGENUMBER_H

#include "../config.h"
#include "../DataPointer.h"  // Assurez-vous que le chemin est correct
#include <QtCore/QString>

#ifdef HAVE_CRYPTO
#include <gmp.h>
#endif


class LargeNumber {
public:
    LargeNumber();
    ~LargeNumber();
    LargeNumber(const DataPointer& start, int length);
    LargeNumber(const LargeNumber& o);
    LargeNumber& operator=(const LargeNumber& o);
    QString toString() const;

#ifdef HAVE_CRYPTO
    mpz_t t;
#endif
};


#endif // LARGENUMBER_H
