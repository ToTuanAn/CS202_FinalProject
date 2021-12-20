#ifndef _SAVE_LOAD_SYSTEM_
#define _SAVE_LOAD_SYSTEM_

#include "IObject.h"
#include "ISaveable.h"

//#include <dirent.h>
#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

const char* SAVE_PATH = "Save";
const string GOOD_SAVE_PATH = "Save";

class SaveLoadSystem : public IObject
{
private:
	vector<ISaveable*> saveableObjects;
	View* view;
	string currentFile;

public:
	SaveLoadSystem()
	{
		view = nullptr;
		currentFile = "";
	}

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
		out.open(getCurrentFile());
		if (out.is_open())
			for (ISaveable* saveableObject : saveableObjects)
				saveableObject->save(out);

		out.close();
	}

	void load()
	{
		cout << "Loading...\n";

		ifstream in;
		in.open(getCurrentFile());
		if (in.is_open())
			for (ISaveable* saveableObject : saveableObjects)
				saveableObject->load(in);

		in.close();
	}

	vector<string> getAllFiles()
	{
		vector<string> files;

		DIR* direct;
		struct dirent* entry;

		if ((direct = opendir(SAVE_PATH)) != nullptr)
		{
			while ((entry = readdir(direct)) != nullptr)
				files.push_back(entry->d_name);

			closedir(direct);
		}
		else
			cout << "Can't find saving path!\n";

		return files;
	}

	void createNewFile()
	{
		if (currentFile != "")
			save();

		currentFile = "save" + to_string(getAllFiles().size()) + "dat";
	}

	string getCurrentFile()
	{
		return GOOD_SAVE_PATH + "/" + currentFile;
	}

	void setCurrentFile(string newFile)
	{
		if (currentFile != "")
			save();

		currentFile = newFile;
		load();
	}
};
#endif