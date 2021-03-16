#include "Attribute.hpp"
#include <QtXml>
#include <QDataStream>

void Attribute::put(QDomDocument& doc, QDomNode& node) {
	QDomElement r = doc.createElement("attribute");
	r.setAttribute("value", QString("%1").arg(value));
	r.setAttribute("coefficient", QString("%1").arg(coefficient));
	if(multiplier != 1) r.setAttribute("multiplier", QString("%1").arg(multiplier));
	if(neumannFlux != 0) r.setAttribute("neumannFlux", QString("%1").arg(neumannFlux));
	if(reserve != 0) {
		r.setAttribute("reserve", QString("%1").arg(reserve));
		r.setAttribute("reserveMultiplier", QString("%1").arg(reserveMultiplier));
		r.setAttribute("reserveWeight", QString("%1").arg(reserveWeight));
	}
	r.setAttribute("flag", QString("%1").arg(flag));
	node.appendChild(r);
}

bool Attribute::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "attribute") return false;
	value = e.attribute("value", "0").toDouble();
	coefficient = e.attribute("coefficient", "0").toDouble();
	multiplier = e.attribute("multiplier", "1").toDouble();
	neumannFlux = e.attribute("neumannFlux", "0").toDouble();
	reserve = e.attribute("reserve", "0").toDouble();
	reserveMultiplier = e.attribute("reserveMultiplier", "0").toDouble();
	reserveWeight = e.attribute("reserveWeight", "0").toDouble();
	flag = (unsigned)e.attribute("flag", "0").toInt();
	return true;
}

QDataStream& operator<<(QDataStream& s, Attribute& a) {
	return s << a.value << a.coefficient << a.multiplier << a.neumannFlux << a.flag;
}

QDataStream& operator>>(QDataStream& s, Attribute& a) {
	return s >> a.value >> a.coefficient >> a.multiplier >> a.neumannFlux >> a.flag;
}
