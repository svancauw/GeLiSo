#include "channel.hh"

namespace GeLiSo
{
	using namespace std;
	//using boost::asio::ip;
	using boost::asio::ip::tcp;
	using namespace boost;
	
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
		message.push_back(';');
		socket_send.send(boost::asio::buffer(message));
	}
	
	
	
	
	//receive a message and return it
	string channel::receive()
	{

		string returnedMessage;//message that we will return
		string rawMessage;
		
		socket_receive.receive(boost::asio::buffer(buffer_receive));
				
		//now that we have received the message in the buffer, we only keep the useful information
		rawMessage.append(buffer_receive.data());
		char* tok = strtok(const_cast<char *>(rawMessage.c_str()),";");//first token, which is the only that interest us
		
		returnedMessage.append(tok);//get the real message
		
		//return the complete message
		return returnedMessage;
	}
	
	
}