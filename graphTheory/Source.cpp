#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <assert.h>
#include "Graph.h"
#include "AppUtility.h"
using namespace std;

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
		//First get # of vertices and edges
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

		//Now get edge data in from to distance format
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

		//Now get souce and target between which we want to find shortest distance
		std::getline(cin,str);
		std::vector<int> lastData = AppUtility::split<int>(str);
		if(lastData.size() != 2)
		{
			AppUtility::showAssert("Wrong Source and Target Parameter");
			return 0;
		}
		int s = lastData[0] - 1 ;
		int t = lastData[1] - 1;

		//Find SSSP distance
		int distance = findShortestDistance (s, t, graph);

		if (distance >= 0)
			cout << distance << std::endl;
		else
			cout << "NO" << std::endl;
	}
	getchar();
	return 0;
}