#include "Param.hpp"
#include <QtXml>

void Param::put(QDomDocument& doc, QDomNode& node) {
	QDomElement s = doc.createElement("param");
	s.setAttribute("name", name);
	s.setAttribute("value", value);
	s.setAttribute("type", type);
	node.appendChild(s);
}

bool Param::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "param") return false;
	name = e.attribute("name", "unknown");
	value = e.attribute("value", "0");
	type = e.attribute("type", "type");
	return true;
}

void StateParams::put(QDomDocument& doc, QDomNode& node) {
	QDomElement s = doc.createElement("state");
	s.setAttribute("id", id);
		for (Param& p : *this) p.put(doc, s);
	node.appendChild(s);
}

bool StateParams::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "state") return false;
	id = e.attribute("id", "unknown");
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		Param p;
		if(p.get(n)) push_back(p);
		n = n.nextSibling();
	}
	return true;
}
