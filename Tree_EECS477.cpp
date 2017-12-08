#include "BST.h"
#include <vector>

#include <iostream>

using namespace std;

int height(TreeNode *node)
{
	if (!node) return 0;
	else
	{
		return node->height;
	}
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int HeightDiff(TreeNode *node)
{
	if (!node)
		return 0;
	return height(node->left) - height(node->right);
}


TreeNode* BST::BSTSearch(int keyvalue, TreeNode *root) 
{
	if (!root)
	{
		return NULL;
	}
	else if (root->val == keyvalue)
	{
		return root;
	}
	else
	{
		if (keyvalue > root->val)
			return BST::BSTSearch(keyvalue, root->right);
		else
			return BST::BSTSearch(keyvalue, root->left);
	}
}

void BST::BSTInsert(int keyvalue)
{
	if (!BSTSearch(keyvalue, root))
	{
		TreeNode *p_pre = NULL;
		TreeNode *p = root;
		TreeNode *toBeInserted = new TreeNode(keyvalue);

		if (!root)
		{
			root = toBeInserted;
			//cout << "create a tree with root " << keyvalue << endl;
		}
		else
		{
			while (p != NULL)
			{
				p_pre = p;
				if (keyvalue > p->val)
					p = p->right;
				else
					p = p->left;
			}

			if (keyvalue > p_pre->val)
			{
				p_pre->right = toBeInserted;
				//cout << keyvalue << " is inserted into the right of " << p_pre->val << endl;
			}
			else
			{
				p_pre->left = toBeInserted;
				//cout << keyvalue << " is inserted into the left of " << p_pre->val << endl;
			}
		}
	}
}

void BST::BSTDelete(int keyvalue)
{
	TreeNode *p_pre = NULL;
	TreeNode *p = root;
	TreeNode *toBeDeleted = new TreeNode(keyvalue);

	if (!root)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	else
	{
		while (p != NULL && p->val != keyvalue)
		{
			p_pre = p;

			if (keyvalue > p->val)
				p = p->right;
			else if (keyvalue < p->val)
				p = p->left;
		}

		if (!p)
		{
			cout << "Can not find node to be deleted" << endl;
			return;
		}
		else
		{
			if (!p->left && !p->right)
			{
				if (!p_pre)
					root = NULL;				
				else if (p_pre->val < keyvalue)
					p_pre->right = NULL;
				else
					p_pre->left = NULL;
			}
			else if (!p->right)
			{
				if (!p_pre)
					root = p->left;
				else
					p_pre->left = p->left;
			}
			else if (!p->left)
			{
				if (!p_pre)
					root = p->right;
				else
					p_pre->right = p->right;
			}
			else
			{
				TreeNode *rightSubtree = p->right;
				
				if (!p_pre)
					root = p->left;
				else
				{
					if (p_pre->val < keyvalue)
						p_pre->right = p->left;
					else
						p_pre->left = p->left;
				}
				p = p->left;
				while (p->right != NULL)
					p = p->right;				
				p->right = rightSubtree;
			}
		}
	}
}

void BST::BSTTraverse(TreeNode* node, int level)
{
	if (!node)
	{
		cout << "Tree is empty" << endl;
		return;
	}

	if (node->left != NULL)
		BST::BSTTraverse(node->left, level + 1);

	cout << node->val <<"("<<level<<(node->color?"red":"black")<<"|parent:"<<(node->parent?node->parent->val:-1)<<")	";

	if (node->right != NULL)
		BST::BSTTraverse(node->right, level + 1);
}

void BST::SplayTreeRotate(TreeNode *node)
{
	TreeNode *p_pre_pre = NULL;
	TreeNode *p_pre = NULL;
	TreeNode *p = root;
	vector<TreeNode*> PathNodeVector;

	if (!root)
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		while (p != NULL && p->val != node->val)
		{
			//p_pre_pre = p_pre;
			//p_pre = p;
			PathNodeVector.push_back(p);
			if (node->val > p->val)
				p = p->right;
			else if (node->val < p->val)
				p = p->left;
		}
		if (p->val != node->val)
			cout << "node not in the tree" << endl;
		else
		{
			while (!PathNodeVector.empty() && PathNodeVector.back() != root)
			{
				p_pre = PathNodeVector.back();
				PathNodeVector.pop_back();
				p_pre_pre = PathNodeVector.back();
				PathNodeVector.pop_back();
				if (p_pre_pre->val > p_pre->val && p_pre->val > p->val) //zig-zig
				{
					cout << "zig-zig: p_pre: " << p_pre->val << " p_pre_pre: " << p_pre_pre->val << endl;
					p_pre_pre->left = p_pre->right;
					p_pre->right = p_pre_pre;
					p_pre->left = p->right;
					p->right = p_pre;
					//root = node;
				}
				else if (p_pre_pre->val < p_pre->val && p_pre->val < p->val)//zag-zag
				{
					cout << "zag-zag: p_pre: " << p_pre->val << " p_pre_pre: " << p_pre_pre->val << endl;
					p_pre_pre->right = p_pre->left;
					p_pre->left = p_pre_pre;
					p_pre->right = p->left;
					p->left = p_pre;
					//root = node;
				}
				else if (p_pre_pre->val > p_pre->val && p_pre->val < p->val)//zig-zag
				{
					cout << "zig-zag: p_pre: " << p_pre->val << " p_pre_pre: " << p_pre_pre->val << endl;
					p_pre->right = p->left;
					p->left = p_pre;
					p_pre_pre->left = p->right;
					p->right = p_pre_pre;
					//root = node;
				}
				else
				{
					cout << "zag-zig: p_pre: " << p_pre->val << " p_pre_pre: " << p_pre_pre->val << endl;
					p_pre->left = p->right;
					p->right = p_pre;
					p_pre_pre->right = p->left;
					p->left = p_pre_pre;
					//root = node;
				}

			}
			if (PathNodeVector.empty()) //single node, do nothing
			{
				root = p;
				cout << "rotate end" << endl;
			}
			else  //zig
			{
				p_pre = PathNodeVector.back();
				if (root->val > node->val)
				{
					cout << "zig: p_pre: " << p_pre->val << endl;
					p_pre->left = node->right;
					node->right = p_pre;
					root = node;
				}
				else
				{
					cout << "zag: p_pre: " << p_pre->val << endl;
					p_pre->right = node->left;
					node->left = p_pre;
					root = node;
				}
			}
		}
	}
}

TreeNode* BST::SplayTreeSearch(int keyvalue)
{
	TreeNode* foundNode = BST::BSTSearch(keyvalue, root);
	if (foundNode)
	{
		BST::SplayTreeRotate(foundNode);
		return root;
	}
	else
		return NULL;
}

void BST::SplayTreeInsert(int keyvalue)
{
	BST::BSTInsert(keyvalue);
	BST::SplayTreeSearch(keyvalue);
}

void BST::SplayTreeDelete(int keyvalue)
{
	TreeNode *p_pre = NULL;
	TreeNode *p = root;
	TreeNode *toBeDeleted = new TreeNode(keyvalue);

	if (!root)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	else
	{
		while (p != NULL && p->val != keyvalue)
		{
			p_pre = p;

			if (keyvalue > p->val)
				p = p->right;
			else if (keyvalue < p->val)
				p = p->left;
		}

		if (!p)
		{
			cout << "Can not find node to be deleted" << endl;
			return;
		}
		else
		{
			if (!p->left && !p->right)
			{
				if (p_pre == NULL)
					root = NULL;
				else if (p_pre->val < keyvalue)
					p_pre->right = NULL;
				else
					p_pre->left = NULL;
			}
			else if (!p->right)
			{
				if (!p_pre)
					root = p->left;
				else
					p_pre->left = p->left;
			}
			else if (!p->left)
			{
				if (!p_pre)
					root = p->right;
				else
					p_pre->right = p->right;
			}
			else
			{
				TreeNode *rightSubtree = p->right;

				if (!p_pre)
					root = p->left;
				else
				{
					if (p_pre->val < keyvalue)
						p_pre->right = p->left;
					else
						p_pre->left = p->left;
				}
				p = p->left;
				while (p->right != NULL)
					p = p->right;
				p->right = rightSubtree;
			}
		}
	}
	if (p_pre)
		BST::SplayTreeRotate(p_pre);
}

TreeNode* BST::AVLRightRotate(TreeNode *sub_root)
{
	TreeNode *LeftChild;
	LeftChild = sub_root->left;
	sub_root->left = LeftChild->right;
	LeftChild->right = sub_root;

	sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
	LeftChild->height = max(height(LeftChild->left), height(LeftChild->right)) + 1;
	return LeftChild;
}

TreeNode* BST::AVLLeftRotate(TreeNode *sub_root)
{
	TreeNode *RightChild;
	RightChild = sub_root->right;
	sub_root->right = RightChild->left;
	RightChild->left = sub_root;

	sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
	RightChild->height = max(height(RightChild->left), height(RightChild->right)) + 1;
	return RightChild;
}

TreeNode* BST::AVLInsert(TreeNode *node, int keyvalue)
{
	if (!node)
	{
		return (new TreeNode(keyvalue));
	}

	if (keyvalue < node->val)
		node->left = BST::AVLInsert(node->left, keyvalue);
	else if (keyvalue > node->val)
		node->right = BST::AVLInsert(node->right, keyvalue);
	else
		return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int heightDiff = HeightDiff(node);

	if (heightDiff >= 2 && keyvalue < node->left->val)
	{
		cout << "LL case, unbalanced point is " << node->val<< endl;
		return BST::AVLRightRotate(node);
	}
	else if (heightDiff <= -2 && keyvalue > node->right->val)
	{
		cout << "RR case, unbalanced point is " << node->val << endl;
		return BST::AVLLeftRotate(node);
	}
	else if (heightDiff >= 2 && keyvalue > node->left->val)
	{
		cout << "LR case, unbalanced point is " << node->val << endl;
		node->left = BST::AVLLeftRotate(node->left);
		return BST::AVLRightRotate(node);
	}
	else if (heightDiff <= -2 && keyvalue < node->right->val)
	{
		cout << "RL case, unbalanced point is " << node->val << endl;
		node->right = BST::AVLRightRotate(node->right);
		return BST::AVLLeftRotate(node);
	}
	else 
		return node;	
}

TreeNode* BST::AVLSearch(int keyvalue)
{
	return BST::BSTSearch(keyvalue, root);
}

TreeNode* BST::AVLDelete(TreeNode *node, int keyvalue)
{
	if (!node) return NULL;

	if (keyvalue < node->val)
	{
		node->left = BST::AVLDelete(node->left, keyvalue);
		if (HeightDiff(node) <= -2)
		{
			if (HeightDiff(node->right) <= 0)
				node = BST::AVLLeftRotate(node);
			else
			{
				node->right = BST::AVLRightRotate(node->right);
				node = BST::AVLLeftRotate(node);
			}
		}
	}
	else if (keyvalue > node->val)
	{
		node->right = BST::AVLDelete(node->right, keyvalue);
		if (HeightDiff(node) >= 2)
		{
			if (HeightDiff(node->left) >= 0)
				node = BST::AVLRightRotate(node);
			else
			{
				node->left = BST::AVLLeftRotate(node->left);
				node = BST::AVLRightRotate(node);
			}
		}
	}
	else if (keyvalue == node->val)
	{
		if (HeightDiff(node) > 0)
		{
			TreeNode* p = node->left;
			if (!p)
				return node->right;
			TreeNode* pre = node;
			while (p->right)
			{
				pre = p;
				p = p->right;
			}
			node->val = p->val;
			node->left = BST::AVLDelete(node->left, node->val);
		}
		else
		{
			TreeNode* p = node->right;
			if (!p)
				return node->left;
			TreeNode* pre = node;
			while (p->left)
			{
				pre = p;
				p = p->left;
			}
			node->val = p->val;
			node->right = BST::AVLDelete(node->right, node->val);
		}	
	}

	node->height = 1 + max(height(node->left), height(node->right));

	return node;
}

TreeNode* BST::RedBlackLeftRotate(TreeNode *sub_root)
{
	cout << "rbt left rot" << endl;
	TreeNode *RightChild;
	RightChild = sub_root->right;	
	sub_root->right = RightChild->left;
	if (RightChild->left)
		RightChild->left->parent = sub_root;

	RightChild->left = sub_root;
	sub_root->parent = RightChild;

	sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
	RightChild->height = max(height(RightChild->left), height(RightChild->right)) + 1;
	return RightChild;
}

TreeNode* BST::RedBlackRightRotate(TreeNode *sub_root)
{
	cout << "rbt right rot" << endl;
	TreeNode *LeftChild;
	LeftChild = sub_root->left;
	sub_root->left = LeftChild->right;
	if (LeftChild->right)
		LeftChild->right->parent = sub_root;

	LeftChild->right = sub_root;
	sub_root->parent = LeftChild;

	sub_root->height = max(height(sub_root->left), height(sub_root->right)) + 1;
	LeftChild->height = max(height(LeftChild->left), height(LeftChild->right)) + 1;
	return LeftChild;
}

void BST::RedBlackInsert(int keyvalue)
{
	if (!BSTSearch(keyvalue, root))
	{
		TreeNode *p_pre = NULL;
		TreeNode *p = root;
		TreeNode *t = NULL;
		TreeNode *toBeInserted = new TreeNode(keyvalue);

		if (!root)
		{
			root = toBeInserted;
			root->color = 0;
			root->parent = NULL;
			//cout << "create a tree with root " << keyvalue << endl;
		}
		else
		{
			while (p != NULL)
			{
				p_pre = p;
				if (keyvalue > p->val)
					p = p->right;
				else
					p = p->left;
			}
	
			if (keyvalue > p_pre->val)
			{
				p_pre->right = toBeInserted;
				p_pre->right->parent = p_pre;
			}
			else
			{
				p_pre->left = toBeInserted;
				p_pre->left->parent = p_pre;
			}
			t = toBeInserted;

			if (p_pre->color == 1)				
			{
				while (t->val != root->val && t->parent->color == 1 && t->color == 1)
				{
					if (t->parent->val < t->parent->parent->val)
					{
						if (t->parent->parent->right && t->parent->parent->right->color == 1)
						{
							t->parent->color = 0;
							t->parent->parent->right->color = 0;
							t->parent->parent->color = 1;
							t = t->parent->parent;
						}
						else 
						{
							if (t->val > t->parent->val)
							{
								TreeNode* NodeAxis = t->parent;
								TreeNode* NodeParent = t->parent->parent;
								TreeNode* NodeAfterRotate = BST::RedBlackLeftRotate(NodeAxis);
								NodeParent->left = NodeAfterRotate;
								NodeAfterRotate->parent = NodeParent;
								t = NodeAfterRotate->left;
							}
							else 
							{
								TreeNode* NodeAxisPre = t->parent->parent->parent;
								t->parent->color = 0;
								t->parent->parent->color = 1;
								TreeNode* NodeAxis = t->parent->parent;
								t = BST::RedBlackRightRotate(NodeAxis);

								if (NodeAxisPre)
								{
									if (NodeAxisPre->val < t->val)
										NodeAxisPre->right = t;
									else
										NodeAxisPre->left = t;
									t->parent = NodeAxisPre;
								}
								else
								{
									root = t;
									root->parent = NULL;
								}
							}
						}					
					}
					else
					{
						if (t->parent->parent->left && t->parent->parent->left->color == 1)
						{
							t->parent->color = 0;
							t->parent->parent->left->color = 0;
							t->parent->parent->color = 1;
							t = t->parent->parent;
						}
						else
						{
							if (t->val < t->parent->val)
							{
								TreeNode* NodeAxis = t->parent;
								TreeNode* NodeParent = t->parent->parent;
								TreeNode* NodeAfterRotate = BST::RedBlackRightRotate(NodeAxis);
								NodeParent->right = NodeAfterRotate;
								NodeAfterRotate->parent = NodeParent;
								t = NodeAfterRotate->right;
							}
							else
							{
								TreeNode* NodeAxisPre = t->parent->parent->parent;
								t->parent->color = 0;
								t->parent->parent->color = 1;
								TreeNode* NodeAxis = t->parent->parent;
								t = BST::RedBlackLeftRotate(NodeAxis);

								if (NodeAxisPre)
								{
									if (NodeAxisPre->val < t->val)
										NodeAxisPre->right = t;
									else
										NodeAxisPre->left = t;
									t->parent = NodeAxisPre;
								}
								else
								{
									root = t;
									root->parent = NULL;
								}
							}
						}
					}
				}
				root->color = 0;

			}


		}
	}
}

TreeNode* BST::RedBlackSearch(int keyvalue)
{
	return BST::BSTSearch(keyvalue, root);
}

void BST::RedBlackDelete(int keyvalue)
{
	TreeNode *p_pre = NULL;
	TreeNode *p = root;
	int deleteColor = 0;

	if (!root)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	else
	{
		while (p != NULL && p->val != keyvalue)
		{
			p_pre = p;

			if (keyvalue > p->val)
				p = p->right;
			else if (keyvalue < p->val)
				p = p->left;
		}

		if (!p)
		{
			cout << "Can not find node to be deleted" << endl;
			return;
		}
		else
		{
			if (!p->left && !p->right)
			{
				//cout << "delete 00:" << p->val << endl;
				deleteColor = 0;
				if (!p_pre)
					root = NULL;
				else if (p_pre->val < keyvalue)
					p_pre->right = NULL;
				else
					p_pre->left = NULL;
				p = NULL;
			}
			else if (!p->right)
			{
				//cout << "delete 10:" << p->val << endl;
				if (!p_pre)
				{
					root = p->left;
					root->parent = NULL;
				}
				else
				{
					if (p->val > p_pre->val)
					{
						p_pre->right = p->left;
						p->left->parent = p_pre;
					}
					else
					{
						p_pre->left = p->left;
						p->left->parent = p_pre;
					}
				}
				p = p->left;
				deleteColor = p->color;
			}
			else if (!p->left)
			{
				//cout << "delete 01:" << p->val << endl;
				if (!p_pre)
				{
					root = p->right;
					root->parent = NULL;
				}
				else
				{
					if (p->val > p_pre->val)
					{
						p_pre->right = p->right;
						p->right->parent = p_pre;
					}
					else
					{
						p_pre->left = p->right;
						p->right->parent = p_pre;
					}
				}
				
				p = p->right;
				deleteColor = p->color;
			}
			else
			{	
				//cout << "delete 11:" << p->val << endl;
				TreeNode* pp = p->left;
				p_pre = p;
				//TreeNode* pret = p;
				while (pp)
				{
					while (pp->right)
						pp = pp->right;

					p->val = pp->val;
					p = pp;
					p_pre = p->parent;
					pp = pp->left;
				}

				if (p_pre->val < p->val)
					p->parent->right = NULL;
				else
					p->parent->left = NULL;
				deleteColor = p->color;
				p = NULL;
			}
		}
		
		while ((!p || p != root) && (!p || !p->color))
		{

			if (deleteColor)
			{
				if (p)
					p->color = 0;
				break;
			}


			//cout << "p:" << p->val << "|(" << (p->color ? "red" : "black") << ")" << endl;
			if (p == root)
				break;
			
			
			if (p == p_pre->left)
			{
				if (deleteColor == 0 && (!p || !p->color) && p != root && p_pre->right && p_pre->right->color)
				{
					cout << "left: condition 1" << endl;
					p_pre->color = 1;
					p_pre->right->color = 0;
				}
				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->right || (!p_pre->right->color &&
					(!p_pre->right->left || !p_pre->right->left->color) &&
						(!p_pre->right->right || !p_pre->right->right->color))))
				{
					cout << "left: condition 2" << endl;
					if (p_pre->right)
						p_pre->right->color = 1;
					p = p_pre;
					p_pre = p_pre->parent;
				}

				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->right || (!p_pre->right->color &&
					(p_pre->right->left && p_pre->right->left->color) &&
						(!p_pre->right->right || !p_pre->right->right->color))))
				{
					cout << "left: condition 3" << endl;
					p_pre->right->color = 1;
					if (p_pre->right->left)
						p_pre->right->left->color = 0;

					TreeNode *temp_p = p_pre;
					temp_p->right = BST::RedBlackRightRotate(p_pre->right);
					temp_p->right->parent = temp_p;
					p_pre = temp_p;
				}

				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->right || (!p_pre->right->color &&
					(p_pre->right->right && p_pre->right->right->color))))
				{
					cout << "left: condition 4" << endl;
					p_pre->right->color = p_pre->color;
					p_pre->color = 0;
					if (p_pre->right->right)
						p_pre->right->right->color = 0;

					if (!p_pre->parent)
						root = BST::RedBlackLeftRotate(p_pre);
					else
					{
						if (p_pre->parent->val < p_pre->val)
						{
							TreeNode *temp_p = p_pre->parent;
							temp_p->right = BST::RedBlackLeftRotate(p_pre);
							temp_p->right->parent = temp_p;
						}
						else
						{
							TreeNode *temp_p = p_pre->parent;
							temp_p->left = BST::RedBlackLeftRotate(p_pre);
							temp_p->left->parent = temp_p;
						}
					}
					break;
				}
			}

			else
			{
				if (deleteColor == 0 && (!p || !p->color) && p != root &&p_pre->left && p_pre->left->color)
				{
					cout << "right: condition 1" << endl;
					p_pre->color = 1;
					p_pre->left->color = 0;
				}
				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->left || (!p_pre->left->color && 
					(!p_pre->left->left || !p_pre->left->left->color) &&
						(!p_pre->left->right || !p_pre->left->right->color))))
				{
					cout << "right: condition 2" << endl;
					if (p_pre->left)
						p_pre->left->color = 1;
					p = p_pre;
					p_pre = p_pre->parent;
				}

				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->left || (!p_pre->left->color &&
					(p_pre->left->left && p_pre->left->left->color) &&
						(!p_pre->left->right || !p_pre->left->right->color))))
				{
					cout << "right: condition 3" << endl;
					p_pre->left->color = 1;
					if (p_pre->left->left)
						p_pre->left->left->color = 0;

					TreeNode *temp_p = p_pre;
					temp_p->left = BST::RedBlackLeftRotate(p_pre->left);
					temp_p->left->parent = temp_p;
					p_pre =temp_p;
				}

				if (deleteColor == 0 && (!p || !p->color) && p != root
					&& (!p_pre->left || (!p_pre->left->color &&
					(p_pre->left->right && p_pre->left->right->color))))
				{
					cout << "right: condition 4" << endl;
					p_pre->left->color = p_pre->color; 
					p_pre->color = 0;
					if (p_pre->left->left)
						p_pre->left->left->color = 0;

					if (!p_pre->parent)
						root = BST::RedBlackRightRotate(p_pre);
					else
					{
						if (p_pre->parent->val < p_pre->val)
						{
							TreeNode *temp_p = p_pre->parent;
							temp_p->right = BST::RedBlackRightRotate(p_pre);
							temp_p->right->parent = temp_p;
						}
						else
						{
							TreeNode *temp_p = p_pre->parent;
							temp_p->left = BST::RedBlackRightRotate(p_pre);
							temp_p->left->parent = temp_p;
						}
					}
					break;
				}
			}

			if (p && p->color)
				deleteColor = 1;
			else
				deleteColor = 0;
		}

		if (deleteColor)
		{
			if (p)
				p->color = 0;
		}

	}
}

int main()
{

	//int a[13] = { 34, 18, 76, 13, 12,11, 52,82, 16, 67, 58, 73, 72 };
	//int a[5] = { 22,18,26,14,20 };
	//int a[10] = { 7,2,11,0,5,8,14,4,1,15};
	int a[20] = { 12,1,9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17 };
	BST bstree;

	for (int i = 0; i < 20; i++)
	{
		cout << "adding " << i << "th point:" <<a[i] << endl;
		bstree.RedBlackInsert(a[i]);
		bstree.BSTTraverse(bstree.root, 0);
		cout << endl;
	}
	bstree.BSTTraverse(bstree.root, 0);
	for (int i = 0; i < 20; i++)
	{
		cout << "DELETE " << i << "th point:" << a[i] <<endl;
		bstree.RedBlackDelete(a[i]);
		bstree.BSTTraverse(bstree.root, 0);
		cout << endl;
	}
	//cout << "begin to delete:" << endl;
	//bstree.RedBlackDelete(2);
	//bstree.BSTTraverse(bstree.root, 0);


/*	
	for (int i = 0; i < 13; i++)
	{
		bstree.BSTInsert(a[i]);
		cout << "depth of tree is " << bstree.GetDepth(bstree.root) << endl;
	}
	
	if (!bstree.BSTSearch(1, bstree.root))
		cout << "Point not in the tree" << endl;
	else
		cout << "Point in the tree" << endl;

	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;

	bstree.BSTDelete(34);
	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;

	bstree.SplayTreeRotate(bstree.BSTSearch(67,bstree.root));
	cout << bstree.root->val << endl;
	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;
	
	if (bstree.SplayTreeSearch(73) != NULL)
		cout << "point in the tree" << endl;
	else
		cout << "point not in the tree" << endl;
	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;
	
	bstree.SplayTreeInsert(32);
	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;
	cout << "depth of tree is " << bstree.GetDepth(bstree.root) << endl;

	bstree.SplayTreeDelete(32);
	bstree.BSTTraverse(bstree.root, 0);
	cout << endl;
	cout << "depth of tree is " << bstree.GetDepth(bstree.root) << endl;
*/	
	return 0;
}




