#include <scenes/SceneMgr.h>
#include <scenes/SceneName.h>
#include <scenes/SplashScene.h>
#include <scenes/TitleScene.h>
#include <scenes/PlayScene.h>
#include <scenes/MenuScene.h>
#include <scenes/PausedScene.h>
#include <scenes/OverScene.h>
#include <stages/StageName.h>
#include <stages/IntroStage.h>


#include <iostream>

SceneMgr::SceneMgr()
    : scenes{}
    , stages{}
{
    stages[stg::Name::INTRO] = std::make_shared<IntroStage>();

    scenes.emplace(scn::Name::SPLASH, std::make_shared<SplashScene>(this));
    scenes.emplace(scn::Name::TITLE, std::make_shared<TitleScene>(this));
    scenes.emplace(scn::Name::PLAY, std::make_shared<PlayScene>(this));
    std::dynamic_pointer_cast<PlayScene>(scenes[scn::Name::PLAY])->switchStage(stg::Name::INTRO);
    setScene(scn::Name::SPLASH);
}

std::shared_ptr<Stage> SceneMgr::getStage(stg::Name stageName_)
{
    auto found = stages.find(stageName_);
    if (found != stages.end())
    {
        // found
        return stages[stageName_];

    }
    std::cout << "Picking IntroStage by default!  Not Good!" << std::endl;
    return stages[stg::Name::INTRO];
}

void SceneMgr::addScene(const scn::Name& name, const std::shared_ptr<Scene>& scene) 
{
    scenes[name] = scene;
}

void SceneMgr::setScene(const scn::Name& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        if (auto current = currentScene.lock()) {
            current->onExit();
        }
        currentScene = it->second;
        currentSceneName = name;
        it->second->onEnter();


    }

    nextSceneName = currentSceneName;

}

void SceneMgr::handleEvent(const sf::Event& event) {
    if (auto scene = currentScene.lock()) {
        scene->handleEvent(event);
    }
}

void SceneMgr::input()
{
    if (auto scene = currentScene.lock()) {
        scene->input();
    }
}

void SceneMgr::update(sf::RenderWindow& window, float dt) {
    if (auto scene = currentScene.lock()) {

        if (scene->readyToSwitch() && scene->nextScene != scn::Name::INVARIANT)
        {
            setScene(scene->nextScene);
            return;
        }
        else
        {
            scene->update(window, dt);
        }
    }
}

void SceneMgr::render(sf::RenderWindow& window) {
    if (auto scene = currentScene.lock()) {
        scene->render(window);
    }
}
