#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

/*
Para compilar o código use o seguinte comando no terminal: gcc trabalhoPthread.c -o run -lm -lpthread
Para executar use argumentos em linha de comando, usando o exemplo acima uma entrada possível seria: ./run 7 200
onde 7 é o número de threads e 200 é o número de trapézios.
*/

double areaTotal=0.00;
int nThreads;

double f1(double x){
	return 5.0;
}

double f2(double x){
	return sin(2.0*x)+cos(5.0*x);
}

double calcularAreaSemThreadf1(int nTrapezio){
	double a = 0.00;
	double b = 10.00;
	double h = (b-a)/nTrapezio;
	double area_total = (f1(a)+f1(b))/2;

 	for(int i=1; i<nTrapezio; i++){
 		double x_i = a+i*h;
 		area_total += f1(x_i);
 	}
 	
 	area_total = h*area_total;
 	return area_total;
}

double calcularAreaSemThreadf2(int nTrapezio){
	double a = 0.00;
	double b = 2*M_PI;
	double h = (b-a)/nTrapezio;
	double area_total = (f2(a)+f2(b))/2;

 	for(int i=1; i<nTrapezio; i++){
 		double x_i = a+i*h;
 		area_total += f2(x_i);
 	}
 	area_total = h*area_total;
 	return area_total;
}

void* calcularAreaF1(void *nTrapezio){
	double area_local = calcularAreaSemThreadf1((int)(size_t)nTrapezio);
	area_local = area_local/nThreads;
	areaTotal += area_local;
 	pthread_exit(NULL);
}

void* calcularAreaF2(void *nTrapezio){
	double area_local = calcularAreaSemThreadf2((int)(size_t)nTrapezio);
	//area_local = area_local/nThreads;
	areaTotal += area_local;
 	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	if(argc<3){
		printf("Informe dois argumentos de linha de comando: o número de threads e número de trapézios\n");
		return -1; 
	}

	nThreads = atoi(argv[1]);
	int nTrapezios = atoi(argv[2]);

	int vetorDeDistribuicao[nThreads];

	for(int i=0; i<nThreads; i++){
		vetorDeDistribuicao[i]=0;
	}

	int acumuladorTrapezios = nTrapezios;
	
	while(acumuladorTrapezios > 0){
		for(int i=0; i<nThreads; i++){
			if(acumuladorTrapezios>0){
				vetorDeDistribuicao[i]++;
				acumuladorTrapezios--;
			}
		}
	}

	pthread_t threads[nThreads];
	int status;
	void *thread_return;

	for(int i=0; i<nThreads; i++){
		if(vetorDeDistribuicao[i] != 0){
			status = pthread_create(&threads[i], NULL, calcularAreaF1, (void*)(size_t)vetorDeDistribuicao[i]);
			if(status!=0){
				printf("Erro na criação da Thread %d\n", i);
			}
		}
	}

	for(int i=0; i<nThreads; i++){
		pthread_join(threads[i], &thread_return);
	}
	printf("Teste com f1(x): ");
	printf("%.2e\n", areaTotal);

	areaTotal = 0.00;
	for(int i=0; i<nThreads; i++){
		if(vetorDeDistribuicao[i] != 0){
			status = pthread_create(&threads[i], NULL, calcularAreaF2, (void*)(size_t)12);
			if(status!=0){
				printf("Erro na criação da Thread %d\n", i);
			}
		}
	}

	for(int i=0; i<nThreads; i++){
		pthread_join(threads[i], &thread_return);
	}
	printf("Teste com f2(x): ");
	printf("%.2e\n", areaTotal);

 	//printf("%.2e\n", calcularAreaSemThreadf1(nTrapezios));
 	//printf("%.2e\n", calcularAreaSemThreadf2(nTrapezios));

	return 0;
}