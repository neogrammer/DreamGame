#include <stages/IntroStage.h>
#include <resources/Cfg.h>
#include <actors/ShootableObject.h>
#include <FSM/SmileyJoeFSM.h>

#include <misc/Animator.h>

IntroStage::IntroStage()
	: Stage{}
    , smiles{ std::make_unique<SmileyJoe>("assets/anims/enemies/SmileyJoy.anm") }
{
    
    
}

IntroStage::~IntroStage() {}

void IntroStage::handleEvent(const sf::Event& event)
{
}

void IntroStage::input()
{
}

void IntroStage::update(float dt)
{
    updateDynamicElements(dt);
   
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


void IntroStage::render(sf::RenderWindow& window)
{
    mWnd = &window;

    tmap.render(window);
    if (smiles)
        smiles->render(window);

    sf::Text titleText2{ Cfg::fonts.get(Cfg::Fonts::SplashFont) };
    titleText2.setString("Intro Stage");
    titleText2.setCharacterSize(32);
    titleText2.setFillColor(sf::Color::White);
    titleText2.setPosition({ 200.f, 200.f });

    window.draw(titleText2);

}

void IntroStage::onEnter()
{
    // load all tiles and tilesets
    tmap.setup("Intro");

    if (smiles != nullptr)
    {
        smiles.reset();
        smiles = std::make_unique<SmileyJoe>();
        smiles->setFacingLeft(true);

    }
    else
    {
        smiles = std::make_unique<SmileyJoe>();
        smiles->setFacingLeft(true);
    }

    smiles->getFSM().dispatch(EventStartedMoving{});
}

void IntroStage::onExit()
{
    // clear out tiles and tilesets to make room for another stage but keeping this structure on file in the scene manager
    tmap.onExit();

    if (smiles)
    {
        smiles.reset();
        smiles = nullptr;
    }
}

void IntroStage::updateDynamicElements(float dt)
{
    // run any scripts on all the active objects in the stage
    if (smiles != nullptr)
    {
        if (smiles->isMarked())
        {
            smiles.reset();
            smiles = nullptr;
        }

    }
    if (smiles)
        smiles->update(*mWnd, dt);
}
