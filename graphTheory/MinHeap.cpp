#include "MinHeap.h"
#include "AppUtility.h"

CMinHeap::CMinHeap(int capacity):mHeapItems(capacity, 0), mPos(capacity, -1), mCapacity(capacity), mSize(0)
{	
}

CMinHeap::~CMinHeap(void)
{
}
CHeapItem CMinHeap::getMin()
{
	return *mHeapItems[0];
}
void CMinHeap::deleteMin()
{
	if (isEmpty())
		return;

	//Swap Last element with first
	swapElements(0 , mSize - 1);

	//delete last memory
	CHeapItem * pItem = mHeapItems[mSize - 1];
	delete pItem;
	mHeapItems[mSize - 1] = 0;

	//decrease size
	--mSize;

	percolateDown(0);
}

void CMinHeap::insert(int id, int key)
{
	CHeapItem * pHeapItem  = new CHeapItem(id, key);
	mHeapItems[mSize] = pHeapItem;
	mPos[id] = mSize;	//Currently element is at size
	percolateUp(mSize);
	++mSize;			//Size has increased.
}

void CMinHeap::decreaseKey(int id, int key)
{
	mHeapItems[mPos[id]]->setKey(key);
	percolateUp(mPos[id]);
}

int CMinHeap::getParent(int childPos)
{
	if (0 == childPos)
		return 0;

	return (childPos - 1)/2;
}

void CMinHeap::percolateUp(int pos)
{
	if (0 == pos)
	{
		//We have reached top. No need to go up further
		return;
	}
	int parent = getParent(pos);
	
	if ((0 == mHeapItems[pos]) || (0 == mHeapItems[parent]))
	{
		AppUtility::showAssert("Unexpected Null Pointer");
		return;
	}

	//Compare with parent key
	if (*mHeapItems[pos] < *mHeapItems[parent])
	{
		//Swap elements
		swapElements(pos, parent);
	}
	percolateUp(parent);
}
void CMinHeap::percolateDown(int pos)
{
	if (mSize <= 1)
		return;		//Nothing to do here

	int leftChild = getLeftChild(pos);
	int rightChild = getRightChild(pos);

	if (leftChild < mSize)
	{
		int minChildPos = leftChild;
		
		if (rightChild < mSize)
			minChildPos = *mHeapItems[rightChild] < *mHeapItems[leftChild]   ? rightChild : leftChild;

		if ((0 == mHeapItems[pos]) || (0 == mHeapItems[minChildPos]))
		{
			AppUtility::showAssert("Unexpected Null Pointer");
			return;
		}

		if(*mHeapItems[minChildPos] < *mHeapItems[pos])
		{
			swapElements(minChildPos, pos);
			percolateDown(minChildPos);
		}
	}
}
void CMinHeap::swapElements(int pos1, int pos2)
{
	if (pos1 == pos2)
		return;

	int id1 = mHeapItems[pos1]->getId();
	int id2 = mHeapItems[pos2]->getId();

	CHeapItem * pTemp =  mHeapItems[pos1];
	mHeapItems[pos1] = mHeapItems[pos2];
	mHeapItems[pos2] = pTemp;

	mPos[id1] = pos2;
	mPos[id2] = pos1;
}


