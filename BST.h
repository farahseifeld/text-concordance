//BST h
//made by:
// Habiba Gamal 900151007
//  Mayada el Ghamry 900152853
// Farah Seif ElDin 900160195
//assignment 5

#pragma once
#ifndef BST_H
#define BST_H
#include <string>
using namespace std;

template <class keyType, class dataType>

class BST
{
private:
    class node
    {
    public:
        keyType key; //key
        dataType data; //data
        node* right; //pointer to right child
        node* left; //pointer to left child
    };
    node* root; //node pointer to root
    
   bool insertp(node* &r,keyType k, dataType d); //private function of insert
    bool searchp(node* r, const keyType &k);    //private function of search
    bool retrievep(node* r,const keyType &k, dataType &d); //private function of retrieve
    void traversep(node *r); //private function of traverse
    void preorderp(node* r, ofstream &out); //private function of preorder
	void getNodePar(node*& p, node* &n, keyType k); //gets parent of a node
	void successor(node* & n, node* & s, node*& p); //gets successor of a node
	void predecessor(node* &n, node* & pre); //gets predecessor of a node
public:
    BST(); //constructor
    ~BST(); //destructor
    bool insert(keyType k, dataType d); //public function of insert (inserts a new key into BST)
    void empty(); //makes tree empty
    bool retrieve(const keyType &k, dataType &d); //returns data of a given key by reference. Returns true if retrieved
    bool search(const keyType &k); //returns true if key is found in tree. public function of search
    void traverse();//inorder traversal of BST
    void preorderFile(string filename, bool o); //preorder traversal of BST. outputs tree into a file
    void levelorder(); //level order traversal of BST
    bool remove(keyType k); //removes a node from a BST
    bool isEmpty(); //returns true if BST is empty
    bool getMax(keyType & k, dataType & d); //returns by reference maximum data in a BST
    bool getMin(keyType & k, dataType & d); //returns by reference minimum data in a BST
};







#endif
#include "BST.cpp"
