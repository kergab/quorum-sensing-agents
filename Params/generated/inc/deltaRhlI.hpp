#ifndef deltaRhlI_HPP
#define deltaRhlI_HPP
#include "deltaRhlIStrain.hpp"
#include "Bacter.hpp"

struct deltaRhlI : public Bacter {
public:
	deltaRhlI(deltaRhlIStrain* strain);

	deltaRhlIStrain* str() {return (deltaRhlIStrain*) strain;};

};
#endif
