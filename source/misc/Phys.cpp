#include <misc/Phys.h>
#include <algorithm>
#include <cmath>
#include <tilemap/Tile.h>
#include <actors/Player.h>

namespace phys
{

    bool AABB(const GameObject& a, const GameObject& b)
    {
        const sf::Vector2f apos = a.getPos() - a.getOff();
        const sf::Vector2f asize = a.getSize();
        const sf::Vector2f bpos = b.getPos() - b.getOff();
        const sf::Vector2f bsize = b.getSize();

        return (apos.x < bpos.x + bsize.x &&
            apos.x + asize.x > bpos.x &&
            apos.y < bpos.y + bsize.y &&
            apos.y + asize.y > bpos.y);
    }

    float distSq(const GameObject* a, const GameObject* b)
    {
        sf::Vector2f d = a->getPos() - b->getPos();
        return d.x * d.x + d.y * d.y;
    }

    void detectAndSave_Collidable(GameObject& a, GameObject& b, std::vector<GameObject>& outHits)
    {
        if (!a.isAlive() || !b.isAlive()) return;
        if (AABB(a, b))
            outHits.push_back(b);
    }

    void sortCollided_Nearest(std::vector<GameObject>& hits, const GameObject* reference)
    {
        if (!reference || hits.empty()) return;
        std::sort(hits.begin(), hits.end(), [reference](const GameObject& a,const GameObject& b)
            {
                return distSq(&a, reference) < distSq(&b, reference);
            });
    }

    void detectAndResolve_Stage_Collidables(GameObject& o, std::vector<GameObject>& hits)
    {
        for (auto& h : hits)
        {
            // Simple resolution: push o out of h
            sf::FloatRect or_ = { o.getPos() - o.getOff(), o.getSize() };
            sf::FloatRect hr_ = { h.getPos() - h.getOff(), h.getSize() };

            if (std::optional<sf::FloatRect> fr = or_.findIntersection(hr_); !fr) continue;
            /* std::optional<sf::FloatRect> fr;
             fr = or_.findIntersection(hr_);
             if (fr == std::nullopt)
                 continue;*/

            float dx1 = hr_.position.x + hr_.size.x - or_.position.x;
            float dx2 = or_.position.x + or_.size.x - hr_.position.x;
            float dy1 = hr_.position.y + hr_.size.y - or_.position.y;
            float dy2 = or_.position.y + or_.size.y - hr_.position.y;

            float resolveX = (dx1 < dx2) ? -dx1 : dx2;
            float resolveY = (dy1 < dy2) ? -dy1 : dy2;

            if (std::abs(resolveX) < std::abs(resolveY))
                o.move({ resolveX, 0 });
            else
                o.move({ 0, resolveY });
        }
    }

    void detectAndResolve_Tilemap_Collisions(GameObject& o, std::vector<Tile>& solidTiles)
    {
        std::vector<GameObject> tmp{};
        for (auto& s : solidTiles)
        {
            if (&s == &o) continue;

            detectAndSave_Collidable(o, s, tmp);
        }
        sortCollided_Nearest(tmp, &o);

        for (auto& tile : tmp)
        {
            if (!tile.isAlive()) continue;

            if (AABB(o, tile))
            {
                sf::FloatRect or_ = { o.getPos() - o.getOff(), o.getSize() };
                sf::FloatRect tr_ = { tile.getPos() - tile.getOff(), tile.getSize() };

                float dx1 = tr_.position.x + tr_.size.x - or_.position.x;
                float dx2 = or_.position.x + or_.size.x - tr_.position.x;
                float dy1 = tr_.position.y + tr_.size.y - or_.position.y;
                float dy2 = or_.position.y + or_.size.y - tr_.position.y;

                float resolveX = (dx1 < dx2) ? -dx1 : dx2;
                float resolveY = (dy1 < dy2) ? -dy1 : dy2;

                if (std::abs(resolveX) < std::abs(resolveY))
                    o.move({ resolveX, 0 });
                else
                {

                    if(dynamic_cast<Player*>(&o) != nullptr)
                    {
                        dynamic_cast<Player*>(&o)->land();
                    }
                    o.move({ 0, -(resolveY) });
                }
            }
        }
    }

    void CollidePlayer_Collidables(GameObject& player, std::vector<GameObject>& collidables)
    {
        std::vector<GameObject> hits{};

        // Phase 1: Settle collidables
        for (auto& o : collidables)
        {
            if (&o == &player) continue;

            for (auto& c : collidables)
            {
                if (&c == &o || &c == &player) continue;
                detectAndSave_Collidable(o, c, hits);
            }

            if (!hits.empty())
            {
                sortCollided_Nearest(hits, &o);
                detectAndResolve_Stage_Collidables(o, hits);
                hits.clear();
            }
        }

        // Phase 2: Player vs collidables
        for (auto& obj : collidables)
        {
            if (&obj == &player) continue;
            detectAndSave_Collidable(player, obj, hits);
        }

        if (!hits.empty())
        {
            sortCollided_Nearest(hits, &player);
            detectAndResolve_Stage_Collidables(player, hits);
            hits.clear();
        }
    }


} // namespace phys