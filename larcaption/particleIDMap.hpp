#include <iostream>
#include <string>
#include <map>
using namespace std;

#ifndef PARTICLE_ID_MAP_H
#define PARTICLE_ID_MAP_H 
 
class particleIDMap    
{    
	public:
  
  		// default constructor 
		particleIDMap();

		void getMap(); 

	private:  

		map <string, int> particleNum;
		int numKey;

		void setLeptons();
		void setBaryons();
		void setKaons();
		void setOthers();
};  

#endif  