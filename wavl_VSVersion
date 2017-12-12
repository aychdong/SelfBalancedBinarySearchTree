// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
using std::cout;
using std::endl;

using namespace std;

template <typename T>
class WeakAVLTree
{
private:

	struct RankBalancedNode
	{
		T element;
		RankBalancedNode * left;
		RankBalancedNode * right;
		RankBalancedNode * parent;
		int rank;

		RankBalancedNode(const T & _element,
			RankBalancedNode * lt, RankBalancedNode * rt, RankBalancedNode * pa, int rv = 0)
			: element(_element), left(lt), right(rt), parent(pa), rank(rv) {}
	};

	int treeHeight(RankBalancedNode *node) {
		if (node == NULL) return 0;
		return (1 + max(treeHeight(node->left), treeHeight(node->right)));
	}


public:

	WeakAVLTree() {
		root = NULL;
		tree_size = 0;
	}
	WeakAVLTree(WeakAVLTree & rhs) {
		this->root = clone(rhs.root);
		this->tree_size = rhs.size();
	}
	~WeakAVLTree() {
		clear();
	}

	const WeakAVLTree & operator = (const WeakAVLTree & rhs) {
		if (this != &rhs) {
			this->clear();
			this->root = clone(rhs.root);
			this->tree_size = rhs.tree_size;
		}
		return (*this);
	}

	int size() const {
		return tree_size;
	}
	bool empty() const {
		return size() == 0;
	}
	bool contains(const T & x) const {
		return (contains(x, root) != NULL);
	}
	const T & findMin() const {
		if (empty())
		{
			//throw UnderflowException();
		}
		return findMin(root)->element;
	}
	const T & findMax() const {
		if (empty())
		{
			//throw UnderflowException();
		}
		return findMax(root)->element;
	}
	int getTreeHeight() {
		return treeHeight(root) - 1;
	}
	void clear() {
		clear(root);
		tree_size = 0;
		return;
	}
	void insert(const T & x) {
		if (contains(x)) {
			return;
		}
		++tree_size;
		insert(x, root);
		return;
	}
	void remove(const T & x) {
		if (!contains(x))
		{
			return;
		}
		--tree_size;
		remove(x, root);
		return;
	}

	void levelTraversal() {
		vector<RankBalancedNode *> curLevel;
		curLevel.push_back(root);
		while (curLevel.size()>0) {
			vector<RankBalancedNode *> nextLevel;
			for (int i = 0; i<curLevel.size(); i++) {
				if (curLevel[i]->parent != NULL)
					cout << "element: " << curLevel[i]->element << ", rank: " << curLevel[i]->rank << ", parent: " << curLevel[i]->parent->element << " ||";
				else
					cout << "element: " << curLevel[i]->element << ", rank: " << curLevel[i]->rank << ", parent: NULL";
				if (curLevel[i]->left != NULL) nextLevel.push_back(curLevel[i]->left);
				if (curLevel[i]->right != NULL) nextLevel.push_back(curLevel[i]->right);
			}
			curLevel = nextLevel;
			cout << endl;
		}
		cout << "---------------------------------------" << endl;
	}


private:

	RankBalancedNode * root;
	int tree_size;

	int getNodeRank(RankBalancedNode * node) const {
		if (node == NULL) {
			//Empty node has rank -1
			return -1;
		}
		return node->rank;
	}
	RankBalancedNode* contains(const T & x, RankBalancedNode * node) const {
		while (node != NULL) {
			if (x < node->element) {
				node = node->left;
			}
			else if (node->element < x) {
				node = node->right;
			}
			else {
				return node;
			}
		}
		return NULL;
	}
	RankBalancedNode * clone(RankBalancedNode * node) const {
		if (NULL == node) {
			return NULL;
		}
		return new RankBalancedNode(node->element,
			clone(node->left), clone(node->right), node->parent, getNodeRank(node));
	}
	RankBalancedNode * findMin(RankBalancedNode * node) const {
		if (node != NULL) {
			while (node->left != NULL) {
				node = node->left;
			}
		}
		return node;
	}
	RankBalancedNode * findMax(RankBalancedNode * node) const {
		if (node != NULL) {
			while (node->right != NULL) {
				node = node->right;
			}
		}
		return node;
	}
	void clear(RankBalancedNode * & node) {
		if (node != NULL) {
			clear(node->left);
			clear(node->right);
			delete node;
			node = NULL;
		}
	}
	void rotateRight(RankBalancedNode * & node) {
		RankBalancedNode * k = node->left;
		node->left = k->right;
		if (k->right != NULL) {
			k->right->parent = node;
		}
		k->parent = node->parent;
		if (node->parent == NULL) {
			root = k;
		}
		else if (node->parent->right == node) {
			//node is right child of its parent
			node->parent->right = k;
		}
		else {
			node->parent->left = k;
		}
		k->right = node;
		node->parent = k;
	}
	void rotateLeft(RankBalancedNode * & node) {
		RankBalancedNode * k = node->right;
		node->right = k->left;
		if (k->left != NULL) {
			k->left->parent = node;
		}
		k->parent = node->parent;
		if (node->parent == NULL) {
			root = k;
		}
		else if (node->parent->left == node) {
			//node is right child of its parent
			node->parent->left = k;
		}
		else {
			node->parent->right = k;
		}
		k->left = node;
		node->parent = k;
	}
	void insert(const T & x, RankBalancedNode * & input) {
		RankBalancedNode* node = input;
		if (NULL == node)
		{
			input = new RankBalancedNode(x, NULL, NULL, NULL, 0);
			return;
		}
		RankBalancedNode* parent;
		do {
			parent = node;
			if (node->element > x) {
				node = node->left;
			}
			else if (node->element < x) {
				node = node->right;
			}
			else
				return;
		} while (node != NULL);

		RankBalancedNode* newNode = new RankBalancedNode(x, NULL, NULL, parent, 0);
		if (parent->element > x) {
			parent->left = newNode;
		}
		else {
			parent->right = newNode;
		}

		if (parent->rank == 0) {
			parent->rank++;
			fixAfterInsert(parent);
		}

		return;
	}

	void fixAfterInsert(RankBalancedNode * & node) {
		for (RankBalancedNode *parent = node->parent;
			parent != NULL && node->rank == parent->rank; node->rank++) {
			if (parent->left == node) {
				//node is left child
				if (needRotateRight(parent)) {
					//double-rotate extra step
					if (node->left == NULL || node->rank >= node->left->rank + 2) {
						node->rank--;
						node->right->rank++;
						rotateLeft(node);
					}
					parent->rank--;
					rotateRight(parent);
					break;
				}
			}
			else {
				if (needRotateLeft(parent)) {
					if (node->right == NULL || node->rank >= node->right->rank + 2) {
						node->rank--;
						node->left->rank++;
						rotateRight(node);
					}
					parent->rank--;
					rotateLeft(parent);
					break;
				}
			}
			node = parent;
			parent = node->parent;
		}
	}

	bool needRotateRight(RankBalancedNode * & node) {
		if (node->right == NULL) {
			if (node->rank == 1) {
				return true;
			}
			return false;
		}
		else if (node->rank >= node->right->rank + 2) {
			return true;
		}
		return false;
	}

	bool needRotateLeft(RankBalancedNode * & node) {
		if (node->left == NULL) {
			if (node->rank == 1) {
				return true;
			}
			return false;
		}
		else if (node->rank >= node->left->rank + 2) {
			return true;
		}
		return false;
	}

	void remove(const T & x, RankBalancedNode * & input) {
		RankBalancedNode * node = contains(x, root);
		if (node == NULL) {
			return;
		}
		// If node has 2 child.
		if (node->left != NULL && node->right != NULL) {
			RankBalancedNode *predecessor = findMax(node->left);
			node->element = predecessor->element;
			node = predecessor;
		}
		RankBalancedNode *replacement = (node->left != NULL ? node->left : node->right);
		if (replacement != NULL) {
			//link replacement to parent
			replacement->parent = node->parent;
			RankBalancedNode *sibling = NULL;
			if (node->parent == NULL) {
				//this is the root
				root = replacement;
				return;
			}
			else if (node == node->parent->left) {
				// node is left child;
				node->parent->left = replacement;
				sibling = node->parent->right;
			}
			else {
				node->parent->right = replacement;
				sibling = node->parent->left;
			}

			node->left = node->right = node->parent = NULL;
			delete node;

			fixAfterRemove(replacement->parent, sibling, replacement);
		}
		else if (node->parent == NULL) {
			root = NULL;
		}
		else {
			//victim node has no child
			RankBalancedNode *victimParent = node->parent;
			RankBalancedNode *sibling = NULL;

			if (node == node->parent->left) {
				node->parent->left = NULL;
				sibling = node->parent->right;
			}
			else if (node == node->parent->right) {
				node->parent->right = NULL;
				sibling = node->parent->left;
			}
			node->parent = NULL;
			node->rank--;
			fixAfterRemove(victimParent, sibling, node);
		}
	}

	int rank(RankBalancedNode * & node) {
		return (node == NULL) ? -1 : node->rank;
	}

	bool isNode22(RankBalancedNode * & node) {
		if (node == NULL || node->rank == 0) {
			return false;
		}
		if (node->rank == 1) {
			if (node->left == NULL && node->right == NULL) {
				return true;
			}
			else
				return false;
		}
		else {
			return (node->left->rank == node->right->rank && node->left->rank + 2 == node->rank);
		}
	}

	void fixAfterRemove(RankBalancedNode * & parent, RankBalancedNode * & sibling, RankBalancedNode * & node) {
		int rankDiff = parent->rank - node->rank;
		//if (node->parent == NULL) delete node; //node is a leaf, should be delete.
		while (rankDiff == 3 || parent->rank == 1 && isNode22(parent)) {
			int rankDiffSibling = (sibling == NULL) ? parent->rank + 1 : parent->rank - sibling->rank;
			if (rankDiffSibling == 2) {
				parent->rank--;
			}
			else {
				int rankDiffSiblingLeft = sibling->rank - rank(sibling->left); // use function since that sibling->left could be NULL no rank
				int rankDiffSiblingRight = sibling->rank - rank(sibling->right);

				if (rankDiffSiblingLeft == rankDiffSiblingRight && rankDiffSiblingLeft == 2) {
					//demote parent & sibling
					parent->rank--;
					sibling->rank--;
				}
				else if (parent->right == sibling) {
					//sibling on the right
					if (rankDiffSiblingRight == 1) {
						// single rotation
						sibling->rank++;
						parent->rank--;
						if (sibling->left == NULL) {
							parent->rank--;
						}
						rotateLeft(parent);
					}
					else {
						//double rotation
						parent->rank -= 2;
						sibling->rank--;
						sibling->left->rank += 2;
						rotateRight(sibling);
						rotateLeft(parent);
					}
					break;
				}
				else {
					if (rankDiffSiblingLeft == 1) {
						// single rotation
						sibling->rank++;
						parent->rank--;
						if (sibling->right == NULL) {
							parent->rank--;
						}
						rotateRight(parent);
					}
					else {
						//double rotation
						parent->rank -= 2;
						sibling->rank--;
						sibling->right->rank += 2;
						rotateLeft(sibling);
						rotateRight(parent);
					}
					break;
				}
			}
			if (parent->parent == NULL)
				return;
			RankBalancedNode * newNode = parent;
			parent = newNode->parent;
			sibling = (parent->left == newNode) ? parent->right : parent->left;
			rankDiff = parent->rank - newNode->rank;
		}
	}
};

int main()
{
	DWORD tStart;
	DWORD tEnd;
	int numLoop = 1000000;
	vector<int> numList;
	for (int i = 0; i<numLoop; i++)
		numList.push_back(i);
	vector<int> numList2 = numList;
	random_shuffle(numList.begin(), numList.end());
	random_shuffle(numList2.begin(), numList2.end());
	WeakAVLTree<int> test;
	tStart = GetTickCount();
	for (int i = 0; i<numLoop;i++) {
		test.insert(numList[i]);
	}
	tStart = GetTickCount();
	for (int j = 0; j<numLoop/20;j++) {
		test.remove(numList2[j]);
	}
	tEnd = GetTickCount();
	cout << tEnd - tStart << endl;
	/*
	test.insert(1);
	test.levelTraversal();
	test.insert(2);
	test.levelTraversal();
	test.insert(3);
	test.levelTraversal();
	test.insert(4);
	test.levelTraversal();
	test.insert(5);
	test.levelTraversal();
	test.insert(6);
	test.levelTraversal();
	test.insert(7);
	test.levelTraversal();
	test.insert(8);
	test.levelTraversal();
	test.insert(9);
	test.levelTraversal();
	test.remove(5);
	test.levelTraversal();
	test.remove(3);
	test.levelTraversal();
	test.remove(1);
	test.levelTraversal();
	*/
	cout << "Hello world!" << endl;
	return 0;
}



