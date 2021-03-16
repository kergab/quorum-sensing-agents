#ifndef StrainDescriptor_HPP
#define StrainDescriptor_HPP
#include "Param.hpp"
#include "Culture.hpp"
#include <QString>
#include <vector>

class QDomDocument;
class QDomElement;
class QDomNode;

struct StrainDescriptor {
	QString name;
	double division;
	std::vector<QString> stateSignals;
	std::vector<Param> variables;
	std::vector<StateParams> states;
	Cultures cultures;

	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
	void getStateSignals(QDomNode& node);
};

struct StrainDescriptors : public std::vector<StrainDescriptor> {
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

#endif
