#include <scenes/SplashScene.h>
#include <scenes/SceneMgr.h>
SplashScene::SplashScene(SceneMgr* sceneMgr_)
: Scene{ sceneMgr_, scn::Name::SPLASH }
{

}

void SplashScene::handleEvent(const sf::Event& evt_)
{

    if (auto e = evt_.getIf<sf::Event::KeyReleased>())
    {
        if (e->code == sf::Keyboard::Key::Enter)
        {
            readyUp(scn::Name::TITLE);
        }
    }
}


void SplashScene::update(sf::RenderWindow& window, float dt)
{


}

void SplashScene::input()
{

}

void SplashScene::render(sf::RenderWindow& window)
{
        sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
        titleText.setString("Splash Scene");
        titleText.setCharacterSize(48);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition({ 100.f, 100.f });

        window.draw(titleText);

}

void SplashScene::onEnter()
{
    sceneName = scn::Name::SPLASH;
}
