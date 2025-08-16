#include <resources/Cfg.h>
#include <stages/IntroStage.h>
#include <stages/Stage.h>

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
	music.load(Music::Intro, "assets/sfx/intro.wav");
}

void Cfg::initSounds()
{
	sounds.load(Sounds::MM_BigDmg, "assets/sfx/bigdmg.wav");
	sounds.load(Sounds::MM_SmDmg, "assets/sfx/smalldmg.wav");
	sounds.load(Sounds::MM_Hurt, "assets/sfx/hurt.wav");
	sounds.load(Sounds::MM_Shot1, "assets/sfx/shot1.wav");
	sounds.load(Sounds::MM_Die, "assets/sfx/die.wav");
	sounds.load(Sounds::MM_Jump, "assets/sfx/jump.wav");
	sounds.load(Sounds::MM_Land, "assets/sfx/land.wav");


}

void Cfg::initTextures()
{
	textures.load(Textures::UNKNOWN, "assets/textures/unknown.png");
	textures.load(Textures::Tileset1, "assets/textures/tilesets/Tileset64x64.png");
	textures.load(Textures::TilesetBasicGreeen10x40_64x64, "assets/textures/tilesets/BasicGreen.png");

	textures.load(Textures::PlayerSheet64x96, "assets/textures/player/Vegeta.png");
	textures.load(Textures::PlayerSheet132x170, "assets/textures/player/vegeta_sheet.png");
	textures.load(Textures::MegamanSheet130x160, "assets/textures/player/PlayerAtlas.png");
	textures.load(Textures::SmileyJoe126x126, "assets/textures/enemies/SmileyJoe1.png");
	textures.load(Textures::BusterBullet28x18, "assets/textures/projectiles/busterBullet.png");
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
	fonts.load(Cfg::Fonts::SplashFont, "assets/fonts/font1.ttf");
}