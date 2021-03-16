#ifndef Circle_HPP
#define Circle_HPP
#include <QPointF>
class QDomDocument;
class QDomElement;
class QDomNode;

class Circle {
public:
	QPointF c;
	double r;
	Circle(QPointF C, double R) : c(C), r(R) {}
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

#endif
