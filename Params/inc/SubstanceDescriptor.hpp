#ifndef SubstanceDescriptor_HPP
#define SubstanceDescriptor_HPP
#include "Domain.hpp"
#include <QString>
#include <vector>

class QDomDocument;
class QDomElement;
class QDomNode;

struct SubstanceDescriptor {
	QString name;
	std::vector<Domain> domains;

	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

struct SubstanceDescriptors : public std::vector<SubstanceDescriptor> {
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};
#endif
