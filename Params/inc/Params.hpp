#ifndef Params_HPP
#define Params_HPP
#include "Size.hpp"
#include "SubstanceDescriptor.hpp"
#include "StrainDescriptor.hpp"
#include <vector>
struct Params {
	Size size;
	SubstanceDescriptors substanceDescriptors;
	StrainDescriptors strainDescriptors;
	QString name;
	bool ok;
	QString message;
	Params(const char* file = 0);
	~Params();
	bool get(const QString& name);
	bool put(const QString& name);
};
#endif
