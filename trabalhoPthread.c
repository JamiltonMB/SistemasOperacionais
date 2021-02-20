#include <stdio.h>
#include <math.h>

double f1(double x){
	return 5.0;
}

double f2(double x){
	return sin(2.0*x)+cos(5.0*x);
}

int main(){
	int n = 120;
 	double a = 0.0;
 	//double b = 10.0;
 	double b = 2*M_PI;
 	double h = (b-a)/n;
 	double area_total = (f2(a)+f2(b))/2;
 	
 	for(int i=1; i<n; i++){
 		double x_i = a+i*h;
 		area_total += f2(x_i);
 	}
 	
 	area_total = h*area_total;
 	printf("%lf\n", area_total);
	return 0;
}
