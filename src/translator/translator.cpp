#include "translator.hh"

using namespace boost::uuids;
using namespace std;

uuid* applyMessage(variableMap& varmap, string message)
{
	uuid* newUUID = NULL;
	
	if (!strcmp(message.c_str(), "newSpace"))
	{
		//we create the new uuid for the new variable
		newUUID = new boost::uuids::uuid(boost::uuids::random_generator()());
		
		//we add the variaable and its uuid in the map
		varmap[*newUUID] = NULL; //TODO : change for a variable pointer
		
		
	}	
	
	
	
	
	//return the new uuid, that can be NULL if no new variable has been created
	return newUUID;
	
}