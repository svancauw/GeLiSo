#include "channel/channel.hh"

int main()
{
	using namespace GeLiSo;
	using namespace std;
	
	//(1) create a channel
	channel ch("127.0.0.1",2222, 3333);
	
	//(2) loop : receive messages, behave accordingly and answer
	while(1)
	{
		ch.send("Test");
		
		cout << "We received that message : " << ch.receive() << endl;
		break;
	}
	//(3) if receive "search" message , go out of the loop

	//(4) Begin search and send the results
	
	
	return 0;
	
}