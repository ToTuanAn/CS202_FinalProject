#ifndef _I_SAVEABLE_H_
#define _I_SAVEABLE_H_

#include <fstream>
#include <iostream>
using namespace std;

class ISaveable
{
public:
	virtual void save(ostream& out) = 0;
	virtual void load(istream& in) = 0;
};
#endif