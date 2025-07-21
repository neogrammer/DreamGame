#ifndef PHYS_H__
#define PHYS_H__

// Physics module implementation for collision detection and resolution


#include <SFML/Graphics.hpp>

class GameObject;
class Tile;

namespace phys
{

   bool AABB(const GameObject& a, const GameObject& b);
  
   float distSq(const GameObject* a, const GameObject* b);
  
   void detectAndSave_Collidable(GameObject& a, GameObject& b, std::vector<GameObject>& outHits);
  
   void sortCollided_Nearest(std::vector<GameObject>& hits, const GameObject* reference = nullptr);
  
   void detectAndResolve_Stage_Collidables(GameObject& o, std::vector<GameObject>& hits);
  
   void detectAndResolve_Tilemap_Collisions(GameObject& o, std::vector<Tile>& solidTiles);
  
   void CollidePlayer_Collidables(GameObject& player, std::vector<GameObject>& collidables);
  

} // namespace phys

#endif