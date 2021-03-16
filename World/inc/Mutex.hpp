#ifndef Mutex_HPP
#define Mutex_HPP
class Mutex {
protected:
	int mutex;
	int count;
public:
	Mutex(int n=1);
	~Mutex();
	void lock(int id=0);
	void unlock(int id=0);
};
#endif
