#include "translator.hh"
#include "../GeLiSo/geliso.hh"


namespace GeLiSo
{

using namespace boost::uuids;
using namespace std;

using namespace MPG;
	
	
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
		    printf ("%s\n",messageTokens);
			paramList.push_back(strtol(messageTokens,NULL,10));
			messageTokens = strtok (NULL, " ");
		  }
		
		cout << paramList << endl;
		
		//we create the new tuple
		Tuple* newTuple = new Tuple(paramList);
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = newTuple;
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>(*newUUID);
		
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
		
		//we create the new (empty) GRelation
		GeLiSoCPRelVar& newCPRelVar = sp->newCPRelVar(*glb,*lub);
		
		//we add the variable and its uuid in the map
		varmap[*newUUID] = &newCPRelVar;
		
		cout << newCPRelVar << endl;
		
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
		
		//the UUID as a string is the ack
		ack = boost::lexical_cast<std::string>("The variable has been branched");
		
	}
	
	if (!strcmp(functionToApply, "search"))
	{
		
		//string stream used to get the uuid
		stringstream sssp;
		
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
		GeLiSoEngine engine(GeLiSoEngine(sp, strategyID));
		//the solution space
		GeLiSoSpace* sol;
		
		sol = engine.next();
		
		sol->print();
		
		ack = "Search done";
	}
	
	
	//return the ack (uuid if we created a new variable)
	return ack;
	
}


}