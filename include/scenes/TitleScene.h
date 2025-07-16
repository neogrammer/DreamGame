#ifndef TITLESCENE_H__
#define TITLESCENE_H__

#include <string>
#include <scenes/Scene.h>
#include <resources/Cfg.h>

class TitleScene : public Scene {
public:
    TitleScene() : Scene(scn::Name::TITLE) {}

    void handleEvent(const sf::Event&) override;
    void update(sf::RenderWindow& window, float dt) override;
    void input() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;


};

#endif