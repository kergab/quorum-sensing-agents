#ifndef Attribute_HPP
#define Attribute_HPP
enum Flag : unsigned {Free = 0, Fixed = 1};

class QDomDocument;
class QDomNode;
class QDataStream;
struct Attribute {
	double value, coefficient, multiplier, neumannFlux, reserve, reserveMultiplier, reserveWeight;
	unsigned flag;
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
	friend QDataStream& operator<<(QDataStream& s, Attribute& a);
	friend QDataStream& operator>>(QDataStream& s, Attribute& a);
};

QDataStream& operator<<(QDataStream& s, Attribute& a);

QDataStream& operator>>(QDataStream& s, Attribute& a);
#endif
