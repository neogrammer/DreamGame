#include <scenes/PlayScene.h>
#include <misc/Animator.h>
#include <scenes/SceneMgr.h>
#include <misc/Phys.h>
using namespace stg;

PlayScene::PlayScene(SceneMgr* sceneMgr_) : Scene(sceneMgr_, scn::Name::PLAY), currStage{ nullptr }, player{}
{

}


void PlayScene::handleEvent(const sf::Event& evt_)
{
    if (currStage)
    {
        currStage->handleEvent(evt_);
    }
}

void PlayScene::update(sf::RenderWindow& window, float dt)
{
    if (currStage)
    {
        player.update(window, dt);
        currStage->update(dt);

    }
    // do all collision detection
}



void PlayScene::input()
{
    player.input();

    if (currStage)
    {
        currStage->input();
    }
}


// IMPLEMENTATION BELOW

   // Phase 0: World Movement (optional)
   // currStage->update(dt) calls Stage::IntroStage::updateDynamicElements(dt);

    // functions to make for the next function to operate from the phys class
    //  void phys::detectAndSave_Collidable(o, c, &hits)
    //  void phys::detectAndResolve_Stage_Collidables(o, &hits)
    //  void phys::detectAndSave_Collidable(player, obj, &playerHits)
    //  void phys::detectAndResolve_Stage_Collidables(player, &playerHits)
    //  void phys::detectAndResolve_Tilemap_Collisions(player, tilemap.getSolidTiles()

   //// Phase 1: Stage settles  < --  happens after update & before animation finalizes, then finally rendering
   // void phys::CollidePlayer_Collidables(Player& player, std::vector<GameObject>& collidables) <-- pass in currStage->getCollidables() reference, and a Player Reference, which allows for multiple players
   // {
   //    std::vector<GameObject*> hits{};
   //  for (auto& o : collidables)
   //  {
   //    if (&o == &player) continue;
   //    for (auto& c : collidables)
   //    {
   //        if (&c == &o || &c == &player) continue;
   //        detectAndSave_Collidable(o, c, &hits);
   //    }
   //    if (!hits.empty())
   //    {
   //        sortCollided_Nearest(&hits);
   //        detectAndResolve_Stage_Collidables(o, &hits);
   //        hits.clear();
   //    }
   //  }
   // 
   //// Phase 2: Player vs settled stage <-- same high level function as Phase 1
   //{
   //    std::vector<GameObject*> playerHits;
   //    for (auto& obj : collidables)
   //    {
   //        if (&obj == &player) continue;
   //        detectAndSave_Collidable(player, obj, &playerHits);
   //    }
   //    if (!playerHits.empty())
   //    {
   //        sortCollided_Nearest(&playerHits);
   //        detectAndResolve_Stage_Collidables(player, &playerHits);
   //    }
   //  }
   //// Phase 3: Player vs tilemap (final clamp)
   //detectAndResolve_Tilemap_Collisions(player, tilemap.getSolidTiles());  <-- still in same function
 // }


void PlayScene::render(sf::RenderWindow& window)
{

    //phys::CollidePlayer_Collidables(player, currStage->getTilemap().getSolidTiles());
    

   
    if (currStage)
    {
        currStage->render(window);
    }
    phys::detectAndResolve_Tilemap_Collisions(player, currStage->getTilemap().getSolidTiles());
    player.render(window);



    sf::Text titleText{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText.setString("Play Scene");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 100.f, 100.f });
    window.draw(titleText);

}

void PlayScene::onExit()
{
    if (currStage)
    {
        currStage->onExit();
        currStage.reset();
        currStage = nullptr;
    }
}




void PlayScene::switchStage(stg::Name stageName_)
{
    stageName = stageName_;
}

std::shared_ptr<Stage> PlayScene::getStage(stg::Name stageName_)
{
    return manager->getStage(stageName_);
}

  

void PlayScene::onEnter()
{

    player.setPos({ 30.f, 900.f - 170.f - 38.f });
    nextScene = sceneName;

    if (currStage != nullptr)
    {
        currStage->onExit();
        currStage.reset();
        currStage = nullptr;
    }

    currStage = getStage(stageName);
    currStage->onEnter();
}
