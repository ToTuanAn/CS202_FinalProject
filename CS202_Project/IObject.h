#ifndef _OBJECT_
#define _OBJECT_

class IObject
{
public:
	virtual float update(float deltaTime) = 0;
};
#endif