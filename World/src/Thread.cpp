#include "Thread.hpp"
#include <pthread.h>
#include <iostream>
using namespace std;

Thread::Thread() : Sem() {go = false;}

Thread::~Thread() {}

bool Thread::start() {
	if(!init()) return false;
	pthread_t id;
	go = true;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_create(&id, 0, Thread::thread, this);
	return true;
}

void Thread::stop() {
	if( !go ) return;
	inc();
	go = false;
	wait();
	cleanup();
}

bool Thread::init() {return true;}

void Thread::cleanup() {}

void Thread::run() {}

void *Thread::thread( void *o ) {
	((Thread*)o)->run();
	((Thread*)o)->dec();
	return 0;
}

