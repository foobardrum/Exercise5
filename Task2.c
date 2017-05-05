// Tobias Egger, 16-728-016

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NIL 0

struct element {
	int val;
	struct element *next;
};
struct element* H[8];

void init(){
	int i;
	for(i=0; i<8; i++){
		H[i] = malloc(sizeof(struct element));
		H[i]->next = NULL;
		H[i]->val = NIL;	
	}
}
int h(int val){
	double a = (sqrt(5)-1)/2;
	return floor(8*fmod(val*a,1));
}
void insert(int val){
	int i = h(val);
	if (H[i]->val == NIL){
		H[i]->val = val;
	}else{
		struct element* p = H[i];
		while(p->next != NULL){
			p = p->next;
		}
		p->next = malloc(sizeof(struct element));
		p->next->val = val;
		p->next->next = NULL;
	}
}
struct element* search(int val){
	int i = h(val);
	if (H[i]->val == val){
		return H[i];
	}else{
		struct element* p = H[i];
		while(p->next != NULL && p->val != val){
			p = p->next;
		}
		if (p->val == val){
			return p;
		}else{
			return NULL;
		}
	}
	
}
void printHash(){
	int count = 0;
	int i;
	for (i=0; i<8; i++){
		if (H[i]->val != NIL){
			printf("\nindex: %d; value(s): %d", i, H[i]->val);
			struct element* p = H[i]->next;
			while(p != NULL){
				printf(", %d", p->val);
				p = p->next;
				count +=1;
			}
		}
		count += 1;
	}
	printf("\n\nTable Size: %d", count);
}

int main(){
	init();
	insert(111);
	insert(10112);
	insert(1113);
	insert(5568);
	insert(63);
	insert(1342);
	insert(21231);
	printHash();
	printf("\n\nsearch: %s", search(1));	
	printf("\nsearch: %d", *search(10112));
	printf("\nsearch: %d", *search(1113));
	printf("\nsearch: %d", *search(5568));
	printf("\nsearch: %s", search(337));
	return 0;
}
