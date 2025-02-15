
// min heap
#include <iostream>
#include <vector>

class BinaryHeap
{
private:
	std::vector<int> data;

	void MinHeapify(int key);
public:
	BinaryHeap(){ data.push_back(0); };
	~BinaryHeap() 
	{ 
		data.clear();
	};
	void Heapify();
	void insert(int newElement);
	void erase(int key);
	int get(int key);
	void show()
	{
		for (int i = 1; i < data.size(); ++i)
		{
			std::cout << data[i] << " ";
		}
		std::cout << "\n";
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	BinaryHeap heap;
	int N, input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		if (input == 0)
		{
			std::cout << heap.get(1) << "\n";
			heap.erase(1);
		}
		else
		{
			heap.insert(input);
		}
	}
}

void BinaryHeap::MinHeapify(int key)
{
	int l = key * 2, r = l + 1;
	int smallest;
	if (l < data.size() && data[l] < data[key])
	{
		smallest = l;
	}
	else
	{
		smallest = key;
	}

	if (r < data.size() && data[r] < data[smallest])
	{
		smallest = r;
	}

	if (smallest != key)
	{
		std::swap(data[smallest], data[key]);
		return MinHeapify(smallest);
	}
}

void BinaryHeap::Heapify()
{
	for (int i = data.size() / 2; i >= 1 ; --i)
	{
		MinHeapify(i);
	}
}


void BinaryHeap::insert(int newElement)
{
	data.push_back(newElement);
	
	int curNode = data.size() - 1;
	int parent = curNode / 2;
	while (data[parent] > data[curNode])
	{
		std::swap(data[parent], data[curNode]);
		curNode = parent;
		parent /= 2;
	}
}

void BinaryHeap::erase(int key)
{
	if (key < data.size())
	{
		data[key] = data.back();
		data.erase(--data.end());
	}
	else
	{
		return;
	}

	MinHeapify(key);
}

int BinaryHeap::get(int key)
{
	if (data.size() == 1)
	{
		return 0;
	}
	else
	{
		return data[key];
	}
}


