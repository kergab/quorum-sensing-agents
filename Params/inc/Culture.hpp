#ifndef Culture_HPP
#define Culture_HPP
#include "Rect.hpp"
#include "Circle.hpp"
#include <vector>
#include <QString>

class QDomDocument;
class QDomNode;
struct Culture {
	unsigned id;
	QString name;
	unsigned count;
	Rect rect;
	Circle circle;
	Culture() : id(0), count(100), rect(0, 0, 30, 30), circle(QPointF(), 0) {}
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};
struct Cultures : public std::vector<Culture>{
	std::vector<unsigned> cids; // List of different culture id-s in the strain
	std::vector<QString> id; // List of different culture id-s in the strain
};
#endif
