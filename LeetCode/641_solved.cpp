

#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
class MyCircularDeque {
private:
    const int capacity;
    int* pData;
    int front, back, size;
    
public:
    MyCircularDeque(int k) : capacity(k), pData(new int[k]),
        front(k - 1), back(0), size(0)
    {}

    ~MyCircularDeque()
    {
        delete(pData);
    }

    bool insertFront(int value)
    {
        if (size < capacity)
        {
            // move front
            front = (front + 1) % capacity;
            pData[front] = value;
            size++;
            return true;
        }
        return false;
    }

    bool insertLast(int value) {
        if (size < capacity)
        {
            // move back
            back = (back + capacity - 1) % capacity;
            pData[back] = value;
            size++;
            return true;
        }
        return false;
    }

    bool deleteFront() {
        if (size > 0)
        {
            // move front
            front = (front + capacity - 1) % capacity;
            size--;
            return true;
        }
        return false;
    }

    bool deleteLast() {
        if (size > 0)
        {
            // move back
            back = (back + 1) % capacity;
            size--;
            return true;
        }
        return false;
    }

    int getFront() {
        if (isEmpty())
        {
            return -1;
        }
        return pData[front];
    }

    int getRear() {
        if (isEmpty())
        {
            return -1;
        }
        return pData[back];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

        MyCircularDeque dq(10);
	}
