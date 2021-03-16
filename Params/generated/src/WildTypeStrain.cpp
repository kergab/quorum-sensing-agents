#include "WildTypeStrain.hpp"
#include "WildType.hpp"

Bacter* WildTypeStrain::bacter() {return new WildType(this);}

