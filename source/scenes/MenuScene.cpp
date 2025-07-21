#include <scenes/MenuScene.h>
#include <scenes/SceneMgr.h>
MenuScene::MenuScene(SceneMgr* sceneMgr_) : Scene(sceneMgr_, scn::Name::INVARIANT)
{
}

void MenuScene::handleEvent(const sf::Event&)
{
}

void MenuScene::update(sf::RenderWindow& window, float dt)
{
}

void MenuScene::input()
{
}

void MenuScene::render(sf::RenderWindow& window)
{
    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Menu Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });

    window.draw(titleText);

}

void MenuScene::onEnter()
{
    nextScene = sceneName;
}
