#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum direction { MIN = 1, MAX = -1 };

class Heap {
private:
	vector<int> v;
	int heap_size;
	int root_index;
	int direction;
	int count;
public:

	Heap(int direction) {
		v.push_back(-1);
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction;
		this->count = 0;
	}
	void swap(int idx1, int idx2) {
		v[0] = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = v[0];
	}
	void upHeap(int idx) {
		if (idx == root_index) {
			count++;
			return;
		}
		else {
			int parent = idx / 2;
			if (v[parent] * direction > v[idx] * direction) {
				swap(parent, idx);
				upHeap(parent);
			}
			count++;
		}
	}
	void downHeap(int idx) {
		int left = idx * 2;
		int right = idx * 2 + 1;
		if (right <= heap_size) {
			if (v[left] * direction <= v[right] * direction) {
				if (v[left] * direction < v[idx] * direction) {
					swap(left, idx);
					downHeap(left);
				}
				else return;
			}
			else {
				if (v[right] * direction < v[idx] * direction) {
					swap(right, idx);
					downHeap(right);
				}
				else return;
			}
		}
		else if (left <= heap_size) {
			if (v[left] * direction < v[idx] * direction) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else return;
	}
	void insert(int e) {
		v.push_back(e);
		heap_size++;
		upHeap(heap_size);
	}
	int pop() {
		int top = v[root_index];
		v[root_index] = v[heap_size];
		heap_size--;
		v.pop_back();
		downHeap(root_index);
		return top;
	}
	int top() {
		return v[root_index];
	}
	int size() {
		return heap_size;
	}
	int isEmpty() {
		if (heap_size == 0) {
			return 1;
		}
		else return 0;
	}
	void print() {
		if (isEmpty() == 0) {
			for (int i = root_index; i < heap_size; i++) {
				cout << v[i] << " ";
			}
			cout << v[heap_size] << endl;
		}
		else cout << -1 << endl;
	}
	int find(int x) {
		if (isEmpty() == 0)return v.at(x);
	}

	int counting() {
		return count;
	}

};

int main() {
	Heap PQ(MIN);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {

		int a, b;
		cin >> a >> b;

		int arr[10000];

		for (int j = 0; j < a; j++) {
			int num;
			cin >> num;
			PQ.insert(num);
			arr[j] = num;
		}

		for (int y = 0; y < a - 1; y++) {
			for (int x = y; x < a; x++) {
				if (arr[y] > arr[x]) {
					swap(arr[y], arr[x]);
				}
			}
		}

		//주어진 정수를 기반으로 생성된 최소힙을 공백을 기준으로 출력한
		PQ.print();

		// 생성된 최소힙의 p번째 인덱스 값을 출력한다.
		cout << PQ.find(b) << endl;

		//주어진 정수를 오름차순으로 정렬한 결과에서 p번째 값을 출력한다.
		cout << arr[b - 1] << endl;

		//최소힙을 생성할 때 호출 된 upheap의 누적 횟수를 출력한다.
		cout << PQ.counting() << endl;

		for (int j = 0; j < a; j++) {
			PQ.pop();
			arr[i] = 100;
		}

	}
	return 0;
}
