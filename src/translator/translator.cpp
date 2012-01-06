#include "translator.hh"
#include "../GeLiSo/geliso.hh"


namespace GeLiSo
{

using namespace boost::uuids;
using namespace std;

using namespace MPG;

//global variable used in the visitor
stringstream globalvisitorstream("");

//function used as a functor to the visit function
void visitor(const vector<int>& tuple)
{
	globalvisitorstream << tuple << "-"; 
}
	
	
string applyMessage(variableMap& varmap, string message)
{
	
	uuid* newUUID;
	string ack;
	
	//token of the message (used to get different parameters)
	char* messageTokens = strtok(const_cast<char *>(message.c_str())," ");
	
	//The first token of the message must be the name of the function to apply
	char* functionToApply = messageTokens;
	
	
	
	
	if (!strcmp(functionToApply, "newSpace"))
	{
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//we create the new space
		GeLiSoSpace* newSpace = new GeLiSoSpace();
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = newSpace;
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>(*newUUID);
		
	}
	
	if (!strcmp(functionToApply, "newTuple"))
	{
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//list of parameters to pass at the function
		vector<int> paramList;
		
		//fill the parameter list
		messageTokens = strtok (NULL, " ");//go to first component
		while (messageTokens != NULL)
		  {
			paramList.push_back(strtol(messageTokens,NULL,10));
			messageTokens = strtok (NULL, " ");
		  }
		
		//we create the new tuple
		Tuple* newTuple = new Tuple(paramList);
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = newTuple;
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>(*newUUID);
		
	}
	
	if (!strcmp(functionToApply, "getTupleArity"))
	{
		//string streams used to get the uuid
		stringstream sstuple;
		
		//get the tuple (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sstuple << messageTokens;
		sstuple >> spUUID;
		Tuple* t = (Tuple*) varmap[spUUID];
						
		ack = boost::lexical_cast<std::string>(t->arity());
		
	}
	
	if (!strcmp(functionToApply, "newGRelation"))
	{
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//get the arity of the new ground relation
		messageTokens = strtok (NULL, " ");
		
		//we create the new (empty) GRelation
		GRelation* newGRelation = new GRelation(strtol(messageTokens,NULL,10));
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = newGRelation;
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>(*newUUID);
		
	}
	
	//add a tuple to a ground relation
	if (!strcmp(functionToApply, "GRelation-AddTuple"))
	{
		//string streams used to get the uuids
		stringstream ssgr;
		stringstream sstu;
		
		//get the ground relation (first parameter)
		messageTokens = strtok (NULL, " ");//next token
		boost::uuids::uuid grUUID;
		ssgr << messageTokens;
		ssgr >> grUUID;
		GRelation* gr = (GRelation*) varmap[grUUID];
		
		//get the tuple (second parameter)
		messageTokens = strtok (NULL, " ");//next token
		boost::uuids::uuid tuUUID;
		sstu << messageTokens;
		sstu >> tuUUID;
		Tuple* tu = (Tuple*) varmap[tuUUID];
		
		//add the tuple
		gr->add(*tu);
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>("The tuple has been added to the ground relation");
		
	}	
	
	if (!strcmp(functionToApply, "newCPRelVar"))
	{
		//string streams used to get the uuids
		stringstream sssp;
		stringstream ssglb;
		stringstream sslub;
		
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//get the glb (second parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid glbUUID;
		ssglb << messageTokens;
		ssglb >> glbUUID;
		GRelation* glb = (GRelation*) varmap[glbUUID];
		
		//get the lub (third parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid lubUUID;
		sslub << messageTokens;
		sslub >> lubUUID;
		GRelation* lub = (GRelation*) varmap[lubUUID];
		
		//we create the new CPRelVar
		GeLiSoCPRelVar& newCPRelVar = sp->newCPRelVar(*glb,*lub);
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = &newCPRelVar;
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>(*newUUID);
		
	}
	
	if (!strcmp(functionToApply, "branch"))
	{
		//string streams used to get the uuids
		stringstream sssp;
		stringstream sscprelvar;
		
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//get the cprelvar (second parameter)
		messageTokens = strtok (NULL, " ");//next token
		boost::uuids::uuid cprelvarUUID;
		sscprelvar << messageTokens;
		sscprelvar >> cprelvarUUID;
		GeLiSoCPRelVar* cprelvar = (GeLiSoCPRelVar*) varmap[cprelvarUUID];
		
		//branch the variable
		branch(*sp,*cprelvar);
		
		ack = boost::lexical_cast<std::string>("The variable has been branched");
		
	}
	
	if (!strcmp(functionToApply, "newSearchEngine"))
	{
		//string stream used to get the uuid
		stringstream sssp;
		
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//get the strategyID (second parameter)
		messageTokens = strtok (NULL, " ");//next token
		int strategyID = (int) strtol(messageTokens,NULL,10);
		
		//the search engine
		GeLiSoEngine* engine = new GeLiSoEngine(sp, strategyID);
		//Gecode::DFS<GeLiSoSpace>* engine= new Gecode::DFS<GeLiSoSpace>(sp);
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = engine;
		
		//UUID of the search engine
		ack = boost::lexical_cast<std::string>(*newUUID);
		
	}
	
	if (!strcmp(functionToApply, "nextSolution"))
	{
		
		//string stream used to get the uuid
		stringstream sssp;
		stringstream ssse;
		
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//get the search engine (second parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid seUUID;
		ssse << messageTokens;
		ssse >> spUUID;
		GeLiSoEngine* se = (GeLiSoEngine*) varmap[spUUID];
		
		//the solution space
		GeLiSoSpace* sol;
		
		sol = se->next();
		
		if(sol)//if there is a (next) solution
		{
			//we add the variable and its uuid in the map
			varmap[*newUUID] = sol;

			//UUID of the search engine
			ack = boost::lexical_cast<std::string>(*newUUID);
			
		}
		else//if not
		{
			ack = "0";
		}
		
	}
	
	if (!strcmp(functionToApply, "quitGecode"))
	{
		//TODO : free all the memory here
		
		//the ack will be used to quit the main loop
		ack = "Quit";
	}
	
	if (!strcmp(functionToApply, "getVarInSpace"))
	{
		//string streams used to get the uuids
		stringstream sssp;
		stringstream sscprelvar;
		
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//get the cprelvar of the model space (second parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid cprelvarUUID;
		sscprelvar << messageTokens;
		sscprelvar >> cprelvarUUID;
		GeLiSoCPRelVar* cprelvar = (GeLiSoCPRelVar*) varmap[cprelvarUUID];
				
		//get the cprelvar of the space sp
		GeLiSoCPRelVar& solcprelvar = sp->getGeLiSoCPRelVar(cprelvar->getVectorIndex());
		
		//get the glb (the ground relation, equal to lub in a solution space)
		GRelation solgr = solcprelvar.glb();
		
		//get a vector of vector representing the ground relation
		//empty the global stream
		globalvisitorstream.clear();
		globalvisitorstream.str("");
		
		//add all the tuple of the ground relation
		solgr.visit(&visitor);
		
		globalvisitorstream >> ack;
		
		
		
	}
	
	if (!strcmp(functionToApply, "Constraint"))
	{
		//get the constraint name
		messageTokens = strtok (NULL, " ");
		char* constr = messageTokens;
		
		//string streams used to get the uuids
		stringstream sssp;
		stringstream ssrelA;
		stringstream ssrelB;
		stringstream ssrelC;
		stringstream ssgr;
		
		//UUIDs
		boost::uuids::uuid spUUID;
		boost::uuids::uuid relAUUID;
		boost::uuids::uuid relBUUID;
		boost::uuids::uuid relCUUID;
		boost::uuids::uuid grUUID;
		
		if (!strcmp(constr, "equal"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			equal(*sp,*relA,*relB);
			
		}
		
		if (!strcmp(constr, "complement"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			complement(*sp,*relA,*relB);
			
		}
		
		if (!strcmp(constr, "intersect"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			intersect(*sp,*relA,*relB,*relC);
						
		}
		
		if (!strcmp(constr, "union"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			Union(*sp,*relA,*relB,*relC);
			
		}
		
		if (!strcmp(constr, "subset"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			subset(*sp,*relA,*relB);
			
		}
		
		if (!strcmp(constr, "disjoint"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			disjoint(*sp,*relA,*relB);
			
		}
		
		if (!strcmp(constr, "implies"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			implies(*sp,*relA,*relB,*relC);
			
		}
		
		if (!strcmp(constr, "projection"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the integer (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			int p = strtol(messageTokens,NULL,10);
			
			//get the relA (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the relB (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			projection(*sp,p,*relA,*relB);
			
		}
		
		if (!strcmp(constr, "join"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the integer (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			int j = strtol(messageTokens,NULL,10);
			
			//get the relB (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fifth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			join(*sp,*relA,j,*relB,*relC);
			
		}
		
		if (!strcmp(constr, "follow"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the integer (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			int f = strtol(messageTokens,NULL,10);
			
			//get the relB (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fifth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			follow(*sp,*relA,f,*relB,*relC);
			
		}
		
		if (!strcmp(constr, "divide"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the integer (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			int d = strtol(messageTokens,NULL,10);
			
			//get the relB (fourth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelB << messageTokens;
			ssrelB >> relBUUID;
			GeLiSoCPRelVar* relB = (GeLiSoCPRelVar*) varmap[relBUUID];
			
			//get the relC (fifth parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelC << messageTokens;
			ssrelC >> relCUUID;
			GeLiSoCPRelVar* relC = (GeLiSoCPRelVar*) varmap[relCUUID];
			
			divide(*sp,*relA,d,*relB,*relC);
			
		}
		
		if (!strcmp(constr, "include"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the gr (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssgr << messageTokens;
			ssgr >> grUUID;
			GRelation* gr = (GRelation*) varmap[grUUID];
			
			include(*sp,*relA,*gr);
			
		}
		
		if (!strcmp(constr, "exclude"))
		{
			//get the space (first parameter)
			messageTokens = strtok (NULL, " ");		
			sssp << messageTokens;
			sssp >> spUUID;
			GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
			
			//get the relA (second parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssrelA << messageTokens;
			ssrelA >> relAUUID;
			GeLiSoCPRelVar* relA = (GeLiSoCPRelVar*) varmap[relAUUID];
			
			//get the gr (third parameter)
			messageTokens = strtok (NULL, " ");//next token
			ssgr << messageTokens;
			ssgr >> grUUID;
			GRelation* gr = (GRelation*) varmap[grUUID];
			
			exclude(*sp,*relA,*gr);
			
		}
		
		ack = boost::lexical_cast<std::string>("Constraint posted");
		
	}
	
	if (!strcmp(functionToApply, "printSpace"))
	{
		
		//string stream used to get the uuid
		stringstream sssp;
				
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
		//fill a stream with the space content
		std::stringstream os;
	    sp->print(os);
				
		//ack the string representation of the space
		ack = boost::lexical_cast<std::string>(os.str().c_str());
	}
	
	
	if (!strcmp(functionToApply, "debugSpace"))
	{
		
		//string stream used to get the uuid
		stringstream sssp;
				
		//get the space (first parameter)
		messageTokens = strtok (NULL, " ");		
		boost::uuids::uuid spUUID;
		sssp << messageTokens;
		sssp >> spUUID;
		GeLiSoSpace* sp = (GeLiSoSpace*) varmap[spUUID];
		
	    sp->debug();
				
		//ack the string representation of the space
		ack = boost::lexical_cast<std::string>("check C++ side for debug informations");
	}
	
	
	//return the ack (uuid if we created a new variable)
	return ack;
	
}

}