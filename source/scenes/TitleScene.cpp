#include <scenes/TitleScene.h>

void TitleScene::handleEvent(const sf::Event& evt_)
{
    if (auto e = evt_.getIf<sf::Event::KeyReleased>())
    {
        if (e->code == sf::Keyboard::Key::Enter)
        {
            readyUp(scn::Name::PLAY);
        }
    }
}

void TitleScene::update(sf::RenderWindow& window, float dt)
{
}

void TitleScene::input()
{
}

void TitleScene::render(sf::RenderWindow& window)
{
    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Title Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });

    window.draw(titleText);

}

void TitleScene::onEnter()
{
    sceneName = scn::Name::TITLE;
    nextScene = sceneName;
}
