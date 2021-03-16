#include "SubstanceDescriptor.hpp"
#include <QtXml>

void SubstanceDescriptor::put(QDomDocument& doc, QDomNode& node) {
	QDomElement e = doc.createElement("substance");
	e.setAttribute("name", name);
	for(Domain& d : domains) d.put(doc, e);
	node.appendChild(e);
}

bool SubstanceDescriptor::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "substance") return false;
	name = e.attribute("name", "unknown");
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		Domain d;
		if(d.get(n)) domains.push_back(d);
		n = n.nextSibling();
	}
	return true;
}

void SubstanceDescriptors::put(QDomDocument& doc, QDomNode& node) {
	QDomElement e = doc.createElement("substances");
	for(SubstanceDescriptor& s : *this) s.put(doc, e);
	node.appendChild(e);
}

bool SubstanceDescriptors::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "substances") return false;
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		SubstanceDescriptor s;
		if(s.get(n)) push_back(s);
		n = n.nextSibling();
	}
	return true;
}
