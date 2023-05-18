    #include <sys/types.h>
    #include <sys/sem.h>
    #include <sys/ipc.h>
    #include <string.h>
    #include <errno.h>
    #include <unistd.h>
    #include <stdio.h>

    int main (int argc, char **argv)
    {
    int semaphorid; 
    // идентификатор семафора
    key_t key = ftok("/tmp", '1');
    struct sembuf semaphores[2];

    semaphorid = semget(key, 2, IPC_CREAT);

    if (semaphorid == -1)
    {
    printf("Ошибка: \n");
    _exit(1);
    }

    semaphores[0].sem_num = 0;
    semaphores[0].sem_flg = SEM_UNDO;

    semaphores[1].sem_num = 1;
    semaphores[1].sem_flg = SEM_UNDO;

    char str[100];

    semaphores[0].sem_op = 0;
    while(semaphores[0].sem_op == 0){
	    printf("Производитель: ");
	    fgets(str,100,stdin);
	    semaphores[0].sem_op = 1;
	    semaphores[1].sem_op = 0;
	    if (semaphores[1].sem_op == 0){
		    if (str[0] != '\n'){
			    printf("Потребитель: %s", str);
			    semaphores[0].sem_op = 0;
			    }
		    semaphores[1].sem_op = 1;
	    }
    }
    printf("Введена строка нулевой длины.\n");
    semctl(semaphorid,0,IPC_RMID); // IPC_RMID – аргумент, значащий немедленное удаление набора семафоров
    }
