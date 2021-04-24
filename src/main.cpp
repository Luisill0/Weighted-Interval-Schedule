/** Se supone que toda la enumeracion de arreglos empieza en 1
	No hay una razon mas que no tengo ni idea de como programar las funciones 
	sin hacerlo de esa manera
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "ComputeOpt.hpp"
#include "arrays.hpp"

using namespace std;

int readSize();

int main() {
	
	int n = readSize();
	int *v,*p,*f,*s,*m;
	
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
	
	cout << "start\n";
	printArray(s,n);
	cout << "finish\n";
	printArray(f,n);
	cout << "v\n";
	printArray(v,n);
	cout << "p\n";
	printArray(p,n);
	
	int res = computeOpt(n-1,v,p);
	cout << "\nUsando computeOpt:\nEl tiempo maximo es: " << res << '\n';
	
	res = MComputeOpt(n-1,v,p,m);
	cout << "\nUsando MComputeOpt:\nEl tiempo maximo es: " << res << '\n';
	
	//int res = MComputeOpt(7,)
	
	//int a[] = {0,3,6,4,5,5,8}, b[] = {0,0,0,1,1,3,3};	
	//printArray(a,n);
	//printArray(b,n);
	
	//int res = computeOpt(7,v,p);
	
	
	
	return 0;
}

int readSize(){
	int num;
	
	cout << "Ingresa n:\n";
	cin >> num;
	
	return ++num;
}

