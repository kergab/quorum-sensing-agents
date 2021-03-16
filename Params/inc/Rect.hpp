#ifndef Rect_HPP
#define Rect_HPP
#include <QRect>

class QDomDocument;
class QDomElement;
class QDomNode;

class Rect : public QRect {
public:
	Rect(int x = 0, int y = 0, int w = 0, int h = 0) : QRect(x, y, w, h) {}
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

#endif
