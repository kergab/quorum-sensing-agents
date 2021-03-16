#ifndef Position_HPP
#define Position_HPP
#include <QPointF>
#include <ostream>

class QSize;
class QRect;
class Circle;
class Position : public QPointF {
public:
	enum {In, Left, Right, Up, Down};
public:
	Position() {}
	void set(const QRect& limits);
	void set(const QSize& limits);
	void set(const Circle& limits);
	void set(const QPointF& p);
	unsigned step(const QSize& limits, double speed, const QPointF& gradSpeed = QPointF(0,0));
};
std::ostream& operator<<(std::ostream& os, const Position& p);
#endif

