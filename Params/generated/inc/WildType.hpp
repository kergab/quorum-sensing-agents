#ifndef WildType_HPP
#define WildType_HPP
#include "WildTypeStrain.hpp"
#include "Bacter.hpp"

struct WildType : public Bacter {
public:
	WildType(WildTypeStrain* strain);

	WildTypeStrain* str() {return (WildTypeStrain*) strain;};

};
#endif
