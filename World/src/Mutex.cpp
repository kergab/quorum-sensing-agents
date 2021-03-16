#include "Mutex.hpp"
#include <sys/sem.h>

Mutex::Mutex(int n) {
	mutex = semget(IPC_PRIVATE, count = n, IPC_CREAT | 0666);
	for(int i=0; i<n; i++) semctl(mutex, i, SETVAL, 1);
}

Mutex::~Mutex() {semctl(mutex, 0, IPC_RMID, 0);}

void Mutex::lock(int id) {
	struct sembuf op;
	op.sem_flg = 0;
	op.sem_num = id;
	op.sem_op = -1;
	semop(mutex, &op, 1);
}

void Mutex::unlock(int id) {
	struct sembuf op;
	op.sem_flg = 0;
	op.sem_num = id;
	op.sem_op = 1;
	semop(mutex, &op, 1);
}
