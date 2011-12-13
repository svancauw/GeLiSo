#include "channel.hh"

namespace GeLiSo
{
	using namespace std;
	//using boost::asio::ip;
	using boost::asio::ip::tcp;
	
	//constructor
	channel::channel(std::string ip, unsigned short port_num_send , unsigned short port_num_receive)
	: socket_send(ios), acceptor_send(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port_num_send)),
	socket_receive(ios), acceptor_receive(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port_num_receive))
	{
		cout << "The channel has been created on the C++ side and is waiting for sending and receiving client" << endl;
		acceptor_send.accept(socket_send);
		cout << "Receiving client accepted" << endl;
		acceptor_receive.accept(socket_receive);
		cout << "Sending client accepted" << endl;
		
	}
	
	//send a message
	void channel::send(string message)
	{
		cout << "# C++ sender # " << "The following message will be sent : " << endl << message << endl;
		socket_send.send(boost::asio::buffer(message));
		cout << "# C++ sender # " << "Message sent !" << endl;
	}
	
	
	
	
	//receive a message and return it
	string channel::receive()
	{
		//empty string
		string returnedMessage;
		
		cout << "# C++ receiver # " << "Wait for a message" << endl;
		while (1)
		{
			//error code for buffer reading
			boost::system::error_code error;
		
			//read the message
			int len = socket_receive.read_some(boost::asio::buffer(buffer_receive), error);
			
			cout << "# C++ receiver # " << "Length by readsome : " << endl << len << endl;
			
			cout << "# C++ receiver # " << "the eror is : " << error.message() << len << endl;
			
			if (error == boost::asio::error::eof)
			{
				break;
			}
			
			//add the message to the returned string
			returnedMessage.append(buffer_receive.data(),len);
			
		}
		
		cout << "# C++ receiver # " << "The following message has been received : " << endl << returnedMessage << endl;
		
		//return the complete message
		return returnedMessage;
	}
	
	
}