#include "Diffusion.hpp"
#include "Params.hpp"

Diffusion::Diffusion(Params& params) : Grid(params.size, params.substanceDescriptors.size()) {
	for(unsigned n = 0; n < sc; n++) {
		for(Domain& d : params.substanceDescriptors[n].domains) {
			if(d.filled) set(d.r, d.a, n);
			else setB(d.r, d.a, n);
		}
	}
}
