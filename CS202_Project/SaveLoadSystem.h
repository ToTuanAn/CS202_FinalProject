#ifndef _SAVE_LOAD_SYSTEM_
#define _SAVE_LOAD_SYSTEM_

#include "ISaveable.h"
#include <vector>

class SaveLoadSystem
{
private:
	vector<ISaveable*> saveableObjects;
	static SaveLoadSystem* instance;

	SaveLoadSystem()
	{}

public:
	SaveLoadSystem(const SaveLoadSystem& saveLoadSystem) = delete;

	static SaveLoadSystem* getInstance()
	{
		if (!instance)
			instance = new SaveLoadSystem();
		return instance;
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

	// void save()
	// {
	// 	for (ISaveable* saveableObject : saveableObjects)
	// 		saveableObject->save();
	// }

	// void load()
	// {
	// 	for (ISaveable* saveableObject : saveableObjects)
	// 		saveableObject->load();
	// }
};
#endif