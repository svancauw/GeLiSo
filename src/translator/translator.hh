//message translati
//call the right function for a given received message

#ifndef __TRANSLATOR_HH__
#define __TRANSLATOR_HH__

#include "../varmap/varmap.hh"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>

namespace GeLiSo{
	

	

//apply a given message
//modify the variable map if a new variable has been created
//return the ack
std::string applyMessage(variableMap& varmap, std::string message);

}



#endif