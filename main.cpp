//Data structure HW4-1
//B10815026 ¹ù¾¥­õ

#include<iostream>
#include<vector>
#include<set>
#include<map>

using namespace std;

struct Edge {
	int v1;
	int v2;
	int weight;
};

struct NodeData {
	vector<Edge> outEdges;
	int label;	
	int prevNode;
};

int main() {
	int nodesNum;
	int edgeNum;
	int startV;
	int endV;
	
	vector<int> path;
	set<int> N;
	set<int> labeled;
	map<int, NodeData> allNodes;

	cin >> nodesNum >> edgeNum >> startV >> endV;

	for (int i = 0; i < edgeNum; ++i) {
		Edge tempEdge;
		cin >> tempEdge.v1 >> tempEdge.v2 >> tempEdge.weight;
		if (allNodes.count(tempEdge.v1) == 0) {
			NodeData tempNodeData;
			tempNodeData.label = -1;
			tempNodeData.outEdges.push_back(tempEdge);
			tempNodeData.prevNode = -1;
			allNodes[tempEdge.v1] = tempNodeData;
		}
		else {
			allNodes[tempEdge.v1].outEdges.push_back(tempEdge);
		}
	}

	//for (auto it = allNodes.begin(); it != allNodes.end(); ++it) {
	//	cout << "node: " << (*it).first << endl;
	//	cout << "edges: " << endl;
	//	for (int i = 0; i < it->second.outEdges.size(); ++i) {
	//		cout << "v1: " << it->second.outEdges[i].v1 << " v2: " << it->second.outEdges[i].v2 << " weight: " << it->second.outEdges[i].weight << endl;
	//	}
	//	cout << "\n=================================" << endl;
	//}


	//insert the source node into set N and vector path
	allNodes[startV].label = 0;
	allNodes[startV].prevNode = startV;
	path.push_back(startV);
	N.insert(startV);
	int newInserted = startV;

	//do Dijkstra¡¦s Algorithm, keep searching until the destination node is in set N
	while (!N.count(endV)) {
		//iterate the edges from the newly inserted node
		for (int i = 0; i < allNodes[newInserted].outEdges.size(); ++i) {
			int outNodeName = allNodes[newInserted].outEdges[i].v2;
			//if the node is already in N, don't need to do anything
			if (N.count(outNodeName)) {
				continue;
			}
			else { //label or relabel this node
				//if it's already in the set labeled, relabel it
				if (labeled.count(outNodeName)) {
					if (allNodes[outNodeName].label > allNodes[newInserted].label + allNodes[newInserted].outEdges[i].weight) {
						allNodes[outNodeName].label = allNodes[newInserted].label + allNodes[newInserted].outEdges[i].weight;
						allNodes[outNodeName].prevNode = newInserted;
					}
				}
				else { //label it
					allNodes[outNodeName].label = allNodes[newInserted].label + allNodes[newInserted].outEdges[i].weight;
					labeled.insert(outNodeName);
					allNodes[outNodeName].prevNode = newInserted;
				}
			}
		}

		//pick a node with the min label value, and insert it into set N and vector path
		int minLabel = 2147483647;
		//int prevInserted = newInserted;
		for (auto it = labeled.begin(); it != labeled.end(); ++it) {
			if (minLabel > allNodes[*it].label) {
				minLabel = allNodes[*it].label;
				//let this node to be the newly inserted node
				newInserted = *it;
			}
		}
		N.insert(newInserted);
		path.push_back(newInserted);
		//allNodes[newInserted].prevNode = prevInserted;

		//remove this node from the set labeled
		labeled.erase(newInserted);
	}

	vector<int> result;
	int currentNode = endV;

	do
	{
		result.push_back(currentNode);
		currentNode = allNodes[currentNode].prevNode;
	} while (currentNode != startV);
	result.push_back(currentNode);

	bool first = true;
	for (auto rit = result.rbegin(); rit != result.rend(); ++rit) {
		if (!first) {
			cout << " ";
		}
		else {
			first = false;
		}
		cout << *rit;
	}

	cout << endl;
	cout << allNodes[endV].label;
}