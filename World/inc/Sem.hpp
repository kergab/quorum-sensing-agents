#ifndef Sem_HPP
#define Sem_HPP
class Sem {
protected:
	int sem;
public:
	Sem( int size = 1 );
	~Sem();
	void set( int level, int id = 0 );
	int get( int id = 0 );
	void change( int by, int id = 0 );
	void inc( int id = 0 );
	void dec( int id = 0 );
	void wait( int id = 0 );
};
#endif
