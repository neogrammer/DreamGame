#ifndef PAUSEDSCENE_H__
#define PAUSEDSCENE_H__

#include <string>
#include <scenes/Scene.h>
#include <resources/Cfg.h>
class SceneMgr;
class PausedScene : public Scene {
public:
    PausedScene(SceneMgr* sceneMgr_);

    void handleEvent(const sf::Event&) override;
    void update(sf::RenderWindow& window, float dt) override;
    void input() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;


};

#endif