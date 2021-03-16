#ifndef Param_HPP
#define Param_HPP
#include <QString>
#include <vector>

class QDomDocument;
class QDomElement;
class QDomNode;
struct Param {
	QString name, value, type;
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

struct StateParams : public std::vector<Param> {
	QString id;
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

#endif
