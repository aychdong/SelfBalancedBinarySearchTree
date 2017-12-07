#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

template <typename T>
class SizeBalancedTree{
	private:
		struct TreeNode{
			T value;
			TreeNode* left;
			TreeNode* right;
			int nodeSize;

			TreeNode(const T & _value, TreeNode* _left, TreeNode* _right, int _size = 1)
			: value(_value), left(_left), right(_right), nodeSize(_size) {}
		};

		TreeNode * root;
		int size;

		int getNodeSize(TreeNode * node) const{
			if (node == NULL){
				return 0;
			}
			return node->nodeSize;
		}

		bool contains(const T & x, TreeNode* node) const{
			while(node != NULL){
				if (x < node->value){
					node = node->left;
				}
				else if (x > node->value){
					node = node->right;
				}
				else{
					return true;
				}
			}
			return false;
		}

		TreeNode* clone(TreeNode * node) const {
			if (node == NULL){
				return NULL;
			}
			return new TreeNode(node->value, clone(node->left), clone(node->right));
		}

		TreeNode* findMin(TreeNode* node) const{
			if (node != NULL){
				while (node->left != NULL){
					node = node->left;
				}
			}
			return node;
		}

		TreeNode* findMax(TreeNode* node) const {
			if (node != NULL){
				while (node->right != NULL){
					node = node->right;
				}
			}
			return node;
		}

		int rank(const T & x, TreeNode* node) const{
			int curRank = 0;
			while(node != NULL){
				if ( x < node->value){
					node = node->left;
				}
				else if(x<node->value){
					curRank+=(getNodeSize(node->left)+1);
					node = node->right;
				}
				else{
					curRank+=getNodeSize(node->left);
					break;
				}
			}
			return curRank;
		}

		TreeNode* select(int inputRank, TreeNode* node) const {
			while(node!= NULL){
				if (inputRank<getNodeSize(node->left)){
					node = node->left;
				}
				else if (inputRank > getNodeSize(node->left)){
					inputRank = inputRank - getNodeSize(node->left) - 1;
					node = node->right;
				}
				else{
					break;
				}
			}
			return node;
		}

		void clear(TreeNode * &node){
			if(node!=NULL){
				clear(node->left);
				clear(node->right);
				delete node;
				node = NULL;
			}
		}

		void rightRotate(TreeNode * & node){
			TreeNode* k = node->left;
			node->left = k->right;
			k->right = node;
			k->nodeSize = getNodeSize(node);
			node->nodeSize = getNodeSize(node->left)+getNodeSize(node->right)+1;
			node = k;
		}

		void leftRotate(TreeNode * & node){
			TreeNode* k = node->right;
			node->right = k->left;
			k->left = node;
			k->nodeSize = getNodeSize(node);
			node->nodeSize = getNodeSize(node->left)+getNodeSize(node->right)+1;
			node = k;
		}

		void maintain(TreeNode* & node, bool flag){
			//levelTraversal();
		    cout<<"maintain"<<node->value<<endl;
			if (flag ==false){
                //cout<<"flag == false"<<endl;
                if (node->left != NULL){
					if (getNodeSize(node->left->left)>getNodeSize(node->right)){
						rightRotate(node);
					}
					else if (getNodeSize(node->left->right)>getNodeSize(node->right)){
						leftRotate(node->left);
						rightRotate(node);
					}
					else return;
				}
				else 
					return;
			}
			else {
				if(node->right != NULL){
					//cout<<"flag == true"<<endl;
					if (getNodeSize(node->right->right)>getNodeSize(node->left)){
						leftRotate(node);
					}
					else if (getNodeSize(node->right->left)>getNodeSize(node->left)){
						rightRotate(node->right);
						leftRotate(node);
					}
					else return;
				}
				else 
					return;
			}
			//levelTraversal();
			cout<<"Did something"<<endl;
			if (node->left != NULL)
				maintain(node->left, false);
			if (node->right != NULL)
				maintain(node->right, true);
			maintain(node, true);
			maintain(node, false);
		}

		void simpleInsert(const T & x, TreeNode* & node){
			if (node==NULL){
				node = new TreeNode(x, NULL, NULL);
				return;
			}
			node->nodeSize++;
			if (node->value > x){
				simpleInsert(x, node->left);
			}
			else if (node->value < x){
				simpleInsert(x, node->right);
			}
			return;
		}
		void insert(const T & x, TreeNode * & node){
			if (node==NULL){
                //cout<<"&&"<<endl;
				node = new TreeNode(x, NULL, NULL);
                //cout<<"create finished"<<endl;
				return;
			}
			node->nodeSize++;
			if (node->value > x){
				//simpleInsert(x, node->left);
                //cout<<"!!"<<endl;
				insert(x, node->left);
			}
			else if (node->value < x){
                // /cout<<"@@"<<endl;
				//simpleInsert(x, node->right);
				insert(x, node->right);
			}
			else{
				return;
			}
			maintain(node, x >= node->value);
		}

		void deletion(const T & x, TreeNode * & node)
        {
            if (node ==NULL){
                return;
            }
            node->nodeSize--;
            if (x < node->value){
                deletion(x, node->left);
            }
            else if (x >node->value){
                deletion(x, node->right);
            }
            else{
                if (node->left != NULL && node->right != NULL){
                    if (getNodeSize(node->left) < getNodeSize(node->right)){
                        node->value = findMin(node->right)->value;
                        deletion(node->value, node->right);
                    }
                    else{
                        node->value = findMax(node->left)->value;
                        deletion(node->value, node->left);
                    }
                }
                else{
                    TreeNode * victimNode = node;
                    node = ((node->left != NULL) ? node->left : node->right);
                    delete victimNode;
                    victimNode = NULL;
                }
            }
        }

	public:
		SizeBalancedTree(){
			root = NULL;
			size = 0;
		}
		SizeBalancedTree(SizeBalancedTree & obj){
			this->root = clone(obj.root);
			this->size = obj.getSize();
		}
		~SizeBalancedTree(){
			clear();
		}
		const SizeBalancedTree & operator = (const SizeBalancedTree & obj){
			if (this!=&obj){
				this->clear();
				this->root = clone(obj.root);
				this->size = obj.getSize();
			}
			return (*this);
		}
		int getSize() const {
			return size;
		}
		bool empty() const {
			return getSize()==0;
		}
		bool contains(const T & x) const{
			return contains(x, root);
		}
		const T & findMin() const {
			if (empty()){
				cout<<"There is no element in the search tree"<<endl;
			}
			return findMin(root)->value;
		}
		const T & findMax() const {
			if (empty()){
				cout<<"There is no element in the search tree"<<endl;
			}
			return findMax(root)->value;
		}
		int rank(const T & x) const {
			if (!contains(x)){
				return -1;
			}
			return rank(x, root);
		}
		const T & select(int inputRank) const {
			if (inputRank<0){
				cout<<"input rank is smaller than 0."<<endl;
			}
			if (inputRank>=getSize()){
				cout<<"input rank is larger than tree size"<<endl;
			}
			return select(inputRank, root)->value;
		}

		void levelTraversal(){
            vector<TreeNode *> curLevel;
            curLevel.push_back(root);
            while(curLevel.size()>0){
                vector<TreeNode *> nextLevel;
                for(int i = 0; i<curLevel.size(); i++){
                    cout<<"element: "<< curLevel[i]->value <<", rank: "<< curLevel[i]->nodeSize;
                    if(curLevel[i]->left != NULL) nextLevel.push_back(curLevel[i]->left);
                    if(curLevel[i]->right != NULL) nextLevel.push_back(curLevel[i]->right);
                }
                curLevel = nextLevel;
                cout<<endl;
            }
            cout<<"---------------------------------------"<<endl;
        }

		void clear(){
			clear(root);
			size = 0;
		}
		void insert(const T & x){
			if (contains(x)){
				return;
			}
			size++;
			insert(x, root);
		}
		void remove(const T & x){
			if (!contains(x)){
				return;
			}
			size--;
			deletion(x, root);
		}

};

int main()
{
	SizeBalancedTree<int> test;
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
    cout << "Hello world!" << endl;
    return 0;
}
