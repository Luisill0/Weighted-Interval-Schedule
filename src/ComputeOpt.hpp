#include <iostream>

int max(int num1,int num2){
	int max;
	
	max = (num1 > num2) ? num1 : num2;
	
	return max;
}

int computeOpt(int j,int v[],int p[]){
	int num1,num2;
	if(j == 0){
		return 0;
	}else{
		//num1 = v[j] + computeOpt(p[j],v,p);
		//num2 = computeOpt(j-1,v,p);
		//return max(num1,num2);
		return max(v[j] + computeOpt(p[j],v,p),computeOpt(j-1,v,p));
	}
}


