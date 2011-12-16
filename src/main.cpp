#include "channel/channel.hh"
#include "translator/translator.hh"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

int main()
{
	using namespace GeLiSo;
	using namespace std;
	using namespace boost::uuids;
	
	//(1) create a channel and a variable map
	channel ch("127.0.0.1", 2222, 3333);
	variableMap varmap;
	
	//(2) loop : receive messages, behave accordingly and answer
	while(1)
	{
		cout << "Waiting for a message ... " << endl;
		//the new message received
		string newMessage = ch.receive();
		cout << "Message received ! " << endl;
		
		//apply the new received message and get the new UUID
		uuid* newUUID = applyMessage(varmap, newMessage);
		
		//the UUID as a string to be sent
		string strUUID = boost::lexical_cast<std::string>(newUUID);
		
		ch.send(strUUID);
		
		//(3) if receive "search" message , go out of the loop
		break;
	}
	

	//(4) Begin search and send the results
	
	
	return 0;
	
}