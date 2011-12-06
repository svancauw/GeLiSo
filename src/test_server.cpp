#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
			
using boost::asio::ip::tcp;
				
int main()
{
	// Création du service principal et du résolveur.
	boost::asio::io_service ios;
				
	// Création de l'acceptor avec le port d'écoute 7171 et une adresse quelconque de type IPv4 // (1)
	tcp::acceptor acceptor(ios, tcp::endpoint(tcp::v4(), 2222));
				
	std::string msg ("Bienvenue sur le serveur !"); // (2)
	
	// Création du buffer de réception // (3)
	boost::array<char, 128> buf;
	
	// Création d'une socket
	tcp::socket socket(ios); // (3)
	
	// On accepte la connexion
	acceptor.accept(socket); // (4)
	std::cout << "Client reçu ! " << std::endl;
	
	// On attend la venue d'un client
	while (1)
	{
			
		// On envoi un message de bienvenue
		//socket.send(boost::asio::buffer(msg)); // (5)
		
		boost::system::error_code error;
		// Réception des données, len = nombre d'octets reçus // (4)
		int len = socket.read_some(boost::asio::buffer(buf), error);
				
		if (error == boost::asio::error::eof) // (5)
		{
			std::cout << "\nTerminé !" << std::endl;
			break;
		}
				
		// On affiche (6)
		std::cout.write(buf.data(), len);
	}
				
	return 0;
}