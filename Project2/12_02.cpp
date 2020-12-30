#include <iostream>
#define NOITEM 0 //cell의 상태: 이전에도 현재도 없음
#define ISITEM 1 // 현재값이 이는
#define AVAILABLE 2 //이번에는 있고 현재는 없음
using namespace std;


// 12_4

class cell {
public:
	int key; //(key,value)
	int value;
	int flag;
	cell() {
		key = -1;
		value = -1;
		flag = NOITEM;
	}
};
class LinearHashTable {
private:
	cell* hashArr;
	int arrSize; //현재 테이블 크기
	int curSize; //현재까지 삽입된 entry의 갯수
public:
	LinearHashTable(int size) {
		this->arrSize = size;
		hashArr = new cell[arrSize];
		curSize = 0;
	}
	//해시함수
	int hashfunc(int key) {
		return key % arrSize;
	}
	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = hashfunc(key) % arrSize; //현재 탐색중인 인덱스
		bool firstOpr = true;

		while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
			if (hashArr[curIdx].key == key) {
				cout << "True " << probing << endl;
				return;
			}
			else if (curIdx == initial_idx && !firstOpr) {
				cout << "False "<< probing << endl;
				return;
			}
			probing += 1;
			firstOpr = false;
			curIdx = (hashfunc(key) + probing - 1) % arrSize;
		}
		cout << "False " << probing << endl;
	}

	void put(int key, int value) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = hashfunc(key) % arrSize; //현재 탐색중인 인덱스
		bool firstOpr = true;

		if (isFull()) { cout << "Full" << endl; }
		else {
			while (hashArr[curIdx].flag == ISITEM) {
				if (curIdx == initial_idx && !firstOpr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashfunc(key) + probing - 1) % arrSize;
			}
			hashArr[curIdx].key = key;
			hashArr[curIdx].value = value;
			hashArr[curIdx].flag = ISITEM;
		}
		curSize++;
	}
	void erase(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = hashfunc(key) % arrSize; //현재 탐색중인 인덱스
		bool firstOpr = true;
		if (isEmpty()) { cout << "Empty" << endl; }
		else {
			while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
				if (hashArr[curIdx].key == key) {
					hashArr[curIdx].flag = AVAILABLE;
					hashArr[curIdx].key = -1;
					hashArr[curIdx].value = -1;
					break;
				}
				else if (curIdx == initial_idx && !firstOpr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashfunc(key) + probing - 1) % arrSize;
			}
		}
		curSize--;
	}

	bool isFull() {
		return (curSize == arrSize);
	}
	bool isEmpty() {
		return(curSize == 0);
	}
	void print() {
		for (int i = 0; i < arrSize; i++) {
			cout << "index is " << i << ", and vlaue is " << hashArr[i].value << endl;
		}
	}
};
class DoubleHashig {
private:
	cell* hashArr;
	int arrSize; //현재 테이블 크기
	int curSize; //현재까지 삽입된 entry의 갯수
public:
	DoubleHashig(int size) {
		this->arrSize = size;
		hashArr = new cell[arrSize];
		curSize = 0;
	}
	//해시함수
	int hashfunc(int key) {
		return key % arrSize;
	}
	int hashfunc2(int key) {
		return (17 - (key % 17));
	}

	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
		bool firstOpr = true;

		while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
			if (hashArr[curIdx].key == key) {
				cout << "find" << key << endl;
				return;
			}
			else if (curIdx == initial_idx && !firstOpr) {
				cout << "loop" << endl;
				return;
			}
			probing += 1;
			firstOpr = false;
			curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
		}
		cout << "don't find" << key << endl;
	}

	void put(int key, int value) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
		bool firstOpr = true;

		if (isFull()) { cout << "Full" << endl; }
		else {
			while (hashArr[curIdx].flag == ISITEM) {
				if (curIdx == initial_idx && !firstOpr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
			}
			hashArr[curIdx].key = key;
			hashArr[curIdx].value = value;
			hashArr[curIdx].flag = ISITEM;
		}
		curSize++;
	}

	void erase(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrSize; //처음 인덱스
		int curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
		bool firstOpr = true;
		if (isEmpty()) { cout << "Empty" << endl; }
		else {
			while (hashArr[curIdx].flag == ISITEM || hashArr[curIdx].flag == AVAILABLE) {
				if (hashArr[curIdx].key == key) {
					hashArr[curIdx].flag = AVAILABLE;
					hashArr[curIdx].key = -1;
					hashArr[curIdx].value = -1;
					break;
				}
				else if (curIdx == initial_idx && !firstOpr) {
					cout << "loop" << endl;
				}
				probing += 1;
				firstOpr = false;
				curIdx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrSize;
			}
		}
		curSize--;
	}

	bool isFull() {
		return (curSize == arrSize);
	}
	bool isEmpty() {
		return(curSize == 0);
	}
	void print() {
		for (int i = 0; i < arrSize; i++) {
			cout << hashArr[i].value << " ";
		}
	}

};
int main() {

	int arr[1000];
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int p;
		cin >> p;
		LinearHashTable ht(p);
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int input;
			cin >> input;
			ht.put(input, input);
			arr[j] = input;
		}
		int R;
		cin >> R;
		for (int j = 0; j < R; j++) {
			int r;
			cin >> r;
			ht.find(r);
		}

		for (int j = 0; j < a; j++) {
			ht.erase(arr[j]);
		}
	}



	/*LinearHashTable ht_1(13);
	ht_1.put(7, 7);
	ht_1.put(20, 20);
	ht_1.put(2, 2);
	ht_1.put(5,5);
	ht_1.put(33, 33);
	ht_1.erase(20);

	ht_1.find(33);
	ht_1.find(20);
	cout << " ===" << endl;
	ht_1.print();*/
}