#include "Circle.hpp"
#include <QtXml>

void Circle::put(QDomDocument& doc, QDomNode& node) {
	QDomElement e = doc.createElement("circle");
	e.setAttribute("x", QString("%1").arg(c.x()));
	e.setAttribute("y", QString("%1").arg(c.y()));
	e.setAttribute("r", QString("%1").arg(r));
	node.appendChild(e);
}

bool Circle::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "circle") return false;
	c.rx() = e.attribute("x", "0").toDouble();
	c.ry() = e.attribute("y", "0").toDouble();
	r = e.attribute("r", "0").toDouble();
	return true;
}

