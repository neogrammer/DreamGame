#include <scenes/SceneMgr.h>
#include <scenes/SplashScene.h>
#include <scenes/TitleScene.h>
#include <scenes/PlayScene.h>
#include <scenes/MenuScene.h>
#include <scenes/PausedScene.h>
#include <scenes/OverScene.h>
#include <scenes/SceneName.h>
#include <iostream>

SceneMgr::SceneMgr()
    : scenes{}
{


    scenes.emplace(scn::Name::SPLASH, std::make_shared<SplashScene>());
    scenes.emplace(scn::Name::TITLE, std::make_shared<TitleScene>());
    scenes.emplace(scn::Name::PLAY, std::make_shared<PlayScene>());
    setScene(scn::Name::SPLASH);
}

void SceneMgr::addScene(const scn::Name& name, const std::shared_ptr<Scene>& scene) {
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
