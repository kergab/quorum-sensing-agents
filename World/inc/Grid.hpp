#ifndef Grid_HPP
#define Grid_HPP
#include "Node.hpp"
#include <QSize>
#include <QRect>

class QDataStream;
class QImage;
class Grid {
protected:
	QSize s;
	unsigned sc;
	Node *d;
public:
	Grid(const QSize& s, unsigned sc = 1);
	~Grid();
	QSize size() {return s;}
	inline unsigned substanceCount() {return sc;}
	inline Node* node(int col, int row, unsigned sid = 0) {return d + (row * s.width() + col) * sc + sid;}
	inline Node* node(const QPoint& p, unsigned sid = 0) {return node(p.x(), p.y(), sid);}
	void set(const QRect& rect, const Attribute& a, unsigned sid = 0);
	void set(const Attribute& a, unsigned sid = 0);
	void setB(const QRect& rect, const Attribute& a, unsigned sid = 0);
	void setB(const Attribute& a, unsigned sid = 0);
	void step(unsigned sid);
	void step() {for(unsigned sid = 0; sid < sc; sid++) step(sid);}
	void update(QImage& image, unsigned sid = 0);
protected:
	void link();
//	friend QDataStream& operator<<(QDataStream& s, Grid& g);
//	friend QDataStream& operator>>(QDataStream& s, Grid& g);
};

//QDataStream& operator<<(QDataStream& s, Grid& g);

//QDataStream& operator>>(QDataStream& s, Grid& g);
#endif
