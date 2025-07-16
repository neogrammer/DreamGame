#include <scenes/PausedScene.h>

void PausedScene::handleEvent(const sf::Event&)
{
}

void PausedScene::update(sf::RenderWindow& window, float dt)
{
}

void PausedScene::input()
{
}

void PausedScene::render(sf::RenderWindow& window)
{
    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Paused Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });

    window.draw(titleText);

}

void PausedScene::onEnter()
{
    sceneName = scn::Name::TITLE;
    nextScene = sceneName;
}
