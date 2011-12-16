#include "translator.hh"
#include "../GeLiSo/geliso.hh"


namespace GeLiSo
{

using namespace boost::uuids;
using namespace std;
	
	
string applyMessage(variableMap& varmap, string message)
{
	uuid* newUUID;
	string ack;
	
	if (!strcmp(message.c_str(), "newSpace"))
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
	
	if (!strcmp(message.c_str(), "search"))
	{
		ack = "We will begin the search";
	}
	
	
	//return the ack (uuid if we created a new variable)
	return ack;
	
}

}