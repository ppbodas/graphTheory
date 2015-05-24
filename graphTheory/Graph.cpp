#include "Graph.h"
#include "AppUtility.h"

CAdjecencyNode::CAdjecencyNode(int index, int length): mIndex(index), mLength(length)
{
}


CAdjecencyNode::~CAdjecencyNode()
{
}

CAdjecencyList::CAdjecencyList()
{
	m_Nodes.clear();
}
CAdjecencyList::~CAdjecencyList()
{
}

//CGraph::CGraph():mCount(0)
//{
//	mAdjList.clear();
//}
CGraph::CGraph(int count, bool bNeedEdgeInDataModel): mCount(count), mbNeedEdgeAsDataModel(bNeedEdgeInDataModel)
{
	mAdjList.reserve(count);
	for (int i =0; i< count; ++i)
	{
		mAdjList.push_back(CAdjecencyList());
	}
}

CGraph::~CGraph()
{
}
void CGraph::addEdge(int fromIndex , int toIndex, int length, bool bDirected)
{
	if(mCount == 0 )
		AppUtility::showAssert ("Zero mCount, Set #of Graph vertices");

	CAdjecencyNode * pNode = new CAdjecencyNode(toIndex,length);
	mAdjList[fromIndex].m_Nodes.push_back(pNode);
	if (mbNeedEdgeAsDataModel)
	{
		mEdgeList.push_back(CEdge(fromIndex,toIndex,length));
	}
	
	if(!bDirected)
	{
		//Adding edge from 'To' to 'From'
		CAdjecencyNode * pNode = new CAdjecencyNode(fromIndex,length);
		mAdjList[toIndex].m_Nodes.push_back(pNode);

		if (mbNeedEdgeAsDataModel)
		{
			mEdgeList.push_back(CEdge(toIndex,fromIndex,length));
		}
	}
}
