#ifndef SCENEMGR_H__
#define SCENEMGR_H__
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <scenes/Scene.h>
#include <stages/Stage.h>

class SceneMgr {
public:

    friend class PlayScene;

    SceneMgr();

    void addScene(const scn::Name& name, const std::shared_ptr<Scene>& scene);
    void setScene(const scn::Name& name);

    void handleEvent(const sf::Event& event);
    void input();
    void update(sf::RenderWindow& window, float dt);
    void render(sf::RenderWindow& window);

    std::shared_ptr<Stage> getStage(stg::Name stageName_);

protected:
    

private:
    std::unordered_map<scn::Name, std::shared_ptr<Scene>> scenes;
    std::unordered_map<stg::Name, std::shared_ptr<Stage>> stages;
    std::weak_ptr<Scene> currentScene;
    scn::Name nextSceneName;
    scn::Name currentSceneName;
};

#endif