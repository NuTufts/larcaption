/*
	Implementation file for class to build a non-binary tree from truth information
	such that it can be traversed to create sentences describing interactions.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <queue>
#include "nonBinaryTree.hpp"
using namespace std;



// default constructor
nonBinaryTree::nonBinaryTree()
{
	treeSize = 1;
	root.trackID = 1;
	root.motherID = 1;
	root.numChildren = 0;
	root.particleName = "neutrino";
	root.generation = 'R';
	root.numParticle = 1;
	root.particleID = 1;
	particleCount(root.trackID);   
	countArraySize = 100;
	searchedNode = NULL;
	foundNode = false;    
	//depthCap = NULL;
	//depthCap = "";
}

// parametrized constructor
nonBinaryTree::nonBinaryTree(float rootEnergy, int rootTrackID)
{
	root.trackEnergy = rootEnergy;
	root.trackID = rootTrackID;	
	root.particleName = "neutrino";
	root.generation = 'R';
	root.motherID = 1;
	treeSize = 1;
	root.numChildren = 0;
	root.numParticle = 1;
	root.particleID = 1;
	particleCount(root.particleID);
	countArraySize = 100;
	searchedNode = NULL;
	foundNode = false;
	//depthCap = NULL;
	//depthCap = "";
}

// destructor
nonBinaryTree::~nonBinaryTree()
{
	//delete depthCap;
}

// adjusts the particle count
void nonBinaryTree::particleCount(int particleID)
{
	if (particleID >= countArraySize)
	{
		int *temp = new int[particleID];

		for (int i = 0; i < countArraySize; i++)
		{
			temp[i] = countArray[i];
		}

		countArraySize = *temp;
	}

	countArray[particleID]++;
}

// returns whether or not the child is a leaf (has no children)
bool nonBinaryTree::isLeaf(treeNode *currNode)
{
	if (currNode->numChildren == 0)
		return true;

	else
		return false;
}
 
// returns the node with the trackID being searched for 
void nonBinaryTree::search(int ID_num, treeNode *currNode)  
{
	if (currNode->trackID == ID_num)
	{
		foundNode = true;
		searchedNode = currNode;
	}
  
	if (isLeaf(currNode))
	{
		return;
	}
 
	else
	{
		for (int i = 0; i < currNode->numChildren; i++)
		{
			search(ID_num, &currNode->children[i]);
		}
  
		return;
	}
}

// adds new node to tree
// 1. find mother node of new node
// 2. add new node to mother's children array
// 3. sorts children in order of lowest to highest energy (from left to right)

void nonBinaryTree::addNode(int motherID, int trackID, float energy, string particleName, int particleID)
{
	// resetting class data members so that the search function works
	foundNode = false;
	searchedNode = NULL;

	// find the correct mother node for the new child
	// after the search function call the correct mother node is in data member searchedNode
	search(motherID, &root);

	// create new node
	nonBinaryTree::treeNode child = createNode(energy, trackID, motherID, particleName, particleID);

	// define particle generation
	char newChildGen = setParticleGen(searchedNode->generation);
	child.generation = newChildGen;

	// increment size of tree
	treeSize++;

	// increment particle count
	particleCount(particleID);

	child.numParticle = countArray[particleID];

	// add new node to the back of the children array
	searchedNode->children.push_back(child);
	searchedNode->numChildren = searchedNode->numChildren + 1;

	// sort children in energy order
	int size = searchedNode->numChildren;
	vector <nonBinaryTree::treeNode> temp = sortChildren(searchedNode->children, size);
	searchedNode->children = temp;
}

// sort children in ascending order by energies
// sort algorithm: insertion sort (if numbers get larger then a different algorithm could
// be used due to the time complexity)
vector <nonBinaryTree::treeNode> nonBinaryTree::sortChildren(vector <treeNode> children, int len)
{
	int j;
	nonBinaryTree::treeNode temp;

	if (len < 2)
		return children;  

	for (int i = 0; i < len; i++)
	{
		j = i;

		// compare energies but change placement of nodes
		while (j > 0 && (children[j].trackEnergy < children[j-1].trackEnergy))
		{
			temp = children[j];
			children[j] = children[j-1];
			children[j-1] = temp;
			j--;
		}
	}

	return children;	
}


// creates a new node   
nonBinaryTree::treeNode nonBinaryTree::createNode(float energy, int trackID, int motherID, string particleName, int particleID)
{
	treeNode newNode;
	newNode.trackEnergy = energy;
	newNode.trackID = trackID;
	newNode.motherID = motherID;
	newNode.particleName = particleName;
	newNode.numChildren = 0;
	newNode.particleID = particleID;

	return newNode;
}

// save node
// loop over children
// return (if node isLeaf)   
void nonBinaryTree::depthTrav(treeNode *currNode)
{
	if (isLeaf(currNode))
	{
		cout << currNode->particleName << "-" << 
			currNode->generation << currNode->numParticle << endl;

		//string cap = (currNode->particleName + "-" + currNode->generation + to_string(currNode->numParticle) + " ");
		depthCap->push_back(currNode->particleName);
		return;
	}

	else    
	{
		for(int i = 0; i < currNode->numChildren; i++)
		{
			depthTrav(&(currNode->children[i]));
		}

		cout << currNode->particleName << "-" << 
			currNode->generation << currNode->numParticle << endl;

		depthCap->push_back((currNode->particleName + "-" + currNode->generation + to_string(currNode->numParticle) + " "));
		return;
	}  
} 

string nonBinaryTree::vecToString(vector <string> cap)
{
	string returnCap = "";
	int max = cap.size();
	
	for (int i = 0; i < max; i++)
	{
		returnCap = returnCap + cap[i];
	}

	return returnCap;
} 
  
// public member function to complete the depth trav
string nonBinaryTree::publicDepthTrav()
{
	depthTrav(&root);

	string newCap = vecToString(*depthCap);
	//cout << depthCap;

	return newCap;
}
 
void nonBinaryTree::getTreeSize()
{
	cout << treeSize << endl;
}

// returns the number of children that a given particle has
// (particles identified by trackID)
void nonBinaryTree::getNumChildren(int trackID)
{
	foundNode = false;
	searchedNode =  NULL;
	search(trackID, &root);
	int children = searchedNode->children.size();

	cout << "Particle " << trackID << " has " << children << " children" << endl;
}

// prints the root node's children in order
void nonBinaryTree::printRootChildren()
{ 
	int size = root.numChildren;

	cout << "printing root's children in order" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << root.children[i].particleName << endl;
	}
}  

// print's any node's children in order
// for debugging purposes
void nonBinaryTree::printChildren(int trackID)
{
	searchedNode = NULL;
	foundNode = false;
	search(trackID, &root);
	int size = searchedNode->children.size();

	cout << "Particle " << trackID << "'s children" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << searchedNode->children[i].particleName << 
				searchedNode->children[i].generation << endl;
	}
}

// helper function that returns the correct particle generation 
// given the mother's generation
char nonBinaryTree::setParticleGen(char motherGen)
{
	char childGen;

	if (motherGen == 'R')
		childGen = 'A';

	else
		childGen = motherGen + 1;

	return childGen;
}

// breadth-first traversal of the tree to print
string nonBinaryTree::breadthTrav(treeNode *rootNode)
{
	string caption = "";

	if (treeSize == 1)  
		return caption;

	queue <nonBinaryTree::treeNode *> q;
	q.push(rootNode);

	while (q.empty() == false)
	{
		nonBinaryTree::treeNode *temp = q.front();

		cout << temp->particleName << "-" << temp->generation << temp->numParticle << endl;

		caption = caption + temp->particleName + "-" + temp->generation + to_string(temp->numParticle) + " ";

		if (q.size() )

		q.pop();

		
		// loop over the temp node's children and enqueue
		for (int i = 0; i < temp->numChildren; i++)
		{
			q.push(&(temp->children[i]));
		}
	}

	return caption;
}
 
// public version of breadth traversal
string nonBinaryTree::publicBreadthTrav()
{
	string breadthCap = breadthTrav(&root);

	return breadthCap;
}

// print number of instances of a given particle
void nonBinaryTree::particleNumber(int particleID)
{
	cout << "There are " << countArray[particleID] <<
		" type " << particleID << " particles" << endl;
}

// converts pdg code to string of particle name
// works only for neutron, proton, pions, kaons, and leptons
string nonBinaryTree::pdgToString(int pdgCode)
{
	int codes [16] = {11,12,13,14,15,16,17,18,111,211,2212,2112,130,310,311,321};
	string names [16] = {"electron","electron neutrino","muon","muon neutrino","neutral pion","pion+","proton","neutron", "NL-Kaon", "NS-Kaon","N-Kaon","Kaon+"};
	string notFound = "unidentified particle";

	for (int i = 0; i < 16; i++)
	{
		if (pdgCode == codes[i])
			return names[i];
	}

	// if pdg code not found
	return notFound;

}
  














