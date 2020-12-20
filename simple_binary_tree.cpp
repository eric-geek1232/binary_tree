/*By Eric 19/12/2020 ---binary tree---*/

#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
	int data;
	Node *child_left;
	Node *child_right;
	Node *parent;
};


Node *root = NULL;
int treeDepth = -1;

//function prototypes
Node *createNode(int number, Node *parent);
void insertNode(Node *&tree, Node *parent, int number);
void countNodes(Node *tree, int count);
void showTree(Node *tree);
void searchNode(Node *tree, int number, int count);
void preOrder(Node *tree);
void inOrder(Node *tree);
void postOrder(Node *tree);
bool searchNodeToDelete(Node *tree, int number);
void replaceNode(Node *tree, Node *newNode);
void deleteNode(Node *nodeToDelete);
void destroyNode(Node *node);
Node *selectMinNode(Node *tree);
Node *selectMaxNode(Node *tree);
Node *getPredecessor(Node *node);
Node *getSuccessor(Node *node);

int main() 
{
	Node *node_aux = NULL;
	int option = 0;
	int number = 0;
	
	do {
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< "[1] Insert node"<< endl;
		cout<< "[2] Show Tree"<< endl;
		cout<< "[3] Search node"<< endl;
		cout<< "[4] pre-order list"<< endl;
		cout<< "[5] in-order list"<< endl;
		cout<< "[6] post-order list "<< endl;
		cout<< "[7] delete node"<< endl;
		cout<< "[8] show max-value"<< endl;
		cout<< "[9] show min-value"<< endl;
		cout<< "[10] quit"<< endl;
		
		cout<< "\nSelect: ";
		cin>> option;
		
		system("cls");
		
		switch(option){
			case 1:
				cout<< "Type your number: ";
				cin>> number;
				
				insertNode(root, NULL, number);
				system("cls");
				break;
				
			case 2:
				cout<< "\tShowing...\n"<< endl;
				showTree(root); 
				system("pause");
				break;
				
			case 3: 
				cout<< "Type your number to search: ";
				cin>> number;
				
				system("cls");
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				searchNode(root, number, 0);
				system("pause");
				break;
				
			case 4:
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				cout<< "\n\nPre-order list:  ";
				preOrder(root);
				cout<< "\n"<< endl;
				system("pause");
				break;
				
			case 5:
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				cout<< "\n\nIn-order list:  ";
				inOrder(root);
				cout<< "\n"<< endl;
				system("pause");
				break;
				
			case 6: 
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				cout<< "\n\nPost-order list:  ";
				postOrder(root);
				cout<< "\n"<< endl;
				system("pause");
				break;
				
			case 7:
				cout<< "Type your number to delete: ";
				cin>> number;
				
				system("cls");
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				if (searchNodeToDelete(root, number)) {
					cout<< "\n\nNode: "<< number<< " has been deleted"<< endl;
					cout<< "\n\n\tVerify Again...\n"<< endl;
					
					showTree(root);	
				} else {
					cout<< "\n\nNode: "<< number<< " not found"<< endl;
				}
				
				cout<< "\n";
				system("pause");
				break;
				
			case 8:
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				node_aux = selectMaxNode(root);
				if (node_aux != NULL) {
					cout<< "\n\n\nMax-value: "<< node_aux->data<< "\n"<< endl;
					node_aux = NULL;	
				}
				system("pause");
				break;
				
			case 9:
				cout<< "\tVerify...\n"<< endl;
				showTree(root);
				
				node_aux = selectMinNode(root);
				if (node_aux != NULL) {
					cout<< "\n\n\nMin-value: "<< node_aux->data<< "\n"<< endl;
					node_aux = NULL;	
				}
				system("pause");
				break;
				
			case 10:
				cout<< "\t**Thank you**\n"<< endl;
				system("pause");
				break;
		}
		system("cls");
	} while (option != 10);
	
	return 0;
}

// prepare your node
Node *createNode(int number, Node *parent)
{
	Node *node_new = new Node();
	
	node_new->data = number;
	node_new->child_left = NULL;
	node_new->child_right = NULL;
	node_new->parent = parent;
}

void insertNode(Node *&tree, Node *parent, int number)
{
	if (tree == NULL) { // insert node
		Node *node_new = createNode(number, parent);
		tree = node_new;
	} else { // if you have more than one nodes in your tree
		// get root_value
		int root_value = tree->data;
		
		//Compare the new value with the root 
		if (number < root_value) {
			insertNode(tree->child_left, tree, number); // go to the left on each node
		} else {
			insertNode(tree->child_right, tree, number); // go to the right on each node
		}
	}
}

void countNodes(Node *tree, int count)
{
	if (tree == NULL) {
		if (treeDepth < count-1) { // calculate tree depth
			treeDepth = count-1;
		}
		return;
	} else { // if you have more than 1 nodes in your tree
		countNodes(tree->child_right, count+1); // go to the right on each node
		for (int i = 0; i < count; i++) {
			cout<< "   ";					// print spaces this is stetic
		}
		cout<< tree->data<< endl; // print node
		countNodes(tree->child_left, count+1); // go to the left on each node
	}
}

void showTree(Node *tree)
{
	treeDepth = -1; // reset tree depth
	countNodes(tree, 0);
	
	if (treeDepth != -1) {
		cout<< "\n\nTree depth: "<< treeDepth<< "\n"<< endl;
	} else { 
		cout<< "\n\nTree depth: "<< treeDepth<< endl;
		cout<< "\n\n\t**Empty tree**\n"<< endl;
	}
}

void searchNode(Node *tree, int number, int count)
{
	if (tree == NULL) {
		cout<< "\n\nNode: "<< number<< " not found\n"<< endl;
		return;
	} else if (tree->data == number) {
		cout<< "\n\nNode: "<< number<<" found"<< endl;
		
		cout<< "\nHigh: "<< (treeDepth-count)+1<< endl;
		cout<< "\nLevel: "<< treeDepth-count<< endl;
		
		Node *predecessor = getPredecessor(tree);
		Node *successor = getSuccessor(tree);
		
		if (predecessor != NULL) {
			cout<< "\nPredecessor: " <<getPredecessor(tree)->data<< endl;
		} else {
			cout<< "\nPredecessor: you do not have enough nodes yet"<< endl;
		}
		
		if (successor != NULL) {
			cout<< "\nSuccessor: " <<getSuccessor(tree)->data<< endl;	
		} else {
			cout<< "\nSuccessor: you do not have enough nodes yet"<< endl; 
		}
		
		if (tree->child_left != NULL && tree->child_right != NULL) {
			cout<< "\nKind of Node: Parent"<< endl;
			cout<< "\nGrade: 2\n"<< endl;
		} else if (tree->child_left != NULL || tree->child_right != NULL) {
			cout<< "\nKind of Node: Parent"<< endl;
			cout<< "\nGrade: 1\n"<< endl;
		} else {
			if (predecessor == NULL && successor == NULL && tree->parent == NULL) { // there's only one node in the tree
				cout<< "\nKind of Node: Root"<< endl;
			} else {
				cout<< "\nKind of Node: Hoja"<< endl;	
			}
			cout<< "\nGrade: 0\n"<< endl;
		}
	} else if (number < tree->data) { // keep searching for the left side
		searchNode(tree->child_left, number, count+1);
	} else {
		searchNode(tree->child_right, number, count+1); // keep searching for the right side
	}
}

void preOrder(Node *tree)
{
	if (tree == NULL) { // tree- empty
		return;
	} else { 
		cout<< tree->data << " - "; // print node
		preOrder(tree->child_left); // go to the left on each node
		preOrder(tree->child_right); // go to the right on each node
	}
}

void inOrder(Node *tree)
{
	if (tree == NULL) { // tree empty
		return;
	} else {
		inOrder(tree->child_left); // go to the left on each node
		cout<< tree->data << " - "; // print node
		inOrder(tree->child_right); // go to the right on each node
	}
}

void postOrder(Node *tree)
{
	if (tree == NULL) { // tree empty
		return;
	} else {
		postOrder(tree->child_left); // go to the left on each node
		postOrder(tree->child_right); // go to the right on each node
		cout<< tree->data << " - "; // print node
	}
}

bool searchNodeToDelete(Node *tree, int number)
{
	if (tree == NULL) { // node not found
		return false;
	} else if (number < tree->data) { // keep searching for the left side
		searchNodeToDelete(tree->child_left, number);
	} else if (number > tree->data) { // keep searching for the right side
		searchNodeToDelete(tree->child_right, number);
	} else {
		deleteNode(tree); // node found
		return true;
	}
}

Node *selectMinNode(Node *tree)
{
	if (tree == NULL) { // tree empty
		return NULL;
	} 
	
	if (tree->child_left != NULL) {
		return selectMinNode(tree->child_left); // go to the left on each node
	} else {
		return tree; // min node found
	}
}

Node *selectMaxNode(Node *tree)
{
	if (tree == NULL) { // empty tree
		return NULL;
	} 
	
	if (tree->child_right != NULL) { 
		return selectMaxNode(tree->child_right); // go to the right on each node
	} else {
		return tree; // max node found
	}
}

void replaceNode(Node *tree, Node *newNode)
{
	if (tree->parent != NULL) {
		// verify child side on parent node
		if (tree->parent->child_left != NULL) { // left side
			if (tree->data == tree->parent->child_left->data) {
				tree->parent->child_left = newNode; // parent -> points to its new child
			}
		}
		 
		if (tree->parent->child_right != NULL) { // right side
			if (tree->data == tree->parent->child_right->data) {
				tree->parent->child_right = newNode; // parent -> points to its new child
			}	
		}
	} 
	
	if (newNode != NULL) {
		newNode->parent = tree->parent; // node -> points to its new parent
		
		if (tree->child_left == NULL && tree->parent == NULL) {  // remove the root with no children on the left
			root = newNode;
		} else if (tree->child_right == NULL && tree->parent == NULL) { // remove the root with no children on the right
			root = newNode;
		} 
	}
}

void destroyNode(Node *node)
{
	if (node->child_left == NULL && node->child_right == NULL && node->parent == NULL) { // remove root without children
		root = NULL;
	}
	
	// unlink node
	node->child_left = NULL;
	node->child_right = NULL;
	node->parent = NULL;
	
	delete node;
}

void deleteNode(Node *nodeToDelete)
{
	if (nodeToDelete->child_left != NULL && nodeToDelete->child_right != NULL) { // remove node with left child and right child
		Node *min = selectMinNode(nodeToDelete->child_right); // first go to the right and then select min node 
		nodeToDelete->data = min->data; // change values
		deleteNode(min); // delete node
	} else if (nodeToDelete->child_left != NULL) { // remove node with children on the left only
		replaceNode(nodeToDelete, nodeToDelete->child_left);
		destroyNode(nodeToDelete);
	} else if (nodeToDelete->child_right != NULL) { // remove node with children on the right only
		replaceNode(nodeToDelete, nodeToDelete->child_right);
		destroyNode(nodeToDelete);
	} else { // remove node with no children
		replaceNode(nodeToDelete, NULL);
		destroyNode(nodeToDelete);
	}
}

Node *getPredecessor(Node *node)
{
	if (node == NULL) { // tree empty
		return NULL;
	} 
	
	if (node->child_left != NULL) {
		return selectMaxNode(node->child_left); // keep going to the left
	}
	
	Node *aux = node->parent;
	
	while (aux != NULL && node == aux->child_left) { // search predecessor
		node = aux;
		aux = aux->parent; // update parent
	}
	
	return aux;
}

Node *getSuccessor(Node *node)
{
	if (node == NULL) { // tree empty 
		return NULL;
	} 
	
	if (node->child_right != NULL) {
		return selectMinNode(node->child_right); // keep going to the right
	}
	
	Node *aux = node->parent;
	
	while (aux != NULL && node == aux->child_right) { // search sucessor
		node = aux;
		aux = aux->parent; // update parent
	}
	
	return aux;
}
