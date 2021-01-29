#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(){
  
	int filho1, filho2, neto1, neto2;

	printf("Início do processo pai PID=%d\n", getpid());
	sleep(14);
	filho1 = fork();
	if(!filho1){
		printf("Filho1 com pid=%d e ppid=%d nasce aos 14 segundos\n", getpid(), getppid());
		sleep(13);
		neto1=fork();
		if(!neto1){
			printf("Neto1 com pid=%d e ppid=%d\n", getpid(), getppid());
			sleep(12);
			printf("Neto1 morre aos 12 anos\n");
			exit(0);
		}
		sleep(17);
		printf("Filho1 morre aos 30 anos\n");
		exit(0);
	}

	sleep(2);
	if(filho1>0){
		filho2=fork();
		if(!filho2){
			printf("Filho2 com pid=%d e ppid=%d nasce aos 16 segundos\n", getpid(), getppid());
			sleep(15);
			neto2=fork();
			if(!neto2){
				printf("Neto2 com pid=%d e ppid=%d\n", getpid(), getppid());
				sleep(18);
				exit(0);
			}
			sleep(15);
			printf("filho2 morre aos 30 anos\n");		
			exit(0);
		}
	}
	sleep(46);
	printf("Pai morre aos 60 anos\n");
	exit(0);
	return 0;
}
