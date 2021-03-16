#include "World.hpp"
#include "Strain.hpp"
#include <iostream>

World::World(const char* xml)
 : Thread(),
   Mutex(),
   params(xml),
   strains(params),
   diffusion(params),
   image(params.size, QImage::Format_RGB32),
   counter(0),
   ok(params.ok) {
}

void World::step() {
	diffusion.step();
	strains.step(diffusion);
	counter++;
}

void World::run() {
	while(go) {
		lock();
		step();
		unlock();
	}
}

void World::update(unsigned substance, std::vector<std::vector<unsigned>> cultures) {
	diffusion.update(image, substance);
	for(unsigned s = 0; s < cultures.size(); s++) {
		Strain *strain = strains[s];
		for(unsigned b : cultures[s]) strain->update(image, b);
	}
}