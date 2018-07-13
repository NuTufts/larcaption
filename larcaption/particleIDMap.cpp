
#include <iostream>
#include <string>
#include <map>
#include "particleIDMap.hpp"

using namespace std;  


particleIDMap::particleIDMap()  
{  
	numKey = 0;
	particleNum.insert(pair <string, int> ("END",numKey));
	numKey++;
	setLeptons(); 
	setBaryons();  
	setKaons();
	setOthers();
}  

void particleIDMap::setLeptons()
{
	//particleNum.insert(pair <string, int> ("electron-A0",2));

	string elec = "electron-";
	string muon = "muon-";
	int depth = 5;
	int breadth = 8;
	char letter = 'A';  
	string eKey = elec;
	string mKey = muon;

	// electrons
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		eKey = elec + letter;

		for (int j = 0; j < breadth; i++)
		{
			eKey = eKey + to_string(j);
			particleNum.insert(pair <string, int> (eKey,numKey));
			numKey++;
		}
	}  

	// muons
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		mKey = muon + letter;

		for (int j = 0; j < breadth; i++)
		{
			mKey = mKey + to_string(j);
			particleNum.insert(pair <string, int> (mKey,numKey));
			numKey++;
		}
	}
}

void particleIDMap::setBaryons()
{
	string proton = "proton-";
	string neutron = "neutron-";
	int depth = 5;
	int breadth = 8;
	char letter = 'A';
	string pKey = proton;
	string nKey = neutron;

	// protons
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		pKey = proton + letter;

		for (int j = 0; j < breadth; i++)
		{
			pKey = pKey + to_string(j);
			particleNum.insert(pair <string, int> (pKey,numKey));
			numKey++;
		}
	}

	// neutrons
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		nKey = neutron + letter;  

		for (int j = 0; j < breadth; i++)
		{
			nKey = nKey + to_string(j);
			particleNum.insert(pair <string, int> (nKey,numKey));
			numKey++;
		}
	}
}

void particleIDMap::setOthers()
{
	// neutral pion pi+ "NL-Kaon","NS-Kaon","N-Kaon","Kaon+","deuteron","photon"
	// ,"neutral pion","pion+"
	string nPion = "neutral pion-";
	string piPlus = "pion+-";
	string deut = "deuteron-";
	string photon = "photon-";
	int depth = 5;  
	int breadth = 8;
	char letter = 'A';
	string key = nPion;

	// neutral pion
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = nPion + letter;

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// pion+
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = piPlus + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// deuteron
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = deut + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}
     
	// photon
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = photon + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// unidentified particle
	letter = 'A';
	string UP = "unidentified particle";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = UP + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

}

void particleIDMap::setKaons()
{
	string NLKaon = "NL-Kaon-";
	string NSKaon = "NS-Kaon";
	string NKaon = "N-Kaon-";
	string KPlus = "Kaon+-";
	int depth = 5;
	int breadth = 8;
	char letter = 'A';
	string key = NLKaon;

	// NL Kaon
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = NLKaon + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// NS Kaon
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = NSKaon + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}  
	}

	// neutral kaon
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = NKaon + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// kaon+
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = KPlus + letter;  

		for (int j = 0; j < breadth; i++)
		{
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}
}

void getMap()
{

}


















