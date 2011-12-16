//message translati
//call the right function for a given received message

#ifndef __TRANSLATOR_HH__
#define __TRANSLATOR_HH__

#include "../varmap/varmap.hh"
#include <boost/uuid/uuid_generators.hpp>


//apply a given message
//modify the variable map if a new variable has been created
//return the uuid of the new variable if one has been created, NULL otherwise
boost::uuids::uuid* applyMessage(variableMap& varmap, std::string message);






#endif