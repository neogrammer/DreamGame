#include <scenes/OverScene.h>
#include <scenes/SceneMgr.h>
OverScene::OverScene(SceneMgr* sceneMgr_) : Scene(sceneMgr_, scn::Name::INVARIANT) 
{
}

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
    nextScene = sceneName;
}
