#include <scenes/PlayScene.h>
#include <misc/Animator.h>

using namespace stg;

PlayScene::PlayScene() : Scene(scn::Name::PLAY), currStage{ Cfg::stages.at(stg::Name::INTRO) }, player{}
{

}


void PlayScene::handleEvent(const sf::Event& evt_)
{
    if (currStage)
    {
        currStage->handleEvent(evt_);
    }
}

void PlayScene::update(sf::RenderWindow& window, float dt)
{
    if (currStage)
    {
        player.update(window, dt);
        currStage->update(dt);

    }
}

void PlayScene::input()
{
    player.input();

    if (currStage)
    {
        currStage->input();
    }
}

void PlayScene::render(sf::RenderWindow& window)
{

    tmap.render(window);

    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Play Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });



    window.draw(titleText);

    if (currStage)
    {
        currStage->render(window);
    }

    player.render(window);

}

void PlayScene::onExit()
{
    if (currStage)
    {
        currStage->onExit();
        currStage.reset();
        currStage = nullptr;
    }
}

void PlayScene::onEnter()
{

    player.setPos({ 30.f, 900.f - 170.f - 38.f });

    sceneName = scn::Name::PLAY;
    nextScene = sceneName;

    if (currStage)
    { 
        currStage.reset();
    }
    currStage = Cfg::stages.at(stg::Name::INTRO);   
    currStage->onEnter();

    tmap.setup("Intro");
}
