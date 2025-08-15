#include <misc/ShooterObject.h>
#include <misc/AnimObject.h>
#include <fstream>

void ShooterObject::loadFile(const std::string& anchorFile_)
{
	std::ifstream iFile;
	iFile.open(anchorFile_);

	int numAnchors;
	iFile >> numAnchors;

	int xInt, yInt;
	float x{}, y{};
	std::string animName;


	while (iFile >> animName)
	{
		int numFrames;
		std::string dir;
		iFile >> dir;
		iFile >> numFrames; // 0 - Left, 1 - Right, 2 - Uni

		auto found = frameAnchors.find(animName);
		if (found == frameAnchors.end())
			frameAnchors.emplace(animName, std::map<std::string, std::vector<sf::Vector2f>>());// (std::pair<int, std::vector<sf::Vector2f>>{ dir, std::vector<sf::Vector2f>{} }));
		
		frameAnchors[animName][dir] = std::vector<sf::Vector2f>{};
		frameAnchors[animName][dir].clear();
		frameAnchors[animName][dir].reserve(numFrames);
		for (int i = 0; i < numFrames; i++)
		{
			iFile >> xInt;
			iFile >> yInt;
			x = (float)xInt;
			y = (float)yInt;
			frameAnchors[animName][dir].emplace_back(x,y);
		}
	}

	iFile.close();
}

ShooterObject::ShooterObject(AnimObject& augmented_, const std::string& anchorFile_)
	: augmented{augmented_}

{
	loadFile(anchorFile_);

}


