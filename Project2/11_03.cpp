#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	Node() {
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}
	Node(int data) {
		this->data = data;
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}
};
class binarySearchTree {
private:
	Node* root;
public:
	binarySearchTree() { this->root = NULL; }
	void insert(int inputData) {
		Node* newNode = new Node(inputData);
		Node* saveNode = NULL;

		if (root == NULL) {
			root = newNode;
		}
		else {
			Node* curNode = root;
			while (curNode != NULL) {
				saveNode = curNode;
				if (curNode->data == inputData) {
					cout << "Duplication" << endl;
					return;
				}
				else if (curNode->data > inputData) {
					curNode = curNode->leftChild;
				}
				else {
					curNode = curNode->rightChild;
				}
			}
			if (saveNode->data > inputData) {
				newNode->parent = saveNode;
				saveNode->leftChild = newNode;
			}
			else {
				newNode->parent = saveNode;
				saveNode->rightChild = newNode;
			}
		}
	}
	Node* find(int inputData) {
		Node* curNode = root;
		while (curNode != NULL) {
			if (curNode->data == inputData) {
				return curNode;
			}
			else if (curNode->data > inputData) {
				curNode = curNode->leftChild;
			}
			else {
				curNode = curNode->rightChild;
			}
		}
		return NULL;
	}
	Node* min_findNode(Node* _Node) {
		Node* curNode = _Node;
		Node* saveNode = NULL;
		while (curNode != NULL) {
			saveNode = curNode;
			curNode = curNode->leftChild;
		}
		return saveNode;
	}

	Node* max_findNode(Node* _Node) {
		Node* curNode = _Node;
		Node* saveNode = NULL;
		while (curNode != NULL) {
			saveNode = curNode;
			curNode = curNode->rightChild;
		}
		return saveNode;
	}

	void erase(int data) {
		Node* curNode = find(data);
		int numOfChild = bool(curNode->leftChild) + bool(curNode->rightChild);
		if (numOfChild == 0) {
			if (curNode == root) {
				root = NULL;
			}
			else {
				if (curNode->parent->data > curNode->data) {
					curNode->parent->leftChild = NULL;
				}
				else {
					curNode->parent->rightChild = NULL;
				}
			}
			delete curNode;
		}
		else if (numOfChild == 2) {
			Node* minNode = min_findNode(curNode->rightChild);
			int data = minNode->data;
			erase(minNode->data);
			curNode->data = data;
		}
		else if (numOfChild == 1) {
			if (curNode == root) {
				if (curNode->leftChild != NULL) {
					root = curNode->leftChild;
				}
				else {
					root = curNode->rightChild;
				}
			}
			else {
				Node* curParent = curNode->parent;
				Node* child = (curNode->leftChild) ? curNode->leftChild : curNode->rightChild;
				if (curParent->data > child->data) {
					curParent->leftChild = child;
					child->parent = curParent;
				}
				else {
					curParent->rightChild = child;
					child->parent = curParent;
				}
			}
			delete curNode;
		}
	}
	void preorderPrint(Node* curNode) {
		if (curNode != NULL) {
			cout << curNode->data << " ";
			preorderPrint(curNode->leftChild);
			preorderPrint(curNode->rightChild);

		}
	}
	void preorder() {
		preorderPrint(root);
		cout << endl;
	}
	void inorderPrint(Node* curNode) {
		if (curNode != NULL) {
			inorderPrint(curNode->leftChild);
			cout << curNode->data << " ";
			inorderPrint(curNode->rightChild);
		}
	}
	void inorder() {
		if (root == NULL) {
			cout << "Empty" << endl;
		}
		else {
			inorderPrint(root);
			cout << endl;
		}
	}

};

int main() {

	binarySearchTree bst;
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

		for (int x = 0; x < n; x++) {
			int b;
			cin >> b;
			bst.erase(b);
			for (int y = 0; y < p; y++) {
				if (arr[y] == b) {
					for (int k = y; k < p; k++) {
						arr[k] = arr[k + 1];
					}
				}
			}
		}

		bst.inorder();

		for (int j = 0; j < p-n; j++) {
			bst.erase(arr[j]);
		}
	
	}
	
	return 0;
}