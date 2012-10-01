//Program to implement a BST

//DEclaring the necessary header files
#include<stdio.h>
#include<malloc.h>

//Defining the data structure for the BST node
struct NODE{
	int data; // To store the data of the node
	struct NODE *left;
	struct NODE *right;
};

//typedef for easier use
