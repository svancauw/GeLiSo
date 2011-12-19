#include "channel/channel.hh"
#include "translator/translator.hh"

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
		
		//acknowledgment (a UUID if we create a new variable)
		string ack = applyMessage(varmap, newMessage);
				
		//we send the ack
		ch.send(ack);
		
		//(3) if we received the message "beginSearch" message , begin the search
		if(!strcmp(ack.c_str(), "Search done"))
			break;
	}
	
	
	return 0;
	
}