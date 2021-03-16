#ifndef Size_HPP
#define Size_HPP
#include <QSize>

class QDomDocument;
class QDomElement;
class QDomNode;
class Size : public QSize {
public:
	Size(int w = 0, int h = 0) : QSize(w, h) {}
	void put(QDomDocument& doc, QDomNode& node);
	bool get(QDomNode& node);
};

#endif
