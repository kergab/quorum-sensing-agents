#include "World.hpp"
#include<iostream>
#include<unistd.h>
int main() {
	std::cout << "Starting world\n";
	World world("params.xml");
	world.start();
	sleep(5);
	world.stop();
	return 0;
}
