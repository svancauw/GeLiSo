#ifndef __VARMAP_HH__
#define __VARMAP_HH__

#include <map>
#include <boost/uuid/uuid.hpp>

namespace GeLiSo
{

//map having uuids as keys, and variables of any type as values
typedef std::map<boost::uuids::uuid, void*> variableMap ;

}

#endif