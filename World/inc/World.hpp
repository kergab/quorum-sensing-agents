#ifndef World_HPP
#define World_HPP
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Params.hpp"
#include "Strains.hpp"
#include "Diffusion.hpp"
#include <QImage>
struct World : public Thread, public Mutex {
	Params params;
	Strains strains;
	Diffusion diffusion;
	QImage image;
	unsigned counter;
	bool ok;
	World(const char* xml = 0);
	void step();
	void run();
	void update(unsigned substance, std::vector<std::vector<unsigned>> bacters);
	Size size() {return params.size;}
};
#endif
