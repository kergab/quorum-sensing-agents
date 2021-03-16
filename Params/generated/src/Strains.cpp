#include "Strains.hpp"
#include "Params.hpp"
#include "Strain.hpp"
#include "Diffusion.hpp"
#include "WildTypeStrain.hpp"
#include "deltaRhlIStrain.hpp"

Strains::Strains(Params& params) {
	push_back(new WildTypeStrain);
	push_back(new deltaRhlIStrain);
	if(!(ok = params.ok)) return;
	for(unsigned n = 0; n < size(); n++) {
		at(n)->init(params.strainDescriptors[n]);
		at(n)->set(params.strainDescriptors[n]);
	}
}

Strains::~Strains() {for(Strain* strain : *this) delete strain;}
void Strains::step(Diffusion& diffusion) {for(Strain* strain : *this) strain->step(diffusion);}
