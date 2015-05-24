#pragma once
#include <vector>

//Forword Declaration
class CGraph;
class CAdjecencyList;

class CEdge
{
public:
	CEdge(int from, int to, int length):mFrom(from), mTo(to), mLength(length){};
	int getFromIndex(){return mFrom;}
	int getToIndex(){return mTo;}
	int getLength(){return mLength;}

private:
	int mFrom;
	int mTo;
	int mLength;
};
class CAdjecencyNode
{
	friend CGraph;
	friend CAdjecencyList;
public:
	CAdjecencyNode(int index, int length);
	~CAdjecencyNode();
	int getIndex(){return mIndex;}
	int getLength(){return mLength;}
private:
	int mIndex;
	int mLength;
};

class CAdjecencyList
{
	friend CGraph;
public:
	CAdjecencyList();
	~CAdjecencyList();
	std::vector<CAdjecencyNode *> & getAdjecencyNodes() {return m_Nodes;}
private:
	std::vector<CAdjecencyNode *> m_Nodes;
};
 
class CGraph
{
public:
	//CGraph();
	explicit CGraph(int count, bool bNeedEdgeInDataModel = false);
	~CGraph();
	void addEdge(int fromIndex , int toIndex, int length, bool bDirected = true);
	int getVerticesCount(){return mCount;}
	CAdjecencyList & getAdjecencyList(int vertexIndex){return mAdjList[vertexIndex];}
private:
	int mCount;
	std::vector<CAdjecencyList> mAdjList;
	std::vector<CEdge> mEdgeList;
	bool mbNeedEdgeAsDataModel;
};

