#ifndef SCENEMGR_H__
#define SCENEMGR_H__
#include "Scene.h"
#include <memory>
#include <string>
#include <unordered_map>
class SceneMgr {
public:
    SceneMgr();

    void addScene(const scn::Name& name, const std::shared_ptr<Scene>& scene);
    void setScene(const scn::Name& name);

    void handleEvent(const sf::Event& event);
    void input();
    void update(sf::RenderWindow& window, float dt);
    void render(sf::RenderWindow& window);


private:
    std::unordered_map<scn::Name, std::shared_ptr<Scene>> scenes;
    std::weak_ptr<Scene> currentScene;
    scn::Name nextSceneName;
    scn::Name currentSceneName;
};
#endif