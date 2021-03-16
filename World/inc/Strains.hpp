#ifndef Strains_HPP
#define Strains_HPP
#include <vector>

class Params;
class Strain;
class Diffusion;
struct Strains : public std::vector<Strain*> {
	bool ok;
	Strains(Params& params);
	~Strains();
	void step(Diffusion& diffusion);
};
#endif
