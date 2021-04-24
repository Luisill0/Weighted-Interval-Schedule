/** Se supone que toda la enumeracion de arreglos empieza en 1
	No hay una razon mas que no tengo ni idea de como programar las funciones 
	sin hacerlo de esa manera
*/

#include <iostream>
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

int main() {
		
	int n = readSize();
	int *v,*p,*f,*s,*m,res;
	double t1,t2,total;
	timeval tim;
	
	system("cls");
	
	cout << "n = " << n-1 << "\n\n";
	
	cout << "Generating jobs\n";
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	v = createArray(n);
	p = createArray(n);
	s = createArray(n);
	m = createArray(n);
	f = createArray(n);
	
	randomizeArray(s,n,time(NULL));
	setArrayTo(p,n,0);
	setArrayTo(m,n,-1);
	
	v[0] = p[0] = s[0] = f[0] = 0;
	m[0] = -1;
	
	MergeSort(s,0,n-1);
	
	for(int i = 1; i < n; i++){
		f[i] = s[i] + rand() % 8 + 1;
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
	
	total = (t2-t1);	
	cout << "Jobs and arrays generated (" << total << " usec passed)\n";

	if(n < 21){
		showArrays(s,f,v,p,n);	
	}
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 	
	res = computeOpt(n-1,v,p);	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	total = (t2-t1);	
	cout << "\nUsando computeOpt:\nEl tiempo maximo es: " << res << " (" << total << " usec passed)" << '\n';
	
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec; 
	res = MComputeOpt(n-1,v,p,m);
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	total = (t2-t1);
	cout << "\nUsando MComputeOpt:\nEl tiempo maximo es: " << res << " (" << total << " usec passed)" << '\n';
	
	cout << '\n';
	findSolution(n-1,v,p,m);
	
	return 0;
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

