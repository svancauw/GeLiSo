#ifndef __CPCL_HPP__
#define __CPCL_HPP__

#include <gecode/kernel.hh>
#include <gecode/int.hh>
#include <gecode/set.hh>
#include <gecode/search.hh>

#include <cprel/cprel.hh>
#include <rel/grelation.hh>
	
#include <vector>

namespace GeLiSo
{
	//class declaration
	class GeLiSoCPRelVar;
	
	/***********************************************GeLiSoSpace class****************************************/		
	class GeLiSoSpace : public Gecode::Space
	{
	private:
		//copy constructor
		GeLiSoSpace(bool share, GeLiSoSpace& s);
		//vector of relational variables, to be filled for a given constraint problem
		std::vector<GeLiSoCPRelVar> rv;
	public:	
		
		//constructor 
		GeLiSoSpace(void);
		//destructor
		virtual ~GeLiSoSpace(void);
		//copy method
		virtual Space* copy(bool share);
		
		//print methods
		void print(std::ostream& os) const;
		void print(void) const;
		
		//get vector size
		int getVectorSize(void);
		
		//create a new CPRelVar and add it to the vector
		GeLiSoCPRelVar&
	    newCPRelVar(const MPG::GRelation& l, const MPG::GRelation& u);
	
		//get the CPRelVar at a given index in rv
		GeLiSoCPRelVar&
	    getGeLiSoCPRelVar(int index);
		
	};

	/***********************************************GeLiSoCPRelVar class****************************************/		
	class GeLiSoCPRelVar: public MPG::CPRelVar
	{
	private:
		int vectorIndex;
		GeLiSoCPRelVar(void);//default constructor
	public:
		//constructor
		GeLiSoCPRelVar(GeLiSoSpace& home, const MPG::GRelation& l, const MPG::GRelation& u);//:MPG::CPRelVar(home, l, u);
		//get and set
		int getVectorIndex(void);
		void setVectorIndex(int newIndex);	
	};
	
	/***********************************************GeLiSoEngine class****************************************/		
	
    class GeLiSoEngine
 	{
	private:
		/// The actual search engine
	    Gecode::Search::Engine* e;
    public:
      	// Constructor
		//strategyID is used to choose between the different strategies provided by Gecode
		GeLiSoEngine(GeLiSoSpace* sp, int strategyID, const Gecode::Search::Options& o=Gecode::Search::Options::def);
		//next function (behaviour depend on the chosen strategy)
		GeLiSoSpace* next(void);
		/// Return statistics
	    Gecode::Search::Statistics statistics(void) const;
	    /// Check whether engine has been stopped
	    bool stopped(void) const;
	    /// Destructor
	    ~GeLiSoEngine(void);
    };
	
}


#endif