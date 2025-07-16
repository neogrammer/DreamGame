#ifndef SCENE_H__
#define SCENE_H__

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <scenes/SceneName.h>
using namespace scn;
// Abstract base Scene class
class Scene {
public:
    scn::Name sceneName = scn::Name::INVARIANT;
    scn::Name nextScene = scn::Name::INVARIANT;
public:
    Scene(scn::Name sceneName_ = scn::Name::INVARIANT) : sceneName{ sceneName_ } 
    {
    }

    virtual ~Scene() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void input() = 0;

    virtual void update(sf::RenderWindow& window, float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    inline void readyUp(scn::Name name_) { nextScene = name_; }
    inline bool readyToSwitch() { return bool(nextScene != sceneName); }
    // Optional: return true when scene wants to trigger switch

    virtual void onEnter() {}  // called when scene becomes active
    virtual void onExit() {}   // called when scene deactivates
};

#endif