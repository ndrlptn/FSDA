#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
struct key
{
	int school;
	int direction;
	int specialization;
};

struct Node
{
	Node* right;
	Node* left;
	Node* parent;
	int key1;
	int color;
	int string;

	Node(int _val) : key1(_val), right(nullptr), left(nullptr), parent(nullptr){}
};


struct tree
{
	tree* root;
	tree* right;
	tree* left;
	tree* parent;
	int color;
	int key1;
	int string;
	tree* nil;
	tree(int el,int string): right(nullptr),left(nullptr),key1(el),parent(nullptr),root(nullptr),nil(NULL), string(string) {}
	

	void dump3(tree * root1, int space=0)
	{
		if (root1==nullptr) //!current
			return;
		enum { COUNT = 2 };
		space += COUNT;
		dump3(root1->right,space);
		for (int i = COUNT; i < space; ++i)
			std::cout << "  ";
		std::cout <<root1->key1 <<" "<< root1->color << std::endl;
		dump3(root1->left,space);
	}


	/*void output_file(tree* root, ofstream outputFile)
	{
		if (root == nullptr)
		{
			outputFile.close();
			return;
		}
		output_file(root->right, outputFile);
	}*/

	int height(tree* root1)
	{
		if (root1 == nullptr) return 0;
		
		if(root1->color == 0) return 1 + std::max(height(root1->left), height(root1->right));
		else return std::max(height(root1->left), height(root1->right));
		
	}


	void fix_height(tree* z)
	{
		if (height(root->left) > height(root->right))
		{
			rotate_right(root);
		}
		else
		{
			if (height(root->left) < height(root->right))
			{
				rotate_left(root);
			}
		}
	}

	void fill(tree* z)
	{
		tree* y = nil;//
		tree* x = root;

		while (x != nil)//
		{
			y = x;
			if (z->key1 < x->key1)
				x = x->left;
			else x = x->right;
		}

		z->parent = y;
		if (y == nil)//
		{
			root = z;
			root->color = 0;
		}
		else {
			if (z->key1 < y->key1)
			{
				y->left = z;
				z->left = nil;
				z->right = nil;
				z->color = 1;
				if (z->parent->parent != nullptr and z->parent->parent->right != nullptr)
				{
					fix(z);
					fix_height(z);
				}
				else
					if (z->parent->color = 1) z->parent->color = 0;
			}
			else
			{
				y->right = z;
				z->left = nil;
				z->right = nil;
				z->color = 1;
				if (z->parent->parent != nullptr and z->parent->parent->left != nullptr)
				{
					fix(z);
					fix_height(z);
				}
				else
					if (z->parent->color = 1) z->parent->color = 0;
			}
		}
	}

	void fix(tree* z)
	{
		tree* y;
		while (z->parent != nullptr and z->parent->color == 1) //!!
		{
			if (z->parent == z->parent->parent->left)
			{
				y = z->parent->parent->right;
				if (y->color == 1)
				{
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						rotate_left(z);
					}

					else { //
						z->parent->color = 0;
						z->parent->parent->color = 1;
						rotate_right(z->parent->parent);
					}//
				}
			}
			else
			{
				if (z->parent == z->parent->parent->right)
				{
					y = z->parent->parent->left;
					if (y!= nullptr and y->color == 1) 
					{
						z->parent->color = 0;
						y->color = 0;
						z->parent->parent->color = 1;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							rotate_right(z);
						}

						else {//
							z->parent->color = 0;
							z->parent->parent->color = 1;
							rotate_left(z->parent->parent);
						}
					}
				}
			}

		}


		root->color = 0;
	}
	

	void rotate_left(tree* x)
	{
		tree* y = x->right;
		x->right = y->left;

		if (y->left != nil) //
			y->left->parent = x;
		y->parent = x->parent;

		if (x->parent == nil)//
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}



	void rotate_right(tree* x)
	{
		tree* y = x->left;
		x->left = y->right;

		if (y->right != nil)//
			y->right->parent = x;
		y->parent = x->parent;

		if (x->parent == nil)//
			root = y;
		else if (x->parent->right == x)
			x->parent->right = y;
		else 
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	tree* check_na_nullptr(tree* x, tree* y)
	{
		if (x != nil and y == nil) return x;
		else if (y != nil and x == nil) return y;
	}

	tree* search_el(int el,int str, tree* root)
	{
		if (root != nil) {
			if (root->key1 == el and root->string == str) return root;
			else {
				if (root->right != nil and root->right->key1 == el and root->string == str) return root->right;
				else
				{
					if (root->left != nil and root->left->key1 == el and root->string == str) return root->left;
					else
					{
						return check_na_nullptr(search_el(el,str, root->left), search_el(el, str, root->right));
					}
				}
			}
		}
	}

	void transplant(tree* u, tree* v)
	{
		if (u->parent == nil)
			root = v;
		else
		{
			if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
		}
		if (v!= nil)
			v->parent = u->parent;

	}

	void delete_el(tree* z)
	{
		tree* x;
		tree* y = z;
		int orig_color = y->color;
		if (z->left == nil)
		{
			x = z->right;
			transplant(z, z->right);
		}
		else
		{
			if (z->right == nil)
			{
				x = z->left;
				transplant(z, z->right);
			}
			else
			{
				y = maximus(z->left); ///alalala
				orig_color = y->color;
				x = y->left;
				if (x != nil and y->parent == z)  /////!!!!!!
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				if (z->left != nil)  //!!!!!!!!!!!!!!!!!!!!
				{
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
			}
		}
		if (orig_color == 0)
			delete_fix(x);
	}

	void delete_fix(tree* x)
	{
		tree* w;
		while (x != root and x->color == 0)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rotate_left(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == 0 and w->right->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->right->color == 0)
					{
						w->left->color = 0;
						w->color = 1;
						rotate_right(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->right->color = 0;
					rotate_left(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rotate_right(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == 0 and w->left->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->left->color == 0)
					{
						w->right->color = 0;
						w->color = 1;
						rotate_left(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->left->color = 0;
					rotate_right(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}


	tree* maximus(tree* root1)
	{
		if (root1 == nullptr) return nullptr;
		tree* r = maximus(root1->right);
		tree* l = maximus(root1->left);
		if (r == nullptr and l == nullptr) return root1;
		else
		{
			if (r != nullptr and l != nullptr)
			{
				if (r->key1 > l->key1) return r;
				else return l;
			}
			else 
			{
				if (r != nullptr and l == nullptr) return r;
				else return l;
			}
		}
		return root1;
	}
	


	void PostOrder_RBTree(tree* x, basic_ofstream<char> &file) {   // ПРОБЛЕМААА ПРОБЛЕМА ПРОБЛЕМА
		if (x != nil) {
			PostOrder_RBTree(x->left, file);
			PostOrder_RBTree(x->right, file);
			file << x->key1 << endl;
		}
		
	}
};


int main()
{
	//ofstream output_file;
	//output_file.open("output.txt");
	string path = "myfile.txt";
	auto t1 =  tree(0,0);
	int count = 0;


	ifstream fin;
	fin.open(path);

	string str;
	int number;
	while (!fin.eof())
	{
		count++;
		str = "";
		getline(fin, str);
		if (str != "")
		{
			number = stoi(str);
			auto t = new tree(number,count);
			t1.fill(t);
		}
	}

	fin.close();

	basic_ofstream<char> file;
	file.open("output.txt");
	//t1.delete_el(t1.search_el(2, 4 , t1.root));
	
	//t1.dump3(t1.root,0);

	//ofstream file;
	
	t1.PostOrder_RBTree(t1.root, file); // ПОВОД ПРОБЛЕМЫ ПОВОД ПРОБЛЕМЫ

	file.close();
	/*output_file << t1.PostOrder_RBTree(t1.root, " ") << endl;
	output_file.close();*/

	/*ofstream outputFile("output.txt");
	outputFile << t1.root->key1 << endl;
	outputFile.close();*/ //!!!!!!!!!!!!!!!!!!!!!!!!!1

	

	//std::cout << t1.search_el(7, 2, t1.root);
	//std::cout << t1.nil->parent;
	//std::cout << t1.maximus(t1.root->left->left)->key1;
	//std::cout << t1.maximus(t1.root->right)->key1;
	//std::cout << t1.search_el(9, t1.root)->parent->key1;
	//std::cout << t1.root->key1;
	
	
	return 0;
}