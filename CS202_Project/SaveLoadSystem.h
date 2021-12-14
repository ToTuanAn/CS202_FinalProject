#ifndef _SAVE_LOAD_SYSTEM_
#define _SAVE_LOAD_SYSTEM_

#include "IObject.h"
#include "ISaveable.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

class SaveLoadSystem : public IObject
{
private:
	vector<ISaveable*> saveableObjects;
	View* view;

	string inputFilename()
	{
		return "save.dat";
	}

public:
	void setViewToSaveLoadPosition(View* view)
	{
		this->view = view;
	}

	float update(float deltaTime)
	{
		if (Keyboard::isKeyPressed(Keyboard::L))
			save();
		else if (Keyboard::isKeyPressed(Keyboard::T))
			load();

		return deltaTime;
	}

	void addSaveableObject(ISaveable* saveableObject)
	{
		saveableObjects.push_back(saveableObject);
	}

	void removeSaveableObject(ISaveable* saveableObject)
	{
		vector<ISaveable*>::iterator foundObject = find(saveableObjects.begin(), saveableObjects.end(), saveableObject);
		if (foundObject != saveableObjects.end())
			saveableObjects.erase(foundObject);
	}

	void save()
	{
		cout << "Saving...\n";

		ofstream out;
		out.open(inputFilename());
		if (out.is_open())
			for (ISaveable* saveableObject : saveableObjects)
				saveableObject->save(out);

		out.close();
	}

	void load()
	{
		cout << "Loading...\n";

		ifstream in;
		in.open(inputFilename());
		if (in.is_open())
			for (ISaveable* saveableObject : saveableObjects)
				saveableObject->load(in);

		in.close();
	}
};
#endif