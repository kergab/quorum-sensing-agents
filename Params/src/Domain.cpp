#include "Domain.hpp"
#include <QtXml>
#include <QString>

void Domain::put(QDomDocument& doc, QDomNode& node) {
	QDomElement p = doc.createElement("domain");
	p.setAttribute("filled", QString(filled? "1" : "0"));
	r.put(doc, p);
	a.put(doc, p);
	node.appendChild(p);
}

bool Domain::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "domain") return false;
	filled = e.attribute("filled", "0").toInt();
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		r.get(n) || a.get(n);
		n = n.nextSibling();
	}
	return true;
}
