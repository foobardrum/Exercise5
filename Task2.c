// Tobias Egger, 16-728-016

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct element {
	int val;
	struct element *next;
};
//void init(){
//	//
//}
int h(int val){
	int a = ((sqrt(5)-1)/2);
	printf("%d", a);
	return floor(8*val*(a%1));
}
struct element* H[8];

int main(){
	printf("%d", h(100));
	return 0;
}
