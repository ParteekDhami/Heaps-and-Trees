#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


Variable variables[10];
int varCount = 0; 


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	//allocate memory
	Node *newNode = (Node*)malloc (sizeof(Node));

 if (newNode == NULL) {  // Check if memory allocation failed
        printf("memory allocation fail\n");
        exit(1);  // Exit if memory allocation fails
     }	
	strncpy(newNode -> data,data, sizeof(newNode->data) - 1);//copy info from data to newNode
	newNode->data[sizeof(newNode->data) - 1] = '\0';

	//make pointer for right and left of new node pointing to null
	newNode ->right=NULL;
	newNode-> left = NULL;
	
	return newNode;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr){
	if(expr[0]!= '('){
		Node *node = createNode(expr);
		return node;
	}
	
	int length = strlen(expr); //length of expression string
int open_Bracket = 0; //number of open brackets
int indexOper = -1;  // position of operator

// loop through string after first bracket and end before last bracket
 for (int i = 1; i < length - 1; i++) {

    // Count open and close brackets
    switch (expr[i]) {
        case '(': 
            open_Bracket++; // add to count open brackets
            break;
        case ')': 
            open_Bracket--; //Decrement count for close bracket
            break;
        case '+': //go to other options
        case '-':
        case '*':
        case '/':
            // Check if no open brackets
            if (open_Bracket == 0) {
                indexOper = i; // store the index of operator
                i = length;           // exit loop
            }
            break;
        default:
           
            break;
    } 
} //now indexOper has the postion of binary operater

char left[100], right[100], op[2];
    strncpy(left, expr + 1, indexOper - 1);
    left[indexOper-1] = '\0';
    strncpy(right, expr +indexOper + 1, length -indexOper- 2);
    right[length -indexOper - 2] = '\0';
    op[0] = expr[indexOper];
    op[1] = '\0';

    Node *root = createNode(op);
    root -> left = parseExpression(left);
    root -> right = parseExpression(right);
	return root;
}

// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
	//if current node is NULL stop recursion
 	if (!root) return;
	//print data in node
    printf("%s ", root-> data);
	//Recursively preorder traversal from right subtree
	preorder(root-> right);

    //Recursively preorder traversal from left subtree
	preorder(root-> left);
	
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
	//if current node is NULL stop recursion
	if (!root) return;
    if (root-> left || root ->right) printf("(");//add bracket for ubtree
    inorder(root ->left);
    printf("%s", root->data);
    inorder(root-> right);//print current node
    if (root ->left || root-> right) printf(")");//closes bracket for subtree

}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
if (!root) return;
    postorder(root ->left);//traverse left and right subtree 
    postorder(root ->right);
	//prinnt data at node
    printf("%s ", root->data);
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
    if (!root) return;

    if (isalpha(root->data[0])) {//check if first thing is a letter
        int found = 0;//to check if variable had been found before
		//check if letter already exsist s in array
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root->data) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {//if letter is not found ask user to input value
            strcpy(variables[varCount].varName, root->data);
            printf("enter value for %s: ", root->data);
            scanf("%f", &variables[varCount++].value);
			
        }
    }

    promptVariables(root->left);
    promptVariables(root->right);
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root) {
    if (!root) return 0;

    // If the node is a variable, look up its value
    if (isalpha(root-> data[0])) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].varName, root ->data) == 0) {
                return variables[i].value;
            }
        }
        return 0; // Default value for undefined variables
    }

    // If node is a number, convert string to float
    if (isdigit(root ->data[0]) || root->data[0] == '.') {
        return atof(root-> data);
    }

    // Calculate the left and right subtrees
    float right = calculate(root -> right);
    float left = calculate(root -> left);

    //use switch case for math opperations
    switch (root ->data[0]) {
        case '+':
            return left+ right;
        case '-':
            return left-right;
        case '*':
            return left* right;
        case '/':
            if (right ==0) {
                printf("cant divide 0\n");
                return 0;
            }
            return left/right;
        default:
            printf("invalid entry '%s'\n", root ->data);
            return 0;
    }
}

