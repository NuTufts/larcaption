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
#include "particleIDMap.hpp"
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
	searchedNode = NULL;
	countArraySize = 3000;
	foundNode = false; 
	antiCountArraySize = 3000;  
	particleCount(root.trackID);   
	   
	//depthCap = NULL;
	//depthCap = "";

	for (int i = 0; i < countArraySize; i++)
	{
		countArray[i] = 0;
	}

	for (int i = 0; i < antiCountArraySize; i++)
	{
		antiCountArray[i] = 0;
	}
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
	searchedNode = NULL;
	countArraySize = 3000;
	foundNode = false;
	antiCountArraySize = 3000;
	particleCount(root.particleID);

	//depthCap = NULL;
	//depthCap = "";

	for (int i = 0; i < countArraySize; i++)
	{
		countArray[i] = 0;
	}

	for (int i = 0; i < antiCountArraySize; i++)
	{
		antiCountArray[i] = 0;
	}
}

// destructor
nonBinaryTree::~nonBinaryTree()
{
	//delete depthCap;
}

// adjusts the particle count
void nonBinaryTree::particleCount(int particleID)
{
	if (particleID >= 0)
	{
		if (particleID >= countArraySize)
		{
			//int *temp = new int[particleID];
			int *temp = new int[particleID];

			for (int i = 0; i < particleID; i++)
			{
				temp[i] = 0;
			}

			for (int i = 0; i < countArraySize; i++)
			{	
				temp[i] = countArray[i];
			}

			countArray = temp;
			countArraySize = particleID;
		} 
		countArray[particleID]++;
	}

	else
	{
		int absValPID = particleID*-1;
		if (absValPID >= antiCountArraySize) 
		{
			int *temp = new int[absValPID];

			for (int i = 0; i < absValPID; i++)
			{
				temp[i] = 0;
			}

			for (int i = 0; i < antiCountArraySize; i++)
			{	
				temp[i] = antiCountArray[i];
			}

			antiCountArray = temp;
			countArraySize = absValPID;	
		}
		antiCountArray[absValPID]++;
	}
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
		//foundNode = true;
		searchedNode = currNode;
		foundNode = true;
		return;  
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
	//foundNode = false;
	searchedNode = NULL;
	foundNode =  false;

	// find the correct mother node for the new child
	// after the search function call the correct mother node is in data member searchedNode
	search(motherID, &root);


	// create new node
	if (foundNode == false)  
	{
		nonBinaryTree::treeNode child = createNode(energy, trackID, motherID, particleName, particleID);
		lostNodes.push_back(child);
		cout << "number of orphan nodes: " << lostNodes.size() << endl;
		cout << "after push back lost nodes" << endl;
	}  

	else
	{
		nonBinaryTree::treeNode child = createNode(energy, trackID, motherID, particleName, particleID);

		// define particle generation
		char newChildGen = setParticleGen(searchedNode->generation); 
		child.generation = newChildGen;
		child.mother = searchedNode;

		// increment size of tree
		treeSize++;  
	
		// increment particle count
		particleCount(particleID);  
  
  		/*
  		if (particleID >= 0)
			child.numParticle = countArray[particleID];

		else
			child.numParticle = antiCountArray[(particleID*-1)];
		*/

		// add new node to the back of the children array
		searchedNode->children.push_back(child);
		searchedNode->numChildren = searchedNode->numChildren + 1;

		// sort children in energy order
		int size = searchedNode->numChildren;
		vector <nonBinaryTree::treeNode> temp = sortChildren(searchedNode->children, size);
		searchedNode->children = temp;
	}	
}

// adds the nodes that were given out of order therefore couldn't
// be added initially because the node's mother couldnt be found
void nonBinaryTree::addLeftoverNodes()
{
	for (int i = 0; i < lostNodes.size(); i++)
	{	
		searchedNode = NULL;
		foundNode = false;
		int motherID = lostNodes[i].motherID;

		search(motherID, &root);

		if (foundNode == false)    
		{	
			lostNodes[i].motherID = 1;
			lostNodes[i].generation = setParticleGen(root.generation);
			treeSize++;
			particleCount(lostNodes[i].particleID);
			root.children.push_back(lostNodes[i]);
			root.numChildren = root.numChildren + 1;
			lostNodes[i].mother = &root;

			// sort children in energy order
			int size = root.numChildren;
			vector <nonBinaryTree::treeNode> temp = sortChildren(root.children, size);
			root.children = temp;

			cout << "placed at root " << lostNodes[i].trackID << endl;
		}
  
		else    
		{	 
			// define particle generation
			char newChildGen = setParticleGen(searchedNode->generation); 
			lostNodes[i].generation = newChildGen;

			// increment size of tree
			treeSize++;
	
			// increment particle count
			int partID = lostNodes[i].particleID;

			particleCount(partID);

			// add new node to the back of the children array
			searchedNode->children.push_back(lostNodes[i]);
			searchedNode->numChildren = searchedNode->numChildren + 1;
			lostNodes[i].mother = searchedNode;

			// sort children in energy order
			int size = searchedNode->numChildren;
			vector <nonBinaryTree::treeNode> temp = sortChildren(searchedNode->children, size);
			searchedNode->children = temp;  
		}
	}
}

// sort children in ascending order by energies
// sort algorithm: insertion sort (if numbers get larger then a different algorithm could
// be used due to the time complexity)  
vector <nonBinaryTree::treeNode> nonBinaryTree::sortChildren(vector <treeNode> children, int len)
{
	int j;
	nonBinaryTree::treeNode temp;

	/*
	if (len < 2)
	{
		children[0].numParticle = 1;
		//return children;      
	}

	else
	{
	*/
		for (int i = 0; i < children.size(); i++)
		{
			j = i;

			// compare energies but change placement of nodes
			while (j > 0 && (children[j].trackEnergy < children[j-1].trackEnergy))
			{
				temp = children[j];  
				children[j] = children[j-1];
				//children[j].numParticle = j;
				children[j-1] = temp;
				//children[j-1].numParticle = j + 1;
				j--;
			}  
		}
	//}

	for (int k = 0; k < children.size(); k++)
	{
		children[k].numParticle = k;
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
	//foundNode = false;  
	searchedNode =  NULL;
	foundNode = false;
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
	//foundNode = false;
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
	string currCap = "";
	int numVisited = 0;
	particleIDMap* map = particleIDMap::getInstance();

	if (treeSize == 1)  
		return caption;

	queue <nonBinaryTree::treeNode *> q;
	q.push(rootNode);

	while (q.empty() == false)
	{
		foundNode = false;
		searchedNode = NULL;

		nonBinaryTree::treeNode *temp = q.front();
  		numVisited++;

		if (temp->generation == 'R')
		{
			currCap = "root " + temp->particleName + "-" + temp->generation + to_string(temp->numParticle) + ", ";
			caption = currCap;
			cout << currCap << endl;

			compCap.push_back(map->getNum("root"));
			compCap.push_back(map->getNum(temp->particleName + "-" + temp->generation + to_string(temp->numParticle)));
		}  
  
		else
		{   
			search(temp->motherID, &root);
			char motherGen = searchedNode->generation;
			int motherNum = searchedNode->numParticle;  
			string motherName = pdgToString(searchedNode->particleID);
 
 			if (numVisited == treeSize)
			{
				currCap = motherName + "-" + motherGen + to_string(motherNum) + " created " + temp->particleName + "-" + temp->generation + to_string(temp->numParticle) + " END";
				caption = caption + currCap;
			}

			else
			{
				currCap = motherName + "-" + motherGen + to_string(motherNum) + " created " + temp->particleName + "-" + temp->generation + to_string(temp->numParticle) + ", ";
				caption = caption + currCap;
			}

			// add mother key to vector
			compCap.push_back(map->getNum(motherName + "-" + motherGen + to_string(motherNum)));

			// add daughter key to vector
			compCap.push_back(map->getNum(temp->particleName + "-" + temp->generation + to_string(temp->numParticle)));
	
			cout << currCap << endl;
		}
  
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
	int codes [15] = {1,11,12,13,14,111,211,2212,2112,130,310,311,321,1000010020,22};
	string names [15] = {"neutrino","electron","electron neutrino","muon","muon neutrino","neutral pion","pion+","proton","neutron", "NL-Kaon", "NS-Kaon","N-Kaon","Kaon+","deuteron","photon"};
	string notFound = "unidentified particle";

	for (int i = 0; i < 15; i++)
	{ 
		if (pdgCode == codes[i])
			return names[i];  

		else if (pdgCode == (-1*codes[i]))  
		{
			string name = "anti-" + names[i];  
			return name;
		}  
	}

	// if pdg code not found
	return notFound;
}  

float nonBinaryTree::getRestMass(int pdgCode)
{
	int codes [15] = {1,11,12,13,14,111,211,2212,2112,130,310,311,321,1000010020,22};
	//{"neutrino","electron","electron neutrino","muon","muon neutrino","neutral pion","pion+","proton","neutron", 
	//"NL-Kaon", "NS-Kaon","N-Kaon","Kaon+","deuteron","photon"};
	// rest mass in MeV
	float restMass [15] = {0.0,0.511,0.0,105.7,0.0,134.98,139.57,938.27,939.565,497.7,497.7,497.7,493.7,1875.6,0};
	float notFound = 0.0;

	for (int i = 0; i < 15; i++)
	{ 
		if (pdgCode == codes[i] || pdgCode*-1 == codes[i])
			return restMass[i];
	}

	return notFound;
}

vector <int> nonBinaryTree::getCompCap()
{
	return compCap;
}

void nonBinaryTree::printCompCap()
{
	for (int i = 0; i < compCap.size(); i++)
	{
		cout << compCap[i] << " ";
	}
}



   









