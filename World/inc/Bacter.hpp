#ifndef Bacter_HPP
#define Bacter_HPP
#include "Position.hpp"

class Strain;
class Diffusion;
class Node;
enum Condition {Normal, Dead, Divide};
struct Bacter : public Position {
	static unsigned colors[4];
	Strain* strain;
	double mass, bite, loss;
	unsigned id;
	unsigned stateFlags;
	unsigned color; // 0 - 4
	Bacter(Strain* str);
	virtual ~Bacter() {}
	void setMass();
	void divide() {mass /= 2;}
	virtual unsigned step(Diffusion& diffusion __attribute__((unused))) {return 0;}
};
#endif
