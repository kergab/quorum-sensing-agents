#include "Rect.hpp"
#include <QtXml>

void Rect::put(QDomDocument& doc, QDomNode& node) {
	QDomElement r = doc.createElement("rectangle");
	r.setAttribute("left", QString("%1").arg(left()));
	r.setAttribute("top", QString("%1").arg(top()));
	r.setAttribute("right", QString("%1").arg(right()));
	r.setAttribute("bottom", QString("%1").arg(bottom()));
	node.appendChild(r);
}

bool Rect::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "rectangle") return false;
	setLeft(e.attribute("left", "0").toInt());
	setTop(e.attribute("top", "0").toInt());
	setRight(e.attribute("right", "0").toInt());
	setBottom(e.attribute("bottom", "0").toInt());
	return true;
}

