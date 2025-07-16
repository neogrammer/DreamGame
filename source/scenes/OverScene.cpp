#include <scenes/OverScene.h>

void OverScene::handleEvent(const sf::Event&)
{
}

void OverScene::update(sf::RenderWindow& window, float dt)
{
}

void OverScene::input()
{
}

void OverScene::render(sf::RenderWindow& window)
{
    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Over Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });

    window.draw(titleText);

}

void OverScene::onEnter()
{
    sceneName = scn::Name::TITLE;
    nextScene = sceneName;
}
