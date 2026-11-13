#include "CardCertificate.h"

CardCertificate::CardCertificate(const DataPointer& filewalker) : CardBlock(filewalker),
	certificate(start + 5 )
{}

QString CardCertificate::className() const {
	return "CardCertificate";
}

QString CardCertificate::title() const {
	return tr("Card Certificate");
}

void CardCertificate::printOn(Reporter& report) const {
	report.writeBlock(certificate, tr("certificate"));if(size() != 199 ){ report.tagValuePair("should have", 199 ); report.tagValuePair("has", size()); }
}

