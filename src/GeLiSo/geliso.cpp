#include "geliso.hh"

namespace GeLiSo
{
	using namespace Gecode;
	using namespace MPG;
	using namespace std;
	
/***********************************************CPCLSpace class****************************************/	
	//copy constructor
	GeLiSoSpace::GeLiSoSpace(bool share, GeLiSoSpace& s) : Space(share, s), rv(s.rv) 
	{
		for (int i = 0; i < rv.size(); i++)
	   	{
			rv[i].update(*this, share, s.rv[i]);
			rv[i].setVectorIndex(s.rv[i].getVectorIndex());
		}
	}
	
	//constructor 
	GeLiSoSpace::GeLiSoSpace(void)
	{
		//used to avoid copying the vector in memory (when adding a ne variable) and loose the references used outside of the class.
		//TODO : find a cleaner way to avoid this problem
		rv.reserve(1000);
		
	}
	//destructor
	GeLiSoSpace::~GeLiSoSpace(void)
	{
	}
	
	//copy method
	Space* GeLiSoSpace::copy(bool share)
	{
		return new GeLiSoSpace(share,*this);
	}
	
	//print methods
	void GeLiSoSpace::print(std::ostream& os) const
	{
		os << std::endl << std::endl << std::endl << std::endl << std::endl;
		os << "*************************************************" << std::endl;
		os << "The GeLiSoSpace is now printed below : " << std::endl;
	    for (int i = 0; i < rv.size(); i++)
	   	{
			os << "Variable number : " << i << std::endl;
			os << "\trv[" << i << "]: " << rv[i] << std::endl;
		}
		os << "No more variable" << std::endl;
		os << "*************************************************" << std::endl;
		os << std::endl << std::endl << std::endl << std::endl << std::endl;
		
	}
	
	void GeLiSoSpace::print(void) const 
	{
		print(cerr);
	}
	
	//get vector size
	int GeLiSoSpace::getVectorSize(void)
	{
		return rv.size();
	}
	
	//getVector
	std::vector<GeLiSoCPRelVar>* 
	GeLiSoSpace::getVectorAdress(void)
	{
		return &rv;
	}
	
	//create a new CPRelVar and add it to the vector
	GeLiSoCPRelVar&
	GeLiSoSpace::newCPRelVar(const MPG::GRelation& l, const MPG::GRelation& u)
	{
		GeLiSoCPRelVar* newVar = new GeLiSoCPRelVar(*this,l,u);
		rv.push_back(*newVar);
        rv.back().setVectorIndex(rv.size() - 1);
        return rv.back();
	}
	
	//get the CPRelVar at a given index in rv
	GeLiSoCPRelVar&
    GeLiSoSpace::getGeLiSoCPRelVar(int index)
	{
		return rv[index];
	}
	
	//function useful to debug
	void GeLiSoSpace::debug(void)
	{
		
		
		cout << "******************Here is the debug informations********************" << endl;
		cout << endl << endl << endl << endl;
		
		
		cout << "rv adress : " << &rv << endl;
		
		cout << "variable addresses : " << endl;
		for (int i = 0; i < rv.size(); i++)
	   	{
			cout << "Variable number : " << i << std::endl;
			cout << "\trv[" << i << "]: " << &(rv[i]) << std::endl;
		}
		
		cout << "variable indexes : " << endl;
		for (int i = 0; i < rv.size(); i++)
	   	{
			cout << "Variable number : " << i << std::endl;
			cout << "\trv[" << i << "]: " << rv[i].getVectorIndex() << std::endl;
		}
		
		cout << "variables : " << endl;
		
		print();
		
		cout << endl << endl << endl << endl;
		cout << "******************Debug done********************" << endl;
	}
	
	
/***********************************************CPCLCPRelVar class****************************************/		
	
	//default constructor
	GeLiSoCPRelVar::GeLiSoCPRelVar(void){}
	
	//constructor
	GeLiSoCPRelVar::GeLiSoCPRelVar(GeLiSoSpace& home, const GRelation& l, const GRelation& u):MPG::CPRelVar(home, l, u)
    {
      vectorIndex = -1;
    }

	//copy constructor
	GeLiSoCPRelVar::GeLiSoCPRelVar(const GeLiSoCPRelVar& y):MPG::CPRelVar(y)
	{
		vectorIndex = y.vectorIndex;
	}

	//get and set
    int GeLiSoCPRelVar::getVectorIndex(void) const
    {
      return vectorIndex;
    }
    void GeLiSoCPRelVar::setVectorIndex(int newIndex)
    {
      vectorIndex = newIndex;
    }

/***********************************************CPCLEngine class****************************************/		

	// Constructor
	GeLiSoEngine::GeLiSoEngine(GeLiSoSpace* sp, int strategyID, const Search::Options& o)
	{
		using namespace Search;
		switch (strategyID)
		{
			//dfs strategy
		     case 0: 
			{
		          	cout << "Engine with DFS strategy will be constructed" << endl;
					e = dfs(sp,sizeof(GeLiSoSpace),o);
		          	break;
		    }
			//bab strategy
		    case 1:
		   {
		          cout << "Engine with BAB strategy constructed" << endl;
				  e = bab(sp,sizeof(GeLiSoSpace),o);
		          break;
		    }
			//restart strategy
		    case 2:
		   {
		          cout << "Engine with Restart strategy constructed" << endl;
				  e = restart(sp,sizeof(GeLiSoSpace),o);
		
		    }
		}
	}
	
	//next function (behaviour depend on the chosen strategy)
	GeLiSoSpace* GeLiSoEngine::next(void)
	{
		return dynamic_cast<GeLiSoSpace*>(e->next());
	}
	
	/// Return statistics
    Search::Statistics GeLiSoEngine::statistics(void) const
		{
			return e->statistics();
		}
    /// Check whether engine has been stopped
    bool GeLiSoEngine::stopped(void) const
		{
			return e->stopped();
		}
    /// Destructor
    GeLiSoEngine::~GeLiSoEngine(void)
		{
			delete e;
		}


/******************************************************************************************************/
	
}

