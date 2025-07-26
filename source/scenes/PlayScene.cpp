#include <scenes/PlayScene.h>
#include <misc/Animator.h>
#include <scenes/SceneMgr.h>
#include <misc/Phys.h>
#include <stages/IntroStage.h>
#include <actors/player.h>
#include <FSM/PlayerAnimFSM.h>



using namespace stg;

PlayScene::PlayScene(SceneMgr* sceneMgr_) : Scene(sceneMgr_, scn::Name::PLAY), currStage{ nullptr }, player{}
{
    player = std::make_shared<Player>();
    currStage = sceneMgr_->getStage(stg::Name::INTRO);

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
    currStage->setWindow(&window);

    if (currStage)
    {
        if (fabsf(player->getVel().x) > 0.0001f && !player->isJumping() && !player->isJumpingAndShooting() && !player->isFalling() && !player->isFallingAndShooting() && !player->isLanding() && !player->isLandingAndShooting())
        {
            //check below for tile
            auto& allTiles = currStage->getTilemap().getTiles();
        
            std::vector<Tile*> tiles;
            int playerTileXStart = (int)((float)player->getPos().x / (float)allTiles[0].w);
            int playerTileYStart = (int)((float)player->getPos().y / (float)allTiles[0].h);
            int playerTileXEnd = (int)(((float)player->getPos().x + (float)player->getSize().x) / (float)allTiles[0].w);
            int playerTileYEnd = (int)(((float)player->getPos().y + (float)player->getSize().y) / (float)allTiles[0].h);

            float playerCenterX = (float)player->getPos().x + ((float)player->getSize().x / 2.f);
            float playerCenterY = (float)player->getPos().y + ((float)player->getSize().y / 2.f);

            sf::FloatRect testBox{};
            testBox.position.x = (float)playerTileXStart * (float)allTiles[0].w;
            testBox.position.y = (float)playerCenterY + ((float)player->getSize().y / 2.f) + 3.f; // little below the player
            
            testBox.size.x = (playerTileXEnd + 1) * (float)allTiles[0].w - 1.f;

            if (player->collisionOccurred)
                testBox.size.y = player->collisionRect.size.y;
            else
                testBox.size.y = 10.f;

            bool found = false;
            for (int y = playerTileYStart + 1; y <= playerTileYEnd; y++)
            {
                for (int x = playerTileXStart; x <= playerTileXEnd; x++)
                {
                    int i = y * currStage->getTilemap().numCols + x;
                    if (i > allTiles.size()) { break; }
                    else
                    {
                        if (testBox.findIntersection({ allTiles[i].getPos(), allTiles[i].getSize() }))
                        {
                            found = true;
                            break;
                        }
                    }

                }
                if (found == true)
                {
                    break;
                }
            }

            if (!found)
                player->getFSM().dispatch(EventFell{});


        }


        player->update(window, dt);
        currStage->update(dt);

        

    }
    // do all collision detection
}



void PlayScene::input()
{
    player->input();

   

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
    phys::detectAndResolve_Tilemap_Collisions(*player, currStage->getTilemap().getSolidTiles());
    player->render(window);

    //// collision boxes
    //for (auto& t : currStage->getTilemap().getSolidTiles())
    //{
    //    sf::RectangleShape collBox;
    //    collBox.setSize(t.getSize());
    //    collBox.setPosition(t.getPos());
    //    collBox.setFillColor(sf::Color::Transparent);
    //    collBox.setOutlineColor(sf::Color::Yellow);
    //    collBox.setOutlineThickness(1);
    //    
    //    window.draw(collBox);
    //}
    //sf::RectangleShape collBox;
    //collBox.setSize(player->getSize());
    //collBox.setPosition(player->getPos());
    //collBox.setFillColor(sf::Color::Transparent);
    //collBox.setOutlineColor(sf::Color::Yellow);
    //collBox.setOutlineThickness(1);

    //window.draw(collBox);

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
    player->canSetInitialState = true;
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

    player->setInitialState();
    player->canSetInitialState = false;
    player->setPos({ 30.f, 300.f});
    
    

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
