#pragma once
#include <vector>

class CHeapItem
{
public:
	CHeapItem(int id, int key): mId(id), mKey(key){}
	CHeapItem(): mId(-1), mKey(INT_MAX){}
	bool operator < (const CHeapItem & rhs){return mKey < rhs.mKey;}

	int getId(){return mId;}
	int getKey() {return mKey;}
	void setKey(int key){mKey = key;}
private:
	int mId;
	int mKey;
};

class CMinHeap
{
public:
	explicit CMinHeap(int capacity);
	~CMinHeap(void);

	bool isEmpty(){return (0 == mSize);}
	void insert(int id, int key);
	CHeapItem getMin();
	void deleteMin();
	void decreaseKey(int id, int key);
private:
	int getParent(int childPos);
	int getLeftChild(int parentPos){return 2*parentPos + 1;}
	int getRightChild(int parentPos){return 2*parentPos + 2;}
	void percolateUp(int pos);
	void percolateDown(int pos);
	void swapElements(int pos1, int pos2);

private:
	std::vector<int> mPos;
	std::vector<CHeapItem *> mHeapItems;
	int mCapacity;
	int mSize;
};

