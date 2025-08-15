#ifndef CFG_H__
#define CFG_H__

#include <SFML/Graphics.hpp>
#include "ResourceMgr.h"
#include <vector>
#include <SFML/Audio.hpp>
#include <stages/StageName.h>
#include <map>
#include <memory>
#include <utility>

class Stage;
class IntroStage;
class Cfg
{
public:
	Cfg() = delete;
	Cfg(const Cfg&) = delete;
	Cfg& operator=(const Cfg&) = delete;


	//globals 
	//static sol::state lua; // globals are bad, but we'll use it for simpler implementation
	static void Initialize();
	static void Uninitialize();
	// Resource Enums 
	enum class Textures {
		Tileset1, PlayerSheet64x96, PlayerSheet132x170, MegamanSheet130x160, SmileyJoe126x126, TilesetBasicGreeen10x40_64x64,BusterBullet28x18, UNKNOWN };
	enum class Fonts  { SplashFont, None };
	enum class Music { None };
    enum class Sounds { None };


	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, Textures> textures;
	static ResourceManager<sf::Font, Fonts> fonts;
	static ResourceManager<sf::Music, Music> music;
	static ResourceManager<sf::SoundBuffer, Sounds> sounds;

	static std::map<stg::Name, std::shared_ptr<Stage>> stages;

	//static ActionMap<int> playerInputs;

private:
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
	static void initStages();
	static void destroyTextures();
};


#endif