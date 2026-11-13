#include "LargeNumber.h"
#include <cstring>


#ifdef HAVE_CRYPTO

LargeNumber::LargeNumber() {
    mpz_init(t);
}

LargeNumber::~LargeNumber() {
    mpz_clear(t);
}

LargeNumber::LargeNumber(const DataPointer& start, int length) {
    mpz_init(t);
    mpz_import(t, length, 1, 1, 0, 0, start.getData());
}

LargeNumber::LargeNumber(const LargeNumber& o) {
    mpz_init(t);
    mpz_set(t, o.t);
}

LargeNumber& LargeNumber::operator=(const LargeNumber& o) {
    if (this != &o) {
        mpz_set(t, o.t);
    }
    return *this;
}

QString LargeNumber::toString() const {
    char* str = mpz_get_str(nullptr, 10, t);
    QString result(str);
    free(str);
    return result;
}

#else

LargeNumber::LargeNumber(const DataPointer& start, int length) {
    // Constructeur vide pour la version non-crypto
}

LargeNumber::LargeNumber() {
    // Constructeur vide pour la version non-crypto
}

LargeNumber::~LargeNumber() {
    // Destructeur vide pour la version non-crypto
}

LargeNumber::LargeNumber(const LargeNumber& o) {
    // Constructeur de copie vide pour la version non-crypto
}

LargeNumber& LargeNumber::operator=(const LargeNumber& o) {
    // Opérateur d'affectation vide pour la version non-crypto
    return *this;
}

QString LargeNumber::toString() const {
    return "not implemented";
}

#endif

