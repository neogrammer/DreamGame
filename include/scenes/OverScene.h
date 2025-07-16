#ifndef OVERSCENE_H__
#define OVERSCENE_H__

#include <string>
#include <scenes/Scene.h>
#include <resources/Cfg.h>

class OverScene : public Scene {
public:
    OverScene() : Scene(scn::Name::INVARIANT) {}

    void handleEvent(const sf::Event&) override;
    void update(sf::RenderWindow& window, float dt) override;
    void input() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;

  
};

#endif