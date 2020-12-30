#include <iostream>
#define noitem 0 //cell의 상태: 이전에도 현재도 없음
#define isitem 1 // 현재값이 이는
#define available 2 //이번에는 있고 현재는 없음
using namespace std;

 12_2
class cell {
public:
	int key; //(key,value)
	int value;
	int flag;
	cell() {
		key = -1;
		value = -1;
		flag = noitem;
	}
};
class linearhashtable {
private:
	cell* hasharr;
	int arrsize; //현재 테이블 크기
	int cursize; //현재까지 삽입된 entry의 갯수
public:
	linearhashtable(int size) {
		this->arrsize = size;
		hasharr = new cell[arrsize];
		cursize = 0;
	}
	//해시함수
	int hashfunc(int key) {
		return key % arrsize;
	}
	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = hashfunc(key) % arrsize; //현재 탐색중인 인덱스
		bool firstopr = true;

		while (hasharr[curidx].flag == isitem || hasharr[curidx].flag == available) {
			if (hasharr[curidx].key == key) {
				cout << "find" << key << endl;
				return;
			}
			else if (curidx == initial_idx && !firstopr) {
				cout << "loop" << endl;
				return;
			}
			probing += 1;
			firstopr = false;
			curidx = (hashfunc(key) + probing - 1) % arrsize;
		}
		cout << "don't find" << key << endl;
	}

	void put(int key, int value) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = hashfunc(key) % arrsize; //현재 탐색중인 인덱스
		bool firstopr = true;

		if (isfull()) { cout << "full" << endl; }
		else {
			while (hasharr[curidx].flag == isitem) {
				if (curidx == initial_idx && !firstopr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstopr = false;
				curidx = (hashfunc(key) + probing - 1) % arrsize;
			}
			hasharr[curidx].key = key;
			hasharr[curidx].value = value;
			hasharr[curidx].flag =isitem;
		}
		cursize++;
	}
	void erase(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = hashfunc(key) % arrsize; //현재 탐색중인 인덱스
		bool firstopr = true;
		if (isempty()) { cout << "empty" << endl; }
		else {
			while (hasharr[curidx].flag == isitem || hasharr[curidx].flag == available) {
				if (hasharr[curidx].key == key) {
					hasharr[curidx].flag = available;
					hasharr[curidx].key = -1;
					hasharr[curidx].value = -1;
					break;
				}
				else if (curidx == initial_idx && !firstopr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstopr = false;
				curidx = (hashfunc(key) + probing - 1) % arrsize;
			}
		}
		cursize--;
	}

	bool isfull() {
		return (cursize == arrsize);
	}
	bool isempty() {
		return(cursize == 0);
	}
	void print() {
		for (int i = 0; i < arrsize; i++) {
			cout << "index is " << i << ", and vlaue is " << hasharr[i].value << endl;
		}
	}
};
class doublehashig {
private:
	cell* hasharr;
	int arrsize; //현재 테이블 크기
	int cursize; //현재까지 삽입된 entry의 갯수
public:
	doublehashig(int size) {
		this->arrsize = size;
		hasharr = new cell[arrsize];
		cursize = 0;
	}
	//해시함수
	int hashfunc(int key) {
		return key % arrsize;
	}
	int hashfunc2(int key) {
		return (17-(key%17));
	}

	void find(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
		bool firstopr = true;

		while (hasharr[curidx].flag == isitem || hasharr[curidx].flag == available) {
			if (hasharr[curidx].key == key) {
				cout << "find" << key << endl;
				return;
			}
			else if (curidx == initial_idx && !firstopr) {
				cout << "loop" << endl;
				return;
			}
			probing += 1;
			firstopr = false;
			curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
		}
		cout << "don't find" << key << endl;
	}

	void put(int key, int value) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
		bool firstopr = true;

		if (isfull()) { cout << "full" << endl; }
		else {
			while (hasharr[curidx].flag == isitem) {
				if (curidx == initial_idx && !firstopr) {
					cout << "loop" << endl;
					break;
				}
				probing += 1;
				firstopr = false;
				curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
			}
			hasharr[curidx].key = key;
			hasharr[curidx].value = value;
			hasharr[curidx].flag = isitem;
		}
		cursize++;
	}

	void erase(int key) {
		int probing = 1;
		int initial_idx = hashfunc(key) % arrsize; //처음 인덱스
		int curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
		bool firstopr = true;
		if (isempty()) { cout << "empty" << endl; }
		else {
			while (hasharr[curidx].flag == isitem || hasharr[curidx].flag == available) {
				if (hasharr[curidx].key == key) {
					hasharr[curidx].flag = available;
					hasharr[curidx].key = -1;
					hasharr[curidx].value = -1;
					break;
				}
				else if (curidx == initial_idx && !firstopr) {
					cout << "loop" << endl;
				}
				probing += 1;
				firstopr = false;
				curidx = (hashfunc(key) + (probing - 1) * hashfunc2(key)) % arrsize;
			}
		}
		cursize--;
	}

	bool isfull() {
		return (cursize == arrsize);
	}
	bool isempty() {
		return(cursize == 0);
	}
	void print() {
		for (int i = 0; i < arrsize; i++) {
			cout << hasharr[i].value<<" " ;
		}
	}

};
int main() {

	int arr[1000];
	int t;
	cin >> t;
	
	for (int i = 0; i < t; i++) {
		int p;
		cin >> p;
		doublehashig ht(p);
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int input;
			cin >> input;
			ht.put(input, input);
			arr[j] = input;
		}
		ht.print();
		for (int j = 0; j < a; j++) {		
			ht.erase(arr[j]);			
		}
	}



	/*linearhashtable ht_1(13);
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