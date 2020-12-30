#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* leftchild;
	node* rightchild;
	node* parent;

	node() {
		this->leftchild = null;
		this->rightchild = null;
		this->parent = null;
	}
	node(int data) {
		this->data = data;
		this->leftchild = null;
		this->rightchild = null;
		this->parent = null;
	}
};
class binarysearchtree {
private:
	node* root;
public:
	binarysearchtree() { this->root = null; }
	void insert(int inputdata) {
		node* newnode = new node(inputdata);
		node* savenode = null;

		if (root == null) {
			root = newnode;
		}
		else {
			node* curnode = root;
			while (curnode != null) {
				savenode = curnode;
				if (curnode->data == inputdata) {
					cout << "duplication" << endl;
					return;
				}
				else if (curnode->data > inputdata) {
					curnode = curnode->leftchild;
				}
				else {
					curnode = curnode->rightchild;
				}
			}
			if (savenode->data > inputdata) {
				newnode->parent = savenode;
				savenode->leftchild = newnode;
			}
			else {
				newnode->parent = savenode;
				savenode->rightchild = newnode;
			}
		}
	}
	node* find(int inputdata) {
		node* curnode = root;
		while (curnode != null) {
			if (curnode->data == inputdata) {
				return curnode;
			}
			else if (curnode->data > inputdata) {
				curnode = curnode->leftchild;
			}
			else {
				curnode = curnode->rightchild;
			}
		}
		return null;
	}
	node* min_findnode(node* _node) {
		node* curnode = _node;
		node* savenode = null;
		while (curnode != null) {
			savenode = curnode;
			curnode = curnode->leftchild;
		}
		return savenode;
	}

	node* max_findnode(node* _node) {
		node* curnode = _node;
		node* savenode = null;
		while (curnode != null) {
			savenode = curnode;
			curnode = curnode->rightchild;
		}
		return savenode;
	}

	void erase(int data) {
		node* curnode = find(data);
		int numofchild = bool(curnode->leftchild) + bool(curnode->rightchild);
		if (numofchild == 0) {
			if (curnode == root) {
				root = null;
			}
			else {
				if (curnode->parent->data > curnode->data) {
					curnode->parent->leftchild = null;
				}
				else {
					curnode->parent->rightchild = null;
				}
			}
			delete curnode;
		}
		else if (numofchild == 2) {
			node* minnode = min_findnode(curnode->rightchild);
			int data = minnode->data;
			erase(minnode->data);
			curnode->data = data;
		}
		else if (numofchild == 1) {
			if (curnode == root) {
				if (curnode->leftchild != null) {
					root = curnode->leftchild;
				}
				else {
					root = curnode->rightchild;
				}
			}
			else {
				node* curparent = curnode->parent;
				node* child = (curnode->leftchild) ? curnode->leftchild : curnode->rightchild;
				if (curparent->data > child->data) {
					curparent->leftchild = child;
					child->parent = curparent;
				}
				else {
					curparent->rightchild = child;
					child->parent = curparent;
				}
			}
			delete curnode;
		}
	}
	void preorderprint(node* curnode) {
		if (curnode != null) {
			cout << curnode->data << " ";
			preorderprint(curnode->leftchild);
			preorderprint(curnode->rightchild);

		}
	}
	void preorder() {
		preorderprint(root);
		cout << endl;
	}




	int min_findnodess(node* _node) {
		node* curnode = _node;
		node* savenode = null;
		while (curnode != null) {
			savenode = curnode;
			curnode = curnode->leftchild;
		}
		return savenode->data;
	}
	int max_findnodess(node* _node) {
		node* curnode = _node;
		node* savenode = null;
		while (curnode != null) {
			savenode = curnode;
			curnode = curnode->rightchild;
		}
		return savenode->data;
	}
	void min(int data) {
		node* curnode = find(data);
		cout << min_findnodess(curnode) << endl;
	}
	void max(int data) {
		node* curnode = find(data);
		cout<<max_findnodess(curnode)<<endl;
	}

};

int main() {

	binarysearchtree bst;
	int testcase;
	cin >> testcase;
	int arr[1000];
	for (int i = 0; i < testcase; i++) {
		int p;
		cin >> p;
		for (int j = 0; j < p; j++) {
			int a;
			cin >> a;
			bst.insert(a);
			arr[j] = a;
		}
		
		int n;
		cin >> n;

		bst.min(n);
		bst.max(n);

		for (int j = 0; j < p; j++) {
			bst.erase(arr[j]);
		}

	}

	return 0;
}