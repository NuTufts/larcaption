#include <iostream>
#include <string>
#include <map>
using namespace std;

#ifndef PARTICLE_ID_MAP_H
#define PARTICLE_ID_MAP_H 
 
class particleIDMap    
{    
	public:
  
  		// string getString(int num);
  		int getNum(string term);

  		static particleIDMap* getInstance();
  		void resetInstance();

		//static const A& get();  

	private:  
 
		map <string, int> particleNum;
		int numKey = 0;

		void setLeptons();
		void setBaryons();  
		void setKaons();
		void setOthers();
  
		// default constructor   
		particleIDMap();
		~particleIDMap();

		static particleIDMap* mapInstance;

		/*
		A():
		~A();
		Static A* -global;

		// in cpp
		A* A::-g instance = NULL;
		
		//for get()
		const A& A::get()
		{
			if (A::_ginstance == NULL)
				A::_ginstance = new A();
			return *(A::ginstance);
		} */

};  

#endif  