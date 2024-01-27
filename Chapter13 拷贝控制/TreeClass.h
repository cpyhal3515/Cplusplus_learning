#ifndef TREE
#define TREE

#include<iostream>
#include<string>
#include<vector>
#include<memory>

// TreeNode 定义行为像指针的类
class TreeNode
{
public:
	TreeNode() : value(std::string()), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(const TreeNode& orig) : value(orig.value), count(orig.count), left(orig.left), right(orig.right)
	{
		++*count;
	}
	TreeNode& operator=(const TreeNode&);

	~TreeNode();

private:
	std::string value;
	int* count;
	TreeNode* left;
	TreeNode* right;

};

TreeNode& TreeNode::operator=(const TreeNode& rhs)
{
	++*rhs.count;
	if (--*count == 0)
	{
		if (left)
		{
			delete left;
		}
		if (right)
		{
			delete right;
		}

		delete count;
	}
	
	value = rhs.value;
	count = rhs.count;
	left = rhs.left;
	right = rhs.right;

	return *this;

}

TreeNode::~TreeNode()
{
	if (--*count == 0)
	{
		if (left)
		{
			delete left;
			left = nullptr;
		}
		if (right)
		{
			delete right;
			right = nullptr;
		}
		delete count;
		count = nullptr;
	}
	
}


// BinStrTree 定义行为像值的类
class BinStrTree
{
public:
	BinStrTree() : root(new TreeNode()) {}

	BinStrTree(const BinStrTree& orig) : root(new TreeNode(*orig.root)) {}

	BinStrTree& operator=(const BinStrTree&);

	~BinStrTree() { delete root; };

private:
	TreeNode* root;

};

BinStrTree& BinStrTree::operator=(const BinStrTree& rhs)
{
	TreeNode* new_root = new TreeNode(*rhs.root);
	delete root;
	root = new_root;
	return *this;
}


#endif // STRBLOB