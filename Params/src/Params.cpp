#include "Params.hpp"
#include <QtXml>
#include <QFile>
#include <iostream>

Params::Params(const char* file) : name(file) {
	get(file);
}

Params::~Params() {put("exitParams.xml");}

bool Params::get(const QString& path) {
	QDomDocument doc("params");
	QFile file(path);

	ok = true;
	if(!file.open(QFile::ReadOnly)) {
		message = QString("Could not find parameter file " ) + path;
		return ok = false;
	}
	if(!doc.setContent(&file)) {
		file.close();
		message = path + " contains XML syntax error";
		return ok = false;
	}
	file.close();
	QDomElement params = doc.documentElement();
	message = path;
	if(params.tagName() != "world") {
		message += " should have container element of type world";
		return ok = false;
	}
	QDomNode n = params.firstChild();
	while(!n.isNull()) {
		if(size.get(n) && (size.width() < 10 || size.height() < 10)) {
			message += " world size is too small";
			ok = false;
		}
		substanceDescriptors.get(n);
		strainDescriptors.get(n);
		n = n.nextSibling();
	}
#if 0
	for(StrainDescriptor sd : strainDescriptors) {
		std::cout << sd.name.toStdString() << "\n";
		for(unsigned cid : sd.cultures.cids) std::cout << ' ' << cid;
		std::cout << "\n";
	}
#endif
	return ok;
}

bool Params::put(const QString& path) {
	QDomDocument doc("params");
	QDomElement world = doc.createElement("world");
	doc.appendChild(world);
	size.put(doc, world);
	substanceDescriptors.put(doc, world);
	strainDescriptors.put(doc, world);
	QFile file(path);
	if(!file.open(QFile::WriteOnly)) return false;
	QTextStream stream(&file);
	stream.setCodec(QTextCodec::codecForName("utf8"));
	stream << doc.toByteArray();
	file.close();
	return true;
}
