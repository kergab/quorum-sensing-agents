#include "Size.hpp"
#include <QtXml>

void Size::put(QDomDocument& doc, QDomNode& node) {
	QDomElement s = doc.createElement("size");
	s.setAttribute("width", QString("%1").arg(width()));
	s.setAttribute("height", QString("%1").arg(height()));
	node.appendChild(s);
}

bool Size::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "size") return false;
	setWidth(e.attribute("width", "0").toInt());
	setHeight(e.attribute("height", "0").toInt());
	return true;
}

