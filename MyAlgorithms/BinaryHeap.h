
// implementation of Binary heap, priority queue
#ifndef _BINARY_HEAP_
#define _BINARY_HEAP_

#include <iostream>
#include <vector>

template<typename T>
class BinaryHeap
{
private:
	std::vector<T> data;
	bool is_Max;

	void MaxHeapify(int key);
	void MinHeapify(int key);
public:
	BinaryHeap(): is_Max(true) { data.push_back(0); };
	~BinaryHeap() 
	{ 
		data.clear();
	};
	void setMax(bool yesOrNot) { is_Max = yesOrNot; };
	void Heapify();
	void insert(T newElement);
	void erase(int key);
	T get(int key);
	void show()
	{
		for (int i = 1; i < data.size(); ++i)
		{
			std::cout << data[i] << " ";
		}
		std::cout << "\n";
	}
};

template<typename T>
void BinaryHeap<T>::MaxHeapify(int key) // compare me, and children
{
	int l = key * 2, r = l + 1;
	int largest;
	if (l < data.size() && data[l] > data[key])
	{
		largest = l;
	}
	else
	{
		largest = key;
	}

	if (r < data.size() && data[r] > data[largest])
	{
		largest = r;
	}

	if (largest != key) // swap
	{
		std::swap(data[largest], data[key]);
		return MaxHeapify(largest);	// propagate
	}
}
template<typename T>
void BinaryHeap<T>::MinHeapify(int key)
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

template<typename T>
void BinaryHeap<T>::Heapify()
{
	if (is_Max)
	{
		for (int i = data.size() / 2; i >= 1 ; --i)
		{
			MaxHeapify(i);
		}
	}
	else
	{
		for (int i = data.size() / 2; i >= 1 ; --i)
		{
			MinHeapify(i);
		}
	}
}


template<typename T>
void BinaryHeap<T>::insert(T newElement)
{
	data.push_back(newElement);
	Heapify();
}

template<typename T>
void BinaryHeap<T>::erase(int key)
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

	if (is_Max)
	{
		MaxHeapify(key);
	}
	else
	{
		MinHeapify(key);
	}
}

template<typename T>
T BinaryHeap<T>::get(int key)
{
	return data[key];
}

#endif
