/** Se supone que toda la enumeracion de arreglos empieza en 1
	No hay una razon mas que no tengo ni idea de como programar las funciones 
	sin hacerlo de esa manera
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>
#include "ComputeOpt.hpp"
#include "arrays.hpp"

using namespace std;

int readSize();
void showArrays(int* s,int* f,int* v,int* p,int n);
double* calculateTimes(int n);
double getAverage(double* array);
void showAverages(double* tOpt, double* tMOpt,double *tFS);
void showDuration(double duration);

int main() {
		
	int n = readSize();
	double tOpt[10],tMOpt[10],tFS[10],*temp;
	
	system("cls");
	
	cout << "n = " << n-1 << "\n\n";
	
	for(int i = 0; i < 10; i++){
		temp = calculateTimes(n);
		tOpt[i] = temp[0];
		tMOpt[i] = temp[1];
		tFS[i] = temp[2];
	}
	
	cout << "\n   ComputeOpt   MComputeOpt    FindSolution\n\n";
	
	for(int i = 0; i < 10; i++){				
		std::cout << std::setfill(' ') << std::setw(2) << i+1 << " |";
		std::cout << std::setfill(' ') << std::setw(6) << tOpt[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tMOpt[i];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << tFS[i];
		cout<< "\n";
	}
	
	showAverages(tOpt,tMOpt,tFS);

	
	return 0;
}

double* calculateTimes(int n){
	int *v,*p,*s,*m,*f;
	double t1,t2,tGen;
	int res;
	double *times = new double[3];
	timeval tim;
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	v = createArray(n);
	p = createArray(n);
	s = createArray(n);
	m = createArray(n);
	f = createArray(n);
	
	randomizeArray(f,n,tim.tv_usec);
	setArrayTo(p,n,0);
	setArrayTo(m,n,-1);
	
	v[0] = p[0] = s[0] = f[0] = 0;
	m[0] = -1;
	
	MergeSort(f,0,n-1);
	
	for(int i = 1; i < n; i++){
		s[i] = f[i] - (rand() % 8 + 2);
		if(s[i] < 0 ){
			s[i] = 0;
		}
		v[i] = f[i] - s[i];
	}
	
	for(int i = 1; i < n; i++){
		for(int j = 1; j < n; j++){
			if(s[i] > f[j]){
				p[i]++;
			}
		}
	}

	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	tGen = (t2-t1);		
	
	//showArrays(s,f,v,p,n);
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 	
	res = 0; //computeOpt(n-1,v,p);	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[0] = (t2-t1) + tGen;	
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 
	res = MComputeOpt(n-1,v,p,m);
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[1] = (t2-t1) + tGen;
	
	cout <<"Tiempo maximo = " << res << "\n";
	cout <<"Intervalos a tomar:\n";
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	findSolution(n-1,v,p,m);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	times[2] = (t2-t1) + tGen;
	cout << "\n\n";
	
	return times;	
}

void showDuration(double duration){
	int seconds,ms,usec;
	int temp = (int) duration;
	
	seconds = temp/1000000;
	temp %= 1000000;
	
	ms = temp/1000;
	temp %= 1000;
	
	usec = temp % 1000;
	
	cout << seconds << " seconds  " << ms << "  miliseconds  " << usec << "  usec";
}

double getAverage(double* array){
	double average=0;
	for(int i = 0; i < 10; i++){
		average += array[i];
	}
	return(average/10);
}

void showAverages(double* tOpt, double* tMOpt,double *tFS){
	double promOtp,promMOpt,promTFS;
	
	promOtp = getAverage(tOpt);
	promMOpt = getAverage(tMOpt);
	promTFS = getAverage(tFS);
	
	cout<< "\n\nPromedios:\n\n" << "ComputeOpt: ";
	showDuration(promOtp);
	cout<< "\nMComputeOpt: ";
	showDuration(promMOpt);
	cout<< "\nFindSolution: ";
	showDuration(promTFS);
}


void showArrays(int* s,int* f,int* v,int* p,int n){
	cout << "start\n";
	printArray(s,n);
	cout << "finish\n";
	printArray(f,n);
	cout << "v\n";
	printArray(v,n);
	cout << "p\n";
	printArray(p,n);
} 

int readSize(){
	int num;
	
	cout << "Ingresa n:\n";
	cin >> num;
	
	return ++num;
}

