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
			cout << "Var" << i << "copied" << endl;
			rv[i].update(*this, share, s.rv[i]);
			rv[i].setVectorIndex(s.rv[i].getVectorIndex());
		}
		cout << "GeLiSoSpace copy constructed" << endl;
	}
	
	//constructor 
	GeLiSoSpace::GeLiSoSpace(void)
	{
		/*freopen ("/tmp/mystdout.txt","w",stdout);
		freopen ("/tmp/mystderr.txt","w",stderr);
		std::cout << "Redirected stdout." << std::endl;
		std::cerr << "Redirected stderr." << std::endl;
		cout << "CPCLSpace constructed" << endl;
		cout << "Here is rv.size() : " << (int) rv.size() << endl;
		cerr << "Here is rv.size() : " << (int) rv.size() << endl;
		rv.reserve(1000); //TODO : fix the problem solved by using this line. This line shoudln't have to be used
		cout << "Here is rv.size() : " << (int) rv.size() << endl;
		cerr << "Here is rv.size() : " << (int) rv.size() << endl;*/
	}
	//destructor
	GeLiSoSpace::~GeLiSoSpace(void)
	{
		/*cout << "CPCLSpace destructed" << endl;
		fclose(stdout);
	    fclose(stderr);*/
	}
	
	//copy method
	Space* GeLiSoSpace::copy(bool share)
	{
		cout << "GeLiSoSpace : copy method called" << endl;
		return new GeLiSoSpace(share,*this);
	}
	
	//print methods
	void GeLiSoSpace::print(std::ostream& os) const
	{
		os << "The GeLiSoSpace is now printed below : " << std::endl;
	    for (int i = 0; i < rv.size(); i++)
	   	{
			os << "Variable number" << i << std::endl;
			os << "\trv[" << i << "]: " << rv[i] << std::endl;
		}
		os << "No more variable" << std::endl;
		
	}
	
	void GeLiSoSpace::print(void) const 
	{
		print(cout);
	}
	
	//get vector size
	int GeLiSoSpace::getVectorSize(void)
	{
		return rv.size();
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
	
	
/***********************************************CPCLCPRelVar class****************************************/		
	
	//default constructor
	GeLiSoCPRelVar::GeLiSoCPRelVar(void){}
	
	//constructor
	GeLiSoCPRelVar::GeLiSoCPRelVar(GeLiSoSpace& home, const GRelation& l, const GRelation& u):MPG::CPRelVar(home, l, u)
    {
      vectorIndex = -1;
    }

	//get and set
    int GeLiSoCPRelVar::getVectorIndex(void)
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
		          	cout << "Engine with DFS strategy constructed" << endl;
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

