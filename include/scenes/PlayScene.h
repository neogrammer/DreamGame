#ifndef PLAYSCENE_H__
#define PLAYSCENE_H__

#include <string>
#include <scenes/Scene.h>
#include <resources/Cfg.h>

#include <memory>
#include <utility>

class Stage;
class SceneMgr;
class Player;
class FSM_Player;

class PlayScene : public Scene
{
    std::shared_ptr<Stage> currStage;
    stg::Name stageName;
public:
    std::shared_ptr<Player> player;

    PlayScene(SceneMgr* sceneMgr_);

    void handleEvent(const sf::Event&) override;
    void update(sf::RenderWindow& window, float dt) override;
    void input() override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;

    void switchStage(stg::Name stageName_ = stg::Name::INTRO);
    std::shared_ptr<Stage> getStage(stg::Name stageName_);
};
#endif