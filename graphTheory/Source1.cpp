#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <assert.h>
#include "Graph.h"
#include "AppUtility.h"
using namespace std;

namespace AppUtility
{
	template<typename T>
	std::vector<T> AppUtility::split(const std::string& line)
	{
		std::istringstream is(line);
		return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
	}
	void AppUtility::showAssert(const std::string & errorMsg)
	{
		assert(false && errorMsg.c_str());
		std::cout << errorMsg.c_str() <<std::endl;
	}
}
void tempFunc()
{
	std::vector<int> v = AppUtility::split<int>("3");
}

//Forword Declaration
class CGraph;
class CAdjecencyList;

class CAdjecencyNode
{
	friend CGraph;
	friend CAdjecencyList;
public:
	CAdjecencyNode(int index, int length): mIndex(index), mLength(length)
	{
	}
	~CAdjecencyNode()
	{
	}
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
	CAdjecencyList()
	{
		m_Nodes.clear();
	}
	~CAdjecencyList(){}
	std::vector<CAdjecencyNode *> & getAdjecencyNodes() {return m_Nodes;}
private:
	std::vector<CAdjecencyNode *> m_Nodes;
};
 
class CGraph
{
public:
	//CGraph();
	explicit CGraph(int count);
	~CGraph();
	void addEdge(int fromIndex , int toIndex, int length, bool bDirected = true);
	int getVerticesCount(){return mCount;}
	CAdjecencyList & getAdjecencyList(int vertexIndex){return mLists[vertexIndex];}
private:
	int mCount;
	std::vector<CAdjecencyList> mLists;
};

//CGraph::CGraph():mCount(0)
//{
//	mLists.clear();
//}
CGraph::CGraph(int count): mCount(count)
{
	mLists.reserve(count);
	for (int i =0; i< count; ++i)
	{
		mLists.push_back(CAdjecencyList());
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
	mLists[fromIndex].m_Nodes.push_back(pNode);
	
	if(!bDirected)
	{
		//Adding edge from 'To' to 'From'
		CAdjecencyNode * pNode = new CAdjecencyNode(fromIndex,length);
		mLists[toIndex].m_Nodes.push_back(pNode);
	}
}

typedef std::pair<int,int> HEAP_PAIR;
class CompareFunc
{
public:
	bool operator() (HEAP_PAIR pair1, HEAP_PAIR pair2)
	{
		if (pair1.second < pair2.second)
			return true;
		else if (pair1.second > pair2.second)
			return false;
		else	//both pair values are same. Now check id
		{
			return pair1.first < pair2.first;
		} 
	}
};
typedef std::set<HEAP_PAIR, CompareFunc> HEAP;

int findShortestDistance (int source, int destination, CGraph & graph)
{
	if (source == destination)		//Distance to self is zero
		return 0;
	int n = graph.getVerticesCount();
	vector<int> vDistances(n,-1);
	
	//Heap implemented as set
	HEAP heap;

	//Add source element to heap
	vDistances[source] = 0;
	heap.insert(make_pair(source,0));

	while (!heap.empty())
	{
		//1.0 Get min element
		HEAP::iterator iter = heap.begin();		

		//2.0 Find all distances
		//get distance upto current node
		int distance = vDistances[(*iter).first];
		if (distance < 0) distance = 0;
		//get adjecency list
		CAdjecencyList & adjList = graph.getAdjecencyList((*iter).first);
		//iterate over adjecency list
		std::vector<CAdjecencyNode *> & nodes = adjList.getAdjecencyNodes();

		//delete this node
		heap.erase(iter);

		for(CAdjecencyNode * pNode : nodes)
		{
			if (vDistances[pNode->getIndex()] == -1)
			{
				//First time this node is discovered, insert in heap
				vDistances[pNode->getIndex()] = distance + pNode->getLength();
				heap.insert(make_pair(pNode->getIndex(),vDistances[pNode->getIndex()]));			
			}
			else
			{
				if(vDistances[pNode->getIndex()] > (distance + pNode->getLength()))
				{
					//This node is already present but we have discovered new shorter path
					HEAP::iterator curNodeIter = heap.find(make_pair(pNode->getIndex(), vDistances[pNode->getIndex()]));
					//Erase this node and insert with updated value
					heap.erase(curNodeIter);
					//Update distance value
					vDistances[pNode->getIndex()] = distance + pNode->getLength();
					heap.insert(make_pair(pNode->getIndex(),vDistances[pNode->getIndex()]));
				}
			}
		}
	}

	return vDistances[destination];
}

int main()
{
	int nTestCases;
	cin >> nTestCases;
	cin.ignore();
	for(int dataIndex = 0; dataIndex < nTestCases; ++dataIndex)
	{
		std::string str;
		std::getline(cin,str);
		std::vector<int> firstData = AppUtility::split<int>(str);
		if (firstData.size() != 2)
		{
			AppUtility::showAssert("Wrong Input");
			return 0;
		}
		
		int n = firstData[0];
		int m = firstData[1];
		CGraph graph(n);

		for (int i = 0; i < m; ++i)
		{
			std::string str;
			std::getline(cin,str);
			std::vector<int> edgeData = AppUtility::split<int>(str);
			if (edgeData.size() != 3)
			{
				AppUtility::showAssert("Wrong Edge Data");
				return 0;
			}
			graph.addEdge(edgeData[0] - 1,edgeData[1] - 1,edgeData[2]);
		}
		std::getline(cin,str);
		std::vector<int> lastData = AppUtility::split<int>(str);
		if(lastData.size() != 2)
		{
			AppUtility::showAssert("Wrong Source and Target Parameter");
			return 0;
		}
		int s = lastData[0] - 1 ;
		int t = lastData[1] - 1;
		int distance = findShortestDistance (s, t, graph);

		if (distance >= 0)
			cout << distance << std::endl;
		else
			cout << "NO" << std::endl;
	}
	getchar();
	return 0;
}