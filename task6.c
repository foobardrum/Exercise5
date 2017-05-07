#include <stdlib.h>
#include <stdio.h>

#define black 0
#define red 1

struct rb_node {
  int key;
  int color;
  struct rb_node* left;
  struct rb_node* right;
  struct rb_node* parent;
};

struct rb_tree {
  int bh;
  struct rb_node *root;
  struct rb_node *nil;
};

struct rb_tree* rb_initialize() {
  struct rb_tree* tree;
  struct rb_node* node;

  tree = (struct rb_tree*) malloc(sizeof(struct rb_tree));

  tree->nil = (struct rb_node*) malloc(sizeof(struct rb_node));
  tree->nil->parent = tree->nil;
  tree->nil->left = tree->nil;
  tree->nil->right = tree->nil;
  tree->nil->color = black;
  tree->nil->key = -2;

  tree->root = tree->nil;
  tree->bh = 0;

  return tree;
}

void rb_leftRotate(struct rb_tree* T, struct rb_node* x) {
	struct rb_node* t1 = (x->right)->left;
	struct rb_node* t2 = x->right;
	(x->right)->left = x;
	x->right = t1;
	if (x->right != T->nil){
		(x->right)->parent = x;	
	}
	if (x->parent == T->nil){
		T->root = t2;
		x->parent = t2;
	}else{
		if((x->parent)->left == x){
			(x->parent)->left = t2;
			x->parent = t2;
		}else{
			(x->parent)->right = t2;
			x->parent = t2;
		}
	}
}

void rb_rightRotate(struct rb_tree* T, struct rb_node* y) {
	struct rb_node* t1 = (y->left)->right;
	struct rb_node* t2 = y->left;
	(y->left)->right = y;
	y->left = t1;
	if (y->left != T->nil){
	  (y->left)->parent = y;	
	}
	if (y->parent == T->nil){
	  T->root = t2;
	  y->parent = t2;
	}else{
	  if((y->parent)->right == y){
	    (y->parent)->right = t2;
	    y->parent = t2;
	  }else{
	    (y->parent)->left = t2;
	    y->parent = t2;
	  }
	}
}

struct rb_node* rb_insertFixup(struct rb_tree* T, struct rb_node* z) {
  struct rb_node* y;
  while (z->parent->color == red) {
    if (z->parent == z->parent->parent->left) { /* non-mirrored cases */
      y = z->parent->parent->right;
      if (y->color == red) {                    /* case 1 */
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {            /* case 2 */
          z = z->parent;
          rb_leftRotate(T, z);
        }
        z->parent->color = black;               /* case 3 */
        z->parent->parent->color = red;
        rb_rightRotate(T, z->parent->parent);
      }
    } else {                                    /* mirrored cases */
      y = z->parent->parent->left;
      if (y->color == red) {                    /* case 1m */
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {             /* case 2m */
          z = z->parent;
          rb_rightRotate(T, z);
        }
        z->parent->color = black;               /* case 3m */
        z->parent->parent->color = red;
        rb_leftRotate(T, z->parent->parent);
      }
    }
  }
  if (T->root->color == red) {
    T->bh += 1;
  }
  T->root->color = black;
}

void rb_insert(struct rb_tree* tree, int key) {
  struct rb_node *oneDelayed = tree->nil;
  struct rb_node *insertPlace = tree->root;
  struct rb_node *nodeToInsert =
    (struct rb_node*) malloc(sizeof(struct rb_node));
  nodeToInsert->key = key;
  nodeToInsert->color = red;

  nodeToInsert->left=tree->nil;
  nodeToInsert->right=tree->nil;
  nodeToInsert->parent=tree->nil;
  while (insertPlace != tree->nil) {
    oneDelayed = insertPlace;
    if (nodeToInsert->key < insertPlace->key) {
      insertPlace = insertPlace->left;
    }
    else {
      insertPlace = insertPlace->right;
    }
  }

  if (oneDelayed == tree->nil) {
    tree->root = nodeToInsert;
  }
  else if (oneDelayed->key < nodeToInsert->key) {
    oneDelayed->right = nodeToInsert;
    nodeToInsert->parent = oneDelayed;
  }
  else {
    oneDelayed->left = nodeToInsert;
    nodeToInsert->parent = oneDelayed;
  }
  rb_insertFixup(tree, nodeToInsert);
}

void rb_printRecursive(struct rb_node *root, struct rb_tree *tree) {
  if (root == tree->nil) {
    return;
  }
  rb_printRecursive(root->left, tree);
  printf(" %d (%s) -- %d\n", root->key, (root->color==red?"RED":"BLACK"),
         root->left->key);
  rb_printRecursive(root->right, tree);
  printf(" %d (%s) -- %d\n", root->key, (root->color==red?"RED":"BLACK"),
         root->right->key);
}

void rb_print(struct rb_tree *tree) {
  printf("graph g {\n");
  rb_printRecursive(tree->root, tree);
  printf("}\n");
}

struct rb_node* rb_search(struct rb_tree* T, int q) {
  struct rb_node* x = T->root;

  if (x == T->nil) {
    return x;
  }
  while (x->key != q) {
    if (q < x->key) {
      x = x->left;
    }
    else {
      x = x->right;
    }
    if (x == T->nil) {
      return x;
    }
  }
  return x;
}

int main(int argc, char **argv) {
  struct rb_tree *t1;

  t1 = rb_initialize();
  rb_insert(t1, 10);
  rb_insert(t1, 1);
  rb_insert(t1, 11);
  rb_insert(t1, 9);
  rb_insert(t1, 5);
  rb_insert(t1, 13);
  rb_print(t1);
  rb_leftRotate(t1, t1->root->left);
  rb_print(t1);
  rb_rightRotate(t1, t1->root->left);
  rb_print(t1);
  return 0;
}
