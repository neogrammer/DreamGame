#include <scenes/PlayScene.h>
#include <misc/Animator.h>
#include <scenes/SceneMgr.h>
#include <misc/Phys.h>
#include <stages/IntroStage.h>
#include <actors/player.h>
#include <FSM/PlayerAnimFSM.h>
#include <actors/SmileyJoe.h>


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

    for (auto& b : player->bullets)
    {

        sf::FloatRect bbox={{b.getPos()},{b.getSize()}};
        auto& smiley = dynamic_cast<IntroStage*>(currStage.get())->smiles;
        
        if (smiley)
        {
            bool found = false;

            if (bbox.findIntersection({ smiley->getPos(), smiley->getSize() }))
            {
                found = true;
            }
            if (found)
            {
               
                b.destroy();
                smiley->takeHit(b.getPower());
                
                if (smiley->health > 0)
                {
                    if (smiley->currSnd == 0)
                    {
                        smiley->hitSnd0.play();
                        smiley->currSnd = 1;
                    }
                    else if (smiley->currSnd == 1)
                    {
                        smiley->hitSnd1.play();
                        smiley->currSnd = 2;
                    }
                    else if (smiley->currSnd == 2)
                    {
                        smiley->hitSnd2.play();
                        smiley->currSnd = 0;
                    }
                }
                else if (smiley->health <= 0)
                {
                    smiley->deadSnd.play();
                }
            }
        }
    }
    for (int i = 0; i < player->bullets.size(); ++i)
    {
        if (player->bullets[i].getPos().x >= window.getView().getCenter().x - (window.getSize().x / 2.f) - player->bullets[i].getSize().x && player->bullets[i].getPos().x < window.getView().getCenter().x + (window.getSize().x / 2.f) &&
            player->bullets[i].getPos().y >= window.getView().getCenter().y - (window.getSize().y / 2.f) - player->bullets[i].getSize().y && player->bullets[i].getPos().y < window.getView().getCenter().y + (window.getSize().y / 2.f))
        {
            // do nothing
        }
        else
        {
            player->bullets[i].destroy();
        }
    }
}



void PlayScene::input()
{
    player->input();

   

    if (currStage)
    {
        currStage->input();
    }
}



void PlayScene::render(sf::RenderWindow& window)
{  

   
    if (currStage)
    {
        currStage->render(window);
    }
    phys::detectAndResolve_Tilemap_Collisions(*player, currStage->getTilemap().getSolidTiles());
    player->render(window);



    for (auto& b : player->bullets)
    {
        b.render(window);
    }

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
