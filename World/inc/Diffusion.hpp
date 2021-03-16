#ifndef Diffusion_HPP
#define Diffusion_HPP
#include "Grid.hpp"
#include "SubstanceNames.hpp"

class Params;
class Diffusion : public Grid {
public:
	Diffusion(Params& params);
};
#endif