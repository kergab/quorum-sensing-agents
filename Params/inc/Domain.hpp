#ifndef Domain_HPP
#define Domain_HPP
#include "Rect.hpp"
#include "Attribute.hpp"

struct Domain {
	bool filled;
	Rect r;
	Attribute a;

	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};
#endif
