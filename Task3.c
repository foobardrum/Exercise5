// Tobias Egger, 16-728-016
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NIL 0

struct node {
	int val;
	struct node* left;
	struct node* right;
};

struct tree {
	struct node* root;
};

struct tree* init(){
	struct tree* t = malloc(sizeof(struct tree));
	t->root = NIL;
	return t;
}
struct node* initnode(struct node* n, int val){
		n = malloc(sizeof(struct node));
		n->val = val;
		n->left = NIL;
		n->right = NIL;
		return n;
}
void insert(struct tree* t, int val){
	struct node* x = t->root;
	struct node* y = NIL;

	while(x != NIL){
		y = x;
		if (val < x->val){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	if (y == NIL){
		x = initnode(x, val);
	}else if(val < y->val){
		y->left = initnode(y->left, val);
	}else{
		y->right = initnode(y->right, val);
	}
}
struct node* search(struct tree* t, int val){
	struct node* p = t->root;
	while (p!= NIL && p->val != val){
		if(val > p->val){
		p = p->right;
		}else {
		p = p->left;
		}
	}
	return p;
}
void delete(struct tree* t, int val){
	
}
void printn(struct node* p){
	if (p!=NIL){
		printn(p->left);
		printf("%d ", p->val);
		printn(p->right);
	}
}
void print(struct tree* t){
	struct node* p = t->root;
	printn(p);

}
int main(){
	struct tree* t = init();
	insert(t, 5);
	insert(t, 2);
	insert(t, 7);
	insert(t, 6);
	insert(t, 8);
	printf("%d", t->root->right->val);
	return 0;
}
