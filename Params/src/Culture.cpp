#include "Culture.hpp"
#include <QtXml>

void Culture::put(QDomDocument& doc, QDomNode& node) {
	QDomElement e = doc.createElement("culture");
	e.setAttribute("id", name);
	e.setAttribute("count", QString("%1").arg(count));
	circle.r > 0? circle.put(doc, e) : rect.put(doc, e);
	node.appendChild(e);
}

bool Culture::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "culture") return false;
	name = e.attribute("id", "0");
	id = name.toInt();
	count = e.attribute("count", "100").toInt();
	if(!node.hasChildNodes()) return false;
	QDomNode n = node.firstChild();
	circle.get(n);
	rect.get(n);
	return true;
}
