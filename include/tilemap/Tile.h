#ifndef TILE_H__
#define TILE_H__
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <resources/Cfg.h>
#include <SFML/System/Vector2.hpp>
#include <misc/GameObject.h>

struct TileDetails
{
    enum class Permanence : uint8_t
    {
        Passthrough = 0,
        Solid
    } permanence{ Permanence::Passthrough };

    enum class Visibility : uint8_t
    {
        Invisible = 0,
        Visible
    } visibility{ Visibility::Visible };

    enum class Reaction : uint8_t
    {
        Mundane = 0,
        Interactive,
        Triggered 
    } reaction{ Reaction::Mundane };

    enum class Environment : uint8_t
    {
        Passive = 0,
        Slow,
        Ice,
        Fire,
        Heal,
        Save,
        Teleport
    } environment{ Environment::Passive };
};

class Tile : public GameObject
{
    friend class Tilemap;
    TileDetails mDeets{};
    void copyOverMe(const GameObject& o);
public:
    Tile(Cfg::Textures texID_ = Cfg::Textures::UNKNOWN, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f off_ = { 0.f,0.f }, sf::Vector2f size_ = { 0.f,0.f }, sf::IntRect rect_ = { {0,0},{0,0} });
    ~Tile() override final;
    Tile(Tile& o);
    Tile& operator=(Tile& o);
    Tile(const Tile& o);
    Tile& operator=(const Tile& o);

    Tile(Tile&& o) noexcept;
    Tile& operator=(Tile&& o) noexcept;

    Cfg::Textures texture;
    sf::Vector2i rectPos{ 0,0 };
    int w{ 64 }, h{ 64 };
    sf::Vector2f pos{ 0.f,0.f };

    void setupDeets(TileDetails::Environment env_, TileDetails::Permanence perm_, TileDetails::Reaction react_, TileDetails::Visibility vis_);

    void setupEnvironmentDeet(TileDetails::Environment env_);
    void setupPermanenceDeet(TileDetails::Permanence perm_);
    void setupReactionDeet(TileDetails::Reaction react_);
    void setupVisibilityDeet(TileDetails::Visibility vis_);


    void render(sf::RenderWindow& wnd_)
    {
        sf::Sprite spr(Cfg::textures.get(texture));

        spr.setPosition(pos);
        spr.setTextureRect({ { (int)rectPos.x, (int)rectPos.y }, { w, h } });

        wnd_.draw(spr);
    }
};

#endif