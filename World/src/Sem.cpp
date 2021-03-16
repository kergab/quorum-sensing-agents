#include "Sem.hpp"
#include <sys/sem.h>

Sem::Sem(int size) {
	sem = semget(IPC_PRIVATE, size, IPC_CREAT | 0666);
	set(0);
}

Sem::~Sem(){semctl(sem, 0, IPC_RMID, 0);}

void Sem::set(int value, int id) {semctl(sem, id, SETVAL, value);}

int Sem::get( int id ) {return semctl(sem, id, GETVAL);}

void Sem::change(int by, int id) {
	struct sembuf op;
	op.sem_flg = 0;
	op.sem_num = id;
	op.sem_op = by;
	semop(sem, &op, 1);
}

void Sem::inc(int id) {change(1, id);}

void Sem::dec(int id) {change(-1, id);}

void Sem::wait(int id) {change(0, id);}
