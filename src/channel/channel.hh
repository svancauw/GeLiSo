#ifndef __CHANNEL_HH__
#define __CHANNEL_HH__

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace GeLiSo
{
	// class that manages message exchanges
	class channel
	{
	private:
		//io service, needed in all asio application
		boost::asio::io_service ios;
		
		//socket to send
		
		//socket
		boost::asio::ip::tcp::socket socket_send;
		//buffer
		boost::array<char, 128> buffer_send;
		//connection acceptor
		boost::asio::ip::tcp::acceptor acceptor_send;
		
		//socket to receive
		
		//socket
		boost::asio::ip::tcp::socket socket_receive;
		//buffer
		boost::array<char, 128> buffer_receive;
		//connection acceptor
		boost::asio::ip::tcp::acceptor acceptor_receive;
		
	public:
		//constructor
		channel(std::string ip, unsigned short port_num_send, unsigned short port_num_receive);
		
		//send a message
		void send(std::string message);
		
		//receive a message and return it
		std::string receive();
					
	};
	
	
}

#endif