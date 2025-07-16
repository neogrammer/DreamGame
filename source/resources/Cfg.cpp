#include <resources/Cfg.h>
#include <stages/IntroStage.h>

ResourceManager<sf::Texture, Cfg::Textures> Cfg::textures = {};
ResourceManager<sf::Font, Cfg::Fonts> Cfg::fonts = {};
ResourceManager<sf::Music, Cfg::Music> Cfg::music = {};
ResourceManager<sf::SoundBuffer, Cfg::Sounds> Cfg::sounds = {};

std::map<stg::Name, std::shared_ptr<Stage>> Cfg::stages = {};

//ActionMap<int> Cfg::playerInputs = {};

void Cfg::Initialize()
{
    initTextures();
    initFonts();
	initMusic();
    initSounds();
	initStages();
}

void Cfg::Uninitialize()
{
	Cfg::textures.unloadAll();
}

void Cfg::initMusic()
{
}

void Cfg::initSounds()
{
}

void Cfg::initTextures()
{
	textures.load(Textures::UNKNOWN, "assets/textures/unknown.png");
	textures.load(Textures::Tileset1, "assets/textures/tilesets/Tiles.png");
	textures.load(Textures::PlayerSheet64x96, "assets/textures/player/Vegeta.png");
	textures.load(Textures::PlayerSheet132x170, "assets/textures/player/vegeta_sheet.png");


}

void Cfg::initStages()
{
	stages.emplace(std::make_pair(stg::Name::INTRO, std::make_shared<IntroStage>()));
}

void Cfg::destroyTextures()
{
	
}


void Cfg::initFonts()
{
	fonts.load(Cfg::Fonts::SplashFont, "assets/fonts/Crusty.ttf");
}