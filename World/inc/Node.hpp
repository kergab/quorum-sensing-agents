#ifndef Node_HPP
#define Node_HPP
#include "Attribute.hpp"
#include <QPointF>

struct Node : public Attribute {
	Node() {left = right = up = down = &value;}
	const Attribute& operator=(const Attribute& a) {
		value = a.value;
		coefficient = a.coefficient;
		multiplier = a.multiplier;
		neumannFlux = a.neumannFlux;
		reserve = a.reserve;
		reserveMultiplier = a.reserveMultiplier;
		reserveWeight = a.reserveWeight;
		flag = a.flag;
		return a;
	}
	inline void step() {
		if(flag & Fixed) saved = value;
		else {
			double av = *left + *right + *up + *down;
			if(reserve != 0) {
				av = ((av + reserve*reserveWeight)/(4 + reserveWeight) - value) * coefficient;
				saved = (value + av) * multiplier + neumannFlux;
				if(reserve > 0) reserve -= av * reserveMultiplier;
			} else {
				saved = (value + coefficient * (av/4 - value)) * multiplier + neumannFlux;
			}
			if(saved < 0) saved = 0;
			if(saved > 1) saved = 1;
		}
	}
	inline void recall() {value = saved;}
	inline QPointF grad() {return QPointF((*right - *left)/2, (*down - *up)/2);}

	double *left, *right, *up, *down;
	double saved;
};
#endif
