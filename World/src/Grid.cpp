#include "Grid.hpp"
#include <QImage>
#include <QColor>
#include <QDataStream>

Grid::Grid(const QSize& siz, unsigned scount) : s(siz), sc(scount), d(new Node[s.width() * s.height() * sc]) {link();}

Grid::~Grid() {delete[] d;}

void Grid::update(QImage& image, unsigned sid) {
	QColor color;
	if(sid < sc) {
		for(int row = 0; row < s.height(); row++) {
			for(int col = 0; col < s.width(); col++) {
				double h = 0.5 * node(col, row, sid)->value;
				if(h > 1) h = 1;
				color.setHsvF(h, 1, 1);
				image.setPixel(col, row, color.rgba());
			}
		}
	} else {
		image.fill(Qt::darkGreen);
	}
}

void Grid::link() {
	for(int row = 0; row < s.height(); row++) {
		for(int col = 0; col < s.width(); col++) {
			for(unsigned sid = 0; sid < sc; sid++) {
				Node* n = node(col, row, sid);
				if(row > 0) n->up = &node(col, row - 1, sid)->value;
				if(row + 1 < s.height()) n->down = &node(col, row + 1, sid)->value;
				if(col > 0) n->left = &node(col - 1, row, sid)->value;
				if(col + 1 < s.width()) n->right = &node(col + 1, row, sid)->value;
			}
		}
	}
}

void Grid::set(const QRect& rect, const Attribute& a, unsigned sid) {
	QRect r = rect.intersected(QRect(QPoint(0, 0), s));
	for(int x = r.left(); x <= r.right(); x++)
		for(int y = r.top(); y <= r.bottom(); y++)
			*node(x, y, sid) = a;
}

void Grid::set(const Attribute& a, unsigned sid) {set(QRect(QPoint(0, 0), s), a, sid);}

void Grid::setB(const QRect& rect, const Attribute& a, unsigned sid) {
	QRect r = rect.intersected(QRect(QPoint(0, 0), s));
	if(r.isEmpty()) return;
	for(int x = r.left(); x <= r.right(); x++)
		*node(x, r.top(), sid) = *node(x, r.bottom(), sid) = a;
	for(int y = r.top(); y <= r.bottom(); y++)
		*node(r.left(), y, sid) = *node(r.right(), y, sid) = a;
}

void Grid::setB(const Attribute& a, unsigned sid) {setB(QRect(QPoint(0, 0), s), a, sid);}

void Grid::step(unsigned sid) {
	for(int row = 0; row < s.height(); row++)
		for(int col = 0; col < s.width(); col++)
			node(col, row, sid)->step();
	for(int row = 0; row < s.height(); row++)
		for(int col = 0; col < s.width(); col++)
			node(col, row, sid)->recall();
}

#if 0
QDataStream& operator<<(QDataStream& s, Grid& g) {
	s << g.s;
	Node* p = g.d;
	for(int n = 0; n < g.s.width() * g.s.height(); n++, p++) s << p->v << p->c << p->m << p->f;
	return s;
}

QDataStream& operator>>(QDataStream& s, Grid& g) {
	s >> g.s;
	delete[] g.d;
	g.d = new Node[g.s.width() * g.s.height()];
	Node* p = g.d;
	for(int n = 0; n < g.s.width() * g.s.height(); n++, p++) s >> p->v >> p->c >> p->m >> p->f;
	g.link();
	return s;
}
#endif
