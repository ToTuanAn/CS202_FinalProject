#ifndef _OBJECT_
#define _OBJECT_

class IObject
{
public:
	virtual void start()
	{}

	virtual void update(float deltaTime) = 0;
};
#endif