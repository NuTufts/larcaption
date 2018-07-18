
#include <iostream>
#include <string>
#include <map>
#include "particleIDMap.hpp"

using namespace std;  

particleIDMap* particleIDMap::mapInstance = NULL;
  
particleIDMap::particleIDMap()  
{  
	cout << "running constructor " << endl;
	numKey = 0;
	particleNum.insert(pair <string, int> ("END",numKey));
	numKey++;
	particleNum.insert(pair <string, int> ("root",numKey));
	numKey++;
	particleNum.insert(pair <string, int> ("neutrino-R1",numKey));
	numKey++;
	setLeptons(); 
	setBaryons();    
	setKaons();      
	setOthers();
}  

particleIDMap::~particleIDMap()
{
	particleNum.clear();
}

void particleIDMap::resetInstance()
{
	delete mapInstance;
	mapInstance = NULL;
}

void particleIDMap::setLeptons()
{
	//particleNum.insert(pair <string, int> ("electron-A0",2));

	string elec = "electron-";
	string muon = "muon-";
	int depth = 3;
	int breadth = 7;
	char letter = 'A';  
	string eKey = elec;
	string mKey = muon;

	// electrons
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		eKey = elec + letter;

		for (int j = 0; j < breadth; j++)
		{
			eKey = elec + letter;
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

		for (int j = 0; j < breadth; j++)
		{
			mKey = muon + letter;
			mKey = mKey + to_string(j);
			particleNum.insert(pair <string, int> (mKey,numKey));
			numKey++;
		}
	}


	/***************** ANTI PARTICLES ********************/

	// electrons
	letter = 'A';
	string anti = "anti-";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		eKey = anti + elec + letter;

		for (int j = 0; j < breadth; j++)
		{
			eKey = anti + elec + letter;
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
		mKey = anti + muon + letter;

		for (int j = 0; j < breadth; j++)
		{
			mKey = anti + muon + letter;
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
	int depth = 3;
	int breadth = 7;
	char letter = 'A';
	string pKey = proton;
	string nKey = neutron;

	// protons
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		pKey = proton + letter;

		for (int j = 0; j < breadth; j++)
		{
			pKey = proton + letter;
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

		for (int j = 0; j < breadth; j++)
		{
			nKey = neutron + letter;
			nKey = nKey + to_string(j);
			particleNum.insert(pair <string, int> (nKey,numKey));
			numKey++;
		}
	}

	/***************** ANTI PARTICLES ********************/

	// protons
	letter = 'A';
	string anti = "anti-";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		pKey = anti + proton + letter;

		for (int j = 0; j < breadth; j++)
		{
			pKey = anti + proton + letter;
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
		nKey = anti + neutron + letter;  

		for (int j = 0; j < breadth; j++)
		{
			nKey = anti + neutron + letter;
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
	int depth = 3;  
	int breadth = 7;
	char letter = 'A';
	string key = nPion;

	// neutral pion
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = nPion + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = nPion + letter;
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

		for (int j = 0; j < breadth; j++)
		{
			key = piPlus + letter; 
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

		for (int j = 0; j < breadth; j++)
		{
			key = deut + letter; 
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

		for (int j = 0; j < breadth; j++)
		{
			key = photon + letter; 
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// unidentified particle
	letter = 'A';
	string UP = "unidentified particle-";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = UP + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = UP + letter; 
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	/***************** ANTI PARTICLES ********************/

	// neutral pion
	letter = 'A';
	string anti = "anti-";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = anti + nPion + letter;

		for (int j = 0; j < breadth; j++)
		{
			key = anti + nPion + letter;
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
		key = anti + piPlus + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + piPlus + letter; 
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
		key = anti + deut + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + deut + letter; 
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
		key = anti + photon + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + photon + letter; 
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	// unidentified particle
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = anti + UP + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + UP + letter; 
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
	int depth = 3;
	int breadth = 7;
	char letter = 'A';
	string key = NLKaon;

	// NL Kaon
	letter = 'A';
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = NLKaon + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = NLKaon + letter;
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

		for (int j = 0; j < breadth; j++)
		{
			key = NSKaon + letter; 
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

		for (int j = 0; j < breadth; j++)
		{
			key = NKaon + letter; 
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

		for (int j = 0; j < breadth; j++)
		{
			key = KPlus + letter;
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

	/***************** ANTI PARTICLES ********************/

	// NL Kaon
	letter = 'A';
	string anti = "anti-";
	for (int i = 0; i < depth; i++)
	{
		letter = letter + i;
		key = anti + NLKaon + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + NLKaon + letter;
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
		key = anti + NSKaon + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + NSKaon + letter; 
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
		key = anti + NKaon + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + NKaon + letter; 
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
		key = anti + KPlus + letter;  

		for (int j = 0; j < breadth; j++)
		{
			key = anti + KPlus + letter;
			key = key + to_string(j);
			particleNum.insert(pair <string, int> (key,numKey));
			numKey++;
		}
	}

}

particleIDMap* particleIDMap::getInstance()
{
	if (mapInstance == NULL)
	{
		mapInstance = new particleIDMap();
	}  

	return mapInstance;
}

/*
string particleIDMap::getString(int num)
{
	string stringKey = particleNum.find(num)->first;
	return stringKey;
}
*/

int particleIDMap::getNum(string term)
{ 
	int numKey = particleNum.find(term)->second;
	return numKey;
}













