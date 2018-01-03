//BST cpp
//made by:
// Habiba Gamal 900151007
//  Mayada el Ghamry 900152853
// Farah Seif ElDin 900160195
//assignment 5

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

//constructor
template <class keyType, class dataType>
BST <keyType, dataType>::BST()
{
    root = NULL;
}

//private function of insert
template <class keyType, class dataType>
bool BST<keyType, dataType>::insertp(node* &r, keyType k, dataType d) //takes pointer to a node, keyType and dataType
{
	if (r == NULL) //if root is null/tree is empty
	{
		r = new node; //create new node
		r->key = k; //put k into key of r
		r->data = d; //put d into data of r
		r->right = NULL; //make right child of r point to null
		r->left = NULL; //make left child of r point to null
		return true;
	}
	else if (k == r->key) //if the key already exists in the truee
    {
		r->data = d; //only change the data
		return true;
	}
    else if (k < r->key) //if k is smaller than key of r
        insertp(r->left, k, d); //call the function again pointing to the root of the left subtree
    else //if k is bigger than key of r
        insertp(r->right, k, d); //call the function again pointing to the root of the right subtree
    
}

//private function of search
template <class keyType, class dataType> 
bool BST<keyType, dataType>::searchp(node* r, const keyType &k)
{
	if (r == NULL) //if BST is empty
    {
		return false;
	}
    
    else if (k == r->key) //if given k is the same as key of r
        return true;

	else 
		if (k < r->key)  //if k is smaller than key of r
		searchp(r->left, k); //call the function pointing to the node of the left sub-tree
	
	
		else  //if k is bigger than r
		searchp(r->right, k); //call the function again pointing to the node of the right sub-tree
		
	
}


//public function of insert
template <class keyType, class dataType>
bool BST<keyType, dataType>::insert(keyType k, dataType d)
{
    return insertp(root, k, d); //calls the private function of insert, with an added parameter (pointer to root of BST)
}


//private function of retrieve
template <class keyType, class dataType>
bool BST<keyType, dataType>::retrievep(node* r,const keyType &k, dataType &d)
{
    if (r == NULL) //if tree if empty
        return false;
    
    else if (k == r->key) //if given k is the same as key of r
    {
        d=r->data; //d (sent by reference) equals data of r
        return true;
    }
    else if (k < r->key) //if k is smaller than key of r
        retrievep(r->left, k, d); //call the function again pointing at the root of the left sub-tree
    else //if k is bigger than key of r
        retrievep(r->right, k, d); //call the function again pointing at the root of the right sub-tree
}

//public function of retrieve
template <class keyType, class dataType>
bool BST<keyType, dataType>::retrieve(const keyType &k, dataType &d)
{
    return retrievep(root, k, d); //calls the private function of retreive pointing at the root of the BST
}

//public function of search
template <class keyType, class dataType>
bool BST<keyType, dataType>::search(const keyType &k)
{
	
    return searchp(root, k); //calls the private function of search pointing to the root of the BST
	
}

//private preorder traversal of BST into output file
template <class keyType, class dataType>
void BST<keyType, dataType>::preorderp(node *r, ofstream &out)
{
    if (r != NULL) //if tree is NOT empty
    {
        out << r->key << " " << r->data << " " << endl; //print key of r, then space, then data of r into output file
        preorderp(r->left, out); // call function pointing at root of left sub-tree
        preorderp(r->right, out); //call function pointing at root of right sub-tree
    }
    
}


//private inorder traversal
template <class keyType, class dataType>
void BST<keyType, dataType>::traversep(node *r)
{
    if (r != NULL) //if tree if not empty
    {
        traversep(r->left); //call function pointing to the root of the left sub-tree
		cout << r->key << " " << r->data << " " << endl; //print key of r, then space, then data of r
        traversep(r->right); //call function pointing at the root of the right sub-tree
    }
    
}

//public function of inorder traversal
template <class keyType, class dataType>
void BST<keyType, dataType>::traverse()
{
    traversep(root); //call private function pointing at the root of BST
}

//public function of preorder traversal of BST
template <class keyType, class dataType>
void BST<keyType, dataType>::preorderFile(string filename, bool o)
{
    ofstream out; //declaring output stream
	if(!o) //bool indicating when true not to overwrite file
    out.open(filename); //overwriting will take place
	else
		out.open(filename,ios_base::app); //not to overwrite content of output file

    if (out.is_open()) //if file is opened
        preorderp(root, out); //call private fuction of preorder
    else //if file is not opened
        cout << "Error loading output file." << endl;
    out.close(); //close file
}

//level order traversal of BST
template <class keyType, class dataType>
void BST<keyType, dataType>::levelorder()
{
    queue <node*> q; //declare queue
    node* t = root; //declare node pointer to root
    if(root!=NULL) //if tree if not empty
        q.push(t); //push root into queue
		int n = q.size(); //n equals the size of the queue

    while (n>0)
    {
		
			t = q.front(); //t equals the front element of the queue
			q.pop(); //pop from queue
			n--; //decrement n
			cout << t->key << " " << t->data << endl; //output key of t, then space, then data of t
		
			if (t->left != NULL) //if there is  a left sub-tree
            {
				q.push(t->left); //add left child to queue
				n++; //increment n
			}
			if (t->right != NULL) //if there is  a right sub-tree
            {
				q.push(t->right); //add right child to queue
				n++; //increment n
			}
	
    }
    
}


//function that makes BST empty
template <class keyType, class dataType>
void BST<keyType, dataType>::empty()
{
    while (root != NULL) //while tree is not empty
       remove(root->key); //remove key of root
}


//destructor of BST
template <class keyType, class dataType>
BST<keyType, dataType> :: ~BST()
{
    empty(); //call empty
    root = NULL; //make root equals NULL
}


//return true if BST is empty
template <class keyType, class dataType>
bool BST<keyType, dataType>::isEmpty()
{
    if (root == NULL)
        return true;
    else
        return false;
}



//returns maximum data and coressponding key in a BST
template <class keyType, class dataType>
bool BST<keyType, dataType>::getMax(keyType & k, dataType & d)
{
	if (isEmpty()) //if BST is empty
		return false;
	else //if BST is not empty
	{
		int max = -100; //declare max and initialize it by a very small number
		node* entry; //delcare node pointer
		entry = root; //make pointer point to root of tree
		while (entry->right != NULL) //while there is a righ sub-tree
		{
			if (entry->data > max) //if data of entry is greater than variable max
			{
				max = entry->data; //maximum equls data of entry
				k = entry->key; //k equals key of entry
				d = entry->data; //d equals data of entry
			}
			entry = entry->right; //entry equals root of right sub-tree
		}
		entry = root; //make entry equals root again
		while (entry->left != NULL) //while left sub-tree of entry is not equal to null
		{
			if (entry->data > max) //if data of root is bigger than max
			{
				max = entry->data; //max gets data of entry
				k = entry->key; //k gets key of entry
				d = entry->data; //d gets data of entry
			}
			entry = entry->left; //entry equals root of left sub-truee
		}
		entry = root; //make root equals to entry
		if (entry->data > max) //if root had the greatest data
        {
			k = entry->key; //k equals key of root/entry
			d = entry->data; //d equals data of root/entry
		}
		return true;
	}
}



//get minimum data and corresponding key in a BST
template <class keyType, class dataType>
bool BST<keyType, dataType>::getMin(keyType & k, dataType & d)
{
	if (isEmpty()) //if BST is empty
		return false;
	else //if BST is not empty
	{
		int min = 1000000; //declare min and initialize it by a very big number
		node* entry; //delcare node pointer
		entry = root;//make pointer point to root of tree
		while (entry->right != NULL) //while there is a righ sub-tree
		{
			if (entry->data < min) //if data of entry is smaller than variable min
			{
				min = entry->data; //maximum equls data of entry
				k = entry->key; //k equals key of entry
				d = entry->data; //d equals data of entry
			}
			entry = entry->right; //entry shifts to node of righ sub-tree
		}
		entry = root; //entry gets root of BST
		while (entry->left != NULL) //if there if a left sub-tree
		{
			if (entry->data < min) //if entry of data is smaller than min
			{
				min = entry->data; //min gets data of entry
				k = entry->key; //k gets key of entry
				d = entry->data; //d gets data of entry
			}
			entry = entry->left; //entry equals root of left sub-tree
		}
		entry = root; //if entry equals root/minimum value is the root
		if (entry->data < min) //if data of entry/root is smaller than min
        {
			k = entry->key; //k gets key of entry
			d = entry->data; //d gets data of entry
		}
		return true;
	}
}


//returns node pointer to predecessor by reference
template <class keyType, class dataType>
void BST<keyType, dataType>::predecessor(node* &n, node* & pre)
{
	pre = n->left; //pre is the left child of n
	while (pre->right != NULL) //while there is a right sub-tree
	{
		pre = pre->right; //pre gets root of the right sub-tree of pre
	}
}

//returns node pointer to successor by reference, and parent of sucessor
template <class keyType, class dataType>
void BST<keyType, dataType>::successor(node* & n, node* & s, node*& p)
{
	p = n; //node p euquals node n
	if (n->right == NULL&&n->left != NULL) //if there is a right sub-tree and a left sub-tree to n
		s = n->left; //s is the left child of n
	else
	{
		s = n->right; //s if the right child of n
		if (n != NULL && n->right != NULL) //if n is not null, and it has a right sub-tree
			while (s->left != NULL) //do while s has a left sub-tree
			{
				p = s; //p gets s
				s = s->left; //s is its left sub-tree
			}
	}
}

//returs pointer to parent of node n by reference
template <class keyType, class dataType>
void BST<keyType, dataType>::getNodePar(node*& p, node* &n, keyType k)
{
	if (root == NULL)//tree is empty
	{
		p = NULL; //p is null
		n = NULL; //n is null
	}
	else //if tree is not empty
	{
		node* q = root; //declara a node pointer to root
		node* prev = NULL; //declare a pointer initialized with null
		bool found = false; //bool initialized with false
		while ((q != NULL) && (!found)) //while q is not null and bool is not false
		{
			if (q->key == k) //if key of q equals k
			{
				p = prev; //parent p is prev
				n = q; // node n gets q
				found = true; //bool is true
			}
			else if (q->key > k) //if key of q is greater than k
			{
				prev = q; //prev gets q
				q = q->left; //q is the root of the left sub-tree
			}
			else if ((q->key) < k) //if key of q is smaller than k
			{
				prev = q; //prev gets q
				q = q->right; //q is the root of the right sub-tree
			}
		}
	}
}

//function that removes a node
template <class keyType, class dataType>
bool BST<keyType, dataType>::remove(keyType k)
{
	node *n, *par, *suc, *sucPar;
	getNodePar(par, n, k);

	if (n == NULL)
		return false;

	//Node to delete is leaf
	if ((n->left == NULL) && (n->right == NULL))
	{
		//node is the left child of the parent
		if (par->left == n)
			par->left = NULL;
		//node is the parent's right child
		else
			par->right = NULL;
		delete n;
		return true;
	}
	//if node to delete is root with no right child
	else if ((n == root) && (n->right == NULL))
	{
		root = n->left;
		delete n;
		return true;
	}
	//if node to delete is root with no left child
	else if ((n == root) && (n->left == NULL))
	{
		root = n->right;
		delete n;
		return true;
	}
	else
	{
		successor(n, suc, sucPar);
		n->key = suc->key;
		n->data = suc->data;
		node *x;
		x = suc;
		//	getNodePar(sucPar, suc, suc->key);
		if (suc->right != NULL)
			sucPar->left = suc->right;
		else
			sucPar->left = NULL;
		delete x;
		return true;

	}

}
