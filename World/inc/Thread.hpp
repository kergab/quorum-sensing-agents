#ifndef Thread_HPP
#define Thread_HPP
#include "Sem.hpp"
class Thread : public Sem {
protected:
	bool go;
public:
	Thread();
	virtual ~Thread();
	bool start();
	void stop();
	bool isRunning() {return go;}
protected:
	virtual bool init();
	virtual void cleanup();
	virtual void run();
	static void *thread(void *o);
};
#endif
