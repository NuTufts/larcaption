/*
	Header file for class to build a non-binary tree from truth information such
	that it can be traversed to create sentences describing interactions.
*/  

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std; 

#ifndef NON_BINARY_TREE_H
#define NON_BINARY_TREE_H
    
class nonBinaryTree 
{
	public:

		// default constructor   
		nonBinaryTree();

		// parametrized constructor
		nonBinaryTree(float rootEnergy, int rootTrackID);

		// destructor  
		~nonBinaryTree();

		void addNode(int motherID, int trackID, float energy, string particleName, int particleID);

		void printTree();
 
		void getTreeSize();

		void getNumChildren(int particleID);

		void printRootChildren();  

		void printChildren(int trackID); 

		string publicBreadthTrav();  

		void particleNumber(int trackID);

		string publicDepthTrav();

		string pdgToString(int pdgCode); 

		void addLeftoverNodes();  

		float getRestMass(int pdgCode);

		vector <int> getCompCap();

		void printCompCap();

	private:  
        
		struct treeNode {
			float trackEnergy; // in MeV
			int trackID;  
			string particleName;  
			int particleID;

			int motherID; // ask if unique
			vector <treeNode> children; 
			int numChildren; 
			char generation;  
			treeNode *mother;  

			// if there are multiple occurrences of a particle type this
			// records which one the node is (e.i. the order)
			int numParticle = 0;    
		};  
  
		int treeSize;       
		treeNode root;       
		treeNode *searchedNode;
		bool foundNode;  
		vector <int> compCap;
  
		// vector of the nodes that were printed out of order 
		vector <treeNode> lostNodes;
  
		//int countArray[100] = {0}; 
		//int countArray[3000] = {0};
		int countArraySize;
		int antiCountArraySize;
		int *countArray = new int[3000];
		int *antiCountArray = new int[3000];
        
		vector <string> *depthCap;   
  
		vector <treeNode> sortChildren(vector <treeNode> children, int len);  

		treeNode createNode(float energy, int trackID, int motherID, string particleName, int particleID);

		bool isLeaf(treeNode *currNode);
    
    	/* 
    	 * every time search is called - foundNode and searchedNode must be reset
    	 * note: this is done within these functions already this is just a reminder 
    	 * functions that call search:
    	 * 1. search
    	 * 2. addNode
    	 * 3. getNumChildren
    	*/  

		void search(int ID_num, treeNode *currNode);
		void depthTrav(treeNode *currNode);  
  
		char setParticleGen(char motherGen);
		void particleCount(int particleID);
		void antiParticleCount(int particleID);

		string vecToString(vector <string> cap);

		void print(vector <string> *caption);
		string breadthTrav(treeNode *root);
};

#endif




