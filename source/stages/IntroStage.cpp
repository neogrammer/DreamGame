#include <stages/IntroStage.h>
#include <resources/Cfg.h>

IntroStage::IntroStage()
	: Stage{}
{

}

IntroStage::~IntroStage() {}

void IntroStage::handleEvent(const sf::Event& event)
{
}

void IntroStage::input()
{
}

void IntroStage::update(float dt)
{
}

void IntroStage::render(sf::RenderWindow& window)
{

    sf::Text titleText2{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText2.setString("Intro Stage");
    titleText2.setCharacterSize(32);
    titleText2.setFillColor(sf::Color::White);
    titleText2.setPosition({ 200.f, 200.f });

    window.draw(titleText2);

}

void IntroStage::onEnter()
{
    // load all sprites
}

void IntroStage::onExit()
{
    // delete sprite textures
}
