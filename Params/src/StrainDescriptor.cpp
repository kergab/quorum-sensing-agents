#include "StrainDescriptor.hpp"
#include <QtXml>
#include <iostream>

void StrainDescriptor::put(QDomDocument& doc, QDomNode& node) {
	QDomElement r = doc.createElement("strain");
	r.setAttribute("name", name);
	QDomElement d = doc.createElement("division");
	d.setAttribute("mass", QString("%1").arg(division));
	r.appendChild(d);
	QDomElement e = doc.createElement("state_signals");
	for (QString& signal : stateSignals) {
		QDomElement f = doc.createElement("signal");
		f.setAttribute("name", signal);
		e.appendChild(f);
	}
	r.appendChild(e);
	
	for(Param& param : variables) param.put(doc, r);
	for(StateParams& state : states) state.put(doc, r);
	for(Culture& culture : cultures) culture.put(doc, r);
	node.appendChild(r);
}

void StrainDescriptor::getStateSignals(QDomNode& node) {
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		QString signal;
		QDomElement e = n.toElement();
		if(e.tagName() != "signal") break;
		else {
			signal = e.attribute("name", "unknown");
			stateSignals.push_back(signal);
		}
		n = n.nextSibling();
	}
};

bool StrainDescriptor::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "strain") return false;
	name = e.attribute("name", "unknown");
	QDomNode n = node.firstChild();
	Param p;
	StateParams s;
	Culture c;
	while(!n.isNull()) {
		if(n.nodeName() == "division") {
			QDomElement e = n.toElement();
			division = e.attribute("mass", "0.5").toDouble();
		}
		if(n.nodeName() == "state_signals") {
			getStateSignals(n);
		}
		if(p.get(n)) variables.push_back(p);
		if(s.get(n)) {states.push_back(s); s.clear();}
		if(c.get(n)) {
			cultures.push_back(c);
			if(find(cultures.id.begin(), cultures.id.end(),c.name) == cultures.id.end()) {
				c.id = cultures.id.size();
				cultures.cids.push_back(c.id);
				cultures.id.push_back(c.name);
			}
//			if(find(cids.begin(), cids.end(),c.id) == cids.end()) cids.push_back(c.id);
		}
		n = n.nextSibling();
	}
	return true;
}

void StrainDescriptors::put(QDomDocument& doc, QDomNode& node) {
	QDomElement e = doc.createElement("strains");
	for(StrainDescriptor& s : *this) s.put(doc, e);
	node.appendChild(e);
}

bool StrainDescriptors::get(QDomNode& node) {
	QDomElement e = node.toElement();
	if(e.tagName() != "strains") return false;
	QDomNode n = node.firstChild();
	while(!n.isNull()) {
		StrainDescriptor s;
		if(s.get(n)) push_back(s);
		n = n.nextSibling();
	}
	return true;
}
