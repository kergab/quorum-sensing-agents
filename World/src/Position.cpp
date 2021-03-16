#include "Position.hpp"
#include "Circle.hpp"
#include "Uniform.hpp"
#include <QSize>
#include <QRect>
#include <cmath>

void Position::set(const QPointF& p) {setX(p.x()); setY(p.y());}

void Position::set(const QRect& limits) {
	setX(Uniform::get()*(limits.right() - limits.left()) + limits.left());
	setY(Uniform::get()*(limits.bottom() - limits.top()) + limits.top());
}

void Position::set(const QSize& limits) {
	setX(Uniform::get()*(limits.width() - 1));
	setY(Uniform::get()*(limits.height() - 1));
}

void Position::set(const Circle& limits) {
	double r = sqrt(Uniform::get()) * limits.r;
	double f = 2. * M_PI * Uniform::get();

	setX(limits.c.x() + r * cos(f));
	setY(limits.c.y() + r * sin(f));
}

unsigned Position::step(const QSize& limits, double speed, const QPointF& gradSpeed) {
	double d = 2 * M_PI * Uniform::get();
	double dx = speed * cos(d) + gradSpeed.x(), nx = x() + dx;
	double dy = speed * sin(d) + gradSpeed.y(), ny = y() + dy;
#if 0
	if(nx < 0 && dx < 0) dx = -dx;
	if(ny < 0 && dy < 0) dy = -dy;
	if(nx + 1 > limits.width() && dx > 0) dx = -dx;
	if(ny + 1 > limits.height() && dy > 0) dy = -dy;
#else
	if(nx < 0) return Left;
	if(ny < 0) return Up;
	if(nx + 1 > limits.width()) return Right;
	if(ny + 1 > limits.height()) return Down;
	//note to self: this is for the bacteria to die at rather than rebounce from the borders
#endif
	setX(x() + dx);
	setY(y() + dy);
	return In;
}

std::ostream& operator<<(std::ostream& os, const Position& p) {
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}

