#ifndef TILESET_H__
#define TILESET_H__

#include "Tile.h"
#include <fstream>
#include <vector>
#include <iostream>
class Tileset
{
public:

    Cfg::Textures texture{};
    std::vector<Tile> tiles{};
    int numRows{}, numCols{};

    void setup(int w_, int h_, Cfg::Textures tex_, int numRows_, int numCols_)
    {
        numRows = numRows_;
        numCols = numCols_;
        texture = tex_;
        tiles.clear();
        tiles.shrink_to_fit();
        tiles.reserve(numRows_ * numCols_);

        for (int y = 0; y < numRows; y++)
        {
            for (int x = 0; x < numCols; x++)
            {
                auto& t = tiles.emplace_back((Cfg::Textures)texture, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ (float)w_, (float)h_ }, sf::IntRect{ sf::Vector2i{ x * (int)w_, y * (int)h_ }, sf::Vector2i{(int)w_, (int)h_ } });
                t.w = w_;
                t.h = h_;
                t.rectPos = { x * w_, y * h_ };
                t.texture = texture;
                t.pos = { 0.f,0.f };
            }
        }
        setupDeets(tex_);

    }


private:
    void setupDeets(Cfg::Textures texID_)
    {
       
        if (tiles.empty())
        {
            std::cout << "Trying to add deets to an empty tileset!" << std::endl;
            return;
        }

        std::string filename = "";

        switch (texID_)
        {
        case Cfg::Textures::Tileset1:
            filename = "Intro.tst";
            break;
        default:
            filename = "Intro.tst";
            break;
        }

        std::ifstream iFile;
        iFile.open("assets/tilesets/" + filename);

        if (!iFile.is_open() || !iFile.good())
        {
            std::cout << "Unable to open tileset file containing the deets for each tile" << std::endl;
            for (auto& t : tiles)
            {
                t.setupDeets(TileDetails::Environment::Passive, TileDetails::Permanence::Passthrough, TileDetails::Reaction::Mundane, TileDetails::Visibility::Invisible);
            }
            return;
        }
        else
        {
            std::string type;
            std::string tsetname;
            iFile >> type >> tsetname;
            if (type != "TILESET")
            {
                std::cout << "Reading tileset deets from wrong kind of file!" << std::endl;
                iFile.close();
                for (auto& t : tiles)
                {
                    t.setupDeets(TileDetails::Environment::Passive, TileDetails::Permanence::Passthrough, TileDetails::Reaction::Mundane, TileDetails::Visibility::Invisible);
                }
                return;
            }
            if (tsetname != filename)
            {
                std::cout << "Reading tileset deets from wrong set of tilset data!" << std::endl;
                iFile.close();
                for (auto& t : tiles)
                {
                    t.setupDeets(TileDetails::Environment::Passive, TileDetails::Permanence::Passthrough, TileDetails::Reaction::Mundane, TileDetails::Visibility::Invisible);                   
                }
                return;
            }
            // made it here then good to go
            std::string deetType;

            while (iFile >> deetType)
            {
                if (deetType == "PERMANENCE")
                {
                    for (auto& t : tiles)
                    {
                        int deet;
                        iFile >> deet;
                        t.setupPermanenceDeet((TileDetails::Permanence)deet);
                    }
                }
                else if (deetType == "VISIBILITY")
                {
                    for (auto& t : tiles)
                    {
                        int deet;
                        iFile >> deet;
                        t.setupVisibilityDeet((TileDetails::Visibility)deet);
                    }
                }
                else if (deetType == "REACTION")
                {
                    for (auto& t : tiles)
                    {
                        int deet;
                        iFile >> deet;
                        t.setupReactionDeet((TileDetails::Reaction)deet);
                    }
                }
                else if (deetType == "ENVIRONMENT")
                {
                    for (auto& t : tiles)
                    {
                        int deet;
                        iFile >> deet;
                        t.setupEnvironmentDeet((TileDetails::Environment)deet);
                    }
                }
                else
                {
                    std::cout << "Unknown Deet Type, setting all to default" << std::endl;
                    iFile.close();
                    for (auto& t : tiles)
                    {
                        t.setupDeets(TileDetails::Environment::Passive, TileDetails::Permanence::Passthrough, TileDetails::Reaction::Mundane, TileDetails::Visibility::Invisible);
                    }
                    return;
                }
            }
            iFile.close();

            int i = 0;




            
        }
    }

public:

    Tile copyTile(int index_)
    {
        return tiles[index_];
    }

    void onExit()
    {
        tiles.clear();
        tiles.shrink_to_fit();
    }
};

#endif