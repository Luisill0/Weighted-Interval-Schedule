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

using namespace std;

int readSize();
int* createArray(int n);
void randomizeArray(int* a,int n,double SEED);
void printArray(int* a,int n);
void setArrayTo(int* a,int n, int num);

void Merge(int A[],int p,int q, int r);
void MergeSort(int A[],int p,int r);
void intercambia(int *A, int *B);

int main() {
	
	int n = readSize();
	int *v,*p,*f,*s,*m;
	
	v = createArray(n);
	p = createArray(n);
	s = createArray(n);
	m = createArray(n);
	f = createArray(n);
	
	randomizeArray(s,n,2000);
	setArrayTo(p,n,0);
	
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
	
	int res = computeOpt(7,v,p);
	cout << "\nEl tiempo maximo es: " << res << '\n';
	
	//int a[] = {0,3,6,4,5,5,8}, b[] = {0,0,0,1,1,3,3};	
	//printArray(a,n);
	//printArray(b,n);
	
	//int res = computeOpt(7,v,p);
	
	
	
	return 0;
}

void setArrayTo(int* a,int n, int num){
	for(int i = 1; i < n; i++){
		a[i] = num;
	}
}

void intercambia(int *A, int *B){
    int Aux;

    Aux = *A;
    *A = *B;
    *B = Aux;
}

void printArray(int* a,int n){
	
	for(int i = 1; i < n; i++){
		cout << "[";
		std::cout.width(2);
		cout << a[i] << "] ";
	}
	cout << "\n\n";
}

int readSize(){
	int num;
	
	cout << "Ingresa n:\n";
	cin >> num;
	
	return ++num;
}

int* createArray(int n){
	int* a = new int[n];
	
	return a;
}

void randomizeArray(int* a,int n,double SEED){
	srand(SEED);
	for(int i = 1; i < n; i++){
		a[i] = rand() % 19 + 1;
	}
}

void Merge(int A[],int p,int q, int r){
    int i,j,k;
    int n1=q-p+1;
    int n2=r-q;
    int L[n1],R[n2];
    for(i=0;i<n1;i++){
    	L[i]=A[p+i];
    }
    for(j=0;j<n2;j++){
    	R[j]=A[q+j+1];
    }
    L[n1]=INT_MAX;
    R[n2]=INT_MAX;

    i=0;
    j=0;
    for(k=p;k<=r;k++){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }else{
            A[k]=R[j];
            j++;
        }
    }  
}

void MergeSort(int A[],int p,int r){
    int q;
    if(p<r){
        q=floor((p+r)/2);
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
