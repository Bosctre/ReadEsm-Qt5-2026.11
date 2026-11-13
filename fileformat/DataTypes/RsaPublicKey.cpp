#include "RsaPublicKey.h"
#include "../Reporter/Reporter.h"
#include "../config.h"
#ifdef HAVE_CRYPTO
#include <gmp.h>
#endif


RsaPublicKey::RsaPublicKey(const DataPointer& start)
    : RawRsaPublicKey(start)
{}

QString RsaPublicKey::className() const { return "RsaPublicKey"; }
int RsaPublicKey::size() const { return 136; }

void RsaPublicKey::printOn(Reporter& report) const {
    RawRsaPublicKey::printOn(report);
}

QByteArray RsaPublicKey::perform(const RawData& input) const {
#ifdef HAVE_CRYPTO
    LargeNumber in, out, exp, mod;
    mpz_import(mod.t, 128, 1, 1, 0, 0, n.getData());
    mpz_import(exp.t, 8,   1, 1, 0, 0, e.getData());
    const char* inputData = input.payload().getData();
    mpz_import(in.t, input.size(), 1, 1, 0, 0, inputData);
    mpz_powm(out.t, in.t, exp.t, mod.t);
    QByteArray rv(mpz_sizeinbase(out.t, 256) + 10, 0);
    size_t sz;
    mpz_export(rv.data(), &sz, 1, 1, 0, 0, out.t);
    rv.resize(sz);
    return rv;
#else
    return QByteArray();
#endif
}

