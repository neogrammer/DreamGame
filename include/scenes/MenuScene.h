#ifndef MENUSCENE_H__
#define MENUSCENE_H__

#include <string>
#include <scenes/Scene.h>
#include <resources/Cfg.h>
class SceneMgr;
class MenuScene : public Scene {
public:
    MenuScene(SceneMgr* sceneMgr_);
   

    void handleEvent(const sf::Event&) override;
    void update(sf::RenderWindow& window, float dt) override;
    void input() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;


};

#endif