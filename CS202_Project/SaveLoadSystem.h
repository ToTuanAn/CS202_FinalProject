#ifndef _SAVE_LOAD_SYSTEM_
#define _SAVE_LOAD_SYSTEM_

#include "IObject.h"
#include "ISaveable.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

const string SAVE_PATH = "Save/";
const string SAVE_FILE_LIST = SAVE_PATH + "SaveList.txt";

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

		ifstream in;
		in.open(SAVE_FILE_LIST);
		if (in.is_open())
		{
			string file;
			getline(in, file);
			files.push_back(file);
		}
		in.close();

		return files;
	}

	void createNewFile()
	{
		if (currentFile != "")
			save();

		currentFile = "save" + to_string(getAllFiles().size()) + "dat";

		vector<string> oldFiles = getAllFiles();

		ofstream out;
		out.open(SAVE_FILE_LIST);
		if (out.is_open())
		{
			out << currentFile << endl;

			for (string file : oldFiles)
				out << file << endl;
		}
		out.close();
	}

	string getCurrentFile()
	{
		return SAVE_PATH + currentFile;
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