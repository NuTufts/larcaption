


#include <iostream>
#include <string>
#include "nonBinaryTree.hpp"
using namespace std;

/*
 * this script shows that the following functions work:
 * addNode, sortChildren, printTree, printChidlren, search
 * depthTrav, isLeaf, all of the get functions, createNode, private print function
 */

int main()  
{  
	nonBinaryTree *newTree = new nonBinaryTree;

	int motherID = 1, trackID = 2;
	float energy = 0.511; //MeV
	string particleName = "2";

	int trackID1 = 3;
	float energy1 = 102.0; //MeV 
	string particleName1 = "3";

	int trackID2 = 4;
	float energy2 = 17; //MeV
	string particleName2 = "5";

	int trackID3 = 4;
	float energy3 = 18; //MeV
	string particleName3 = "6";   
 
	//newTree->getTreeSize();  

	newTree->addNode(motherID,trackID,energy,particleName,0); // neutrino child 2

	newTree->addNode(trackID,trackID3,energy3,particleName3,1); // 18 3rd child of neutrino child 2

	//newTree->getTreeSize(); 

	//newTree->getNumChildren(trackID);
	//newTree->printTree();  

	newTree->addNode(motherID,trackID1,energy1,particleName1,1); // neutrino child 3

	//newTree->printChildren(motherID);

	newTree->addNode(trackID,trackID2,energy2,particleName2,1); // 17 second chld of neutrino 2
	newTree->addNode(trackID,7,15.0,"4",1); // 15 smallest child of neutrino child 2

	newTree->addNode(motherID,8,0.001,"1",1); // neutrino child 1

	string cap = newTree->publicBreadthTrav();

	//cout << endl;  

	//cout << cap << endl;

	//newTree->printChildren(motherID);
	//newTree->printChildren(trackID);
	//newTree->printTree();

	//string cap = newTree->publicDepthTrav();

	cout << endl; 
	cout << cap << endl;

	//newTree->particleNumber(1);

	delete newTree;

	//newTree->getNumChildren(trackID);
	//newTree->printTree();
	//newTree->printRootChildren();

}













