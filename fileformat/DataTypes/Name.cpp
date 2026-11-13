#include "Name.h"

Name::Name(const DataPointer& filewalker) : DataType(filewalker),
	surname(codepageStringCombination(start + 0 , 36)),
	firstNames(codepageStringCombination(start + 36 , 36))
{}

QString Name::className() const {
	return "Name";
}

int Name::size() const{
	return 72 ;
}

QString Name::toString() const{
	return surname + ", " + firstNames;
}

void Name::printOn(Reporter& report) const {
	report.tagValuePair(tr("surname"), surname);
	report.tagValuePair(tr("firstNames"), firstNames);
}

