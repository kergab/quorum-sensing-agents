#include "Strain.hpp"
#include "Bacter.hpp"
#include "StrainDescriptor.hpp"
#include "Diffusion.hpp"
#include <QImage>

Strain::~Strain() {for(Bacter* b : *this) delete b;}

void Strain::set(StrainDescriptor& sd) {
	for(unsigned n = 0; n < sd.cultures.id.size(); n++) {
		Stat s;
		unsigned stateCount = 1 << sd.stateSignals.size();
		while(stateCount--) s.countsPerStates.push_back(0);
		s.count = 0;
		s.birth = 0;
		stat.push_back(s);
	}
	for(Culture& c : sd.cultures) {
		for(unsigned n = 0; n < c.count; n++) {
			Bacter *b = bacter();
			b->id = c.id;
			c.circle.r > 0? b->set(c.circle) : b->set(c.rect);
			b->setMass();
			push_back(b);
		}
		stat[c.id].count += c.count;
	}
}

void Strain::update(QImage& image, unsigned id) {
	for(Bacter* b : *this)
		if(b->id == id) image.setPixel(b->toPoint(), QColor((Qt::GlobalColor)Bacter::colors[b->color]).rgba());
}

void Strain::step(Diffusion& diffusion) {
	Strain::iterator next;
	for(Strain::iterator it = begin(); it != end(); it = next) {
		next = it;
		next++;
		switch((*it)->step(diffusion)) {
			case Dead:
				stat[(*it)->id].count--;
				delete *it;
				erase(it);
				break;
			case Divide:
				(*it)->divide();
				Bacter *b = bacter();
				*b = **it;
				stat[b->id].count++;
				stat[b->id].birth++;
				insert(it, b);
				break;
		}
	}
}

void Strain::fillStates() {
	for(Stat& s : stat) for(unsigned& c : s.countsPerStates) c = 0;
	for(Bacter* b : *this) stat[b->id].countsPerStates[b->stateFlags]++;
}
