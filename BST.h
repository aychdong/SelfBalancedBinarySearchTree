#include <stddef.h>
class TreeNode
{
public:
	int val;
	int height;
	bool color; //0: black; 1:red
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;

	TreeNode(int x) : val(x), color(1), height(1),left(NULL), right(NULL), parent(NULL) {}
};

class BST
{
public:
	TreeNode* root;
	TreeNode* BSTSearch(int keyvalue, TreeNode *root);
	void BSTInsert(int keyvalue);
	void BSTDelete(int keyvalue);
	void BSTTraverse(TreeNode *root, int level);

	void SplayTreeRotate(TreeNode *node);
	TreeNode* SplayTreeSearch(int keyvalue);
	void SplayTreeInsert(int keyvalue);
	void SplayTreeDelete(int keyvalue);

	TreeNode* AVLLeftRotate(TreeNode *sub_root);
	TreeNode* AVLRightRotate(TreeNode *sub_root);
	TreeNode* AVLInsert(TreeNode *node, int keyvalue);
	TreeNode* AVLSearch(int keyvalue);
	TreeNode* AVLDelete(TreeNode *node, int keyvalue);

	void BST::RedBlackInsert(int keyvalue);
	TreeNode* RedBlackLeftRotate(TreeNode *sub_root);
	TreeNode* RedBlackRightRotate(TreeNode *sub_root);
	TreeNode* RedBlackSearch(int keyvalue);
	void RedBlackDelete(int keyvalue);

	BST()
	{
		root = NULL;
	}

};
