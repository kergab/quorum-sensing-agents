#include "Bacter.hpp"
#include "Strain.hpp"
#include "Uniform.hpp"
#include "Diffusion.hpp"
#include <QColor>

Bacter::Bacter(Strain* str) : strain(str), id(0), stateFlags(0), color(3) {}
void Bacter::setMass() {
	mass = Uniform::get() * strain->division;
}

unsigned Bacter::colors[] = {Qt::black, Qt::yellow, Qt::white, Qt::blue};

