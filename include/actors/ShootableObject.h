#ifndef SHOOTABLEOBJECT_H__
#define SHOOTABLEOBJECT_H__
#include <stdint.h>
#include <SFML/Graphics/Color.hpp>

class ShootableObject
{
        
    uint8_t red = 0;
    uint8_t blue = 0;
    uint8_t green = 0;
protected:
    bool hitFlashing = false;
    bool tookHit = false;
    float flashTimer = 0.f;
    float flashDuration = 0.1f; // time for one flash (white or normal)
    int flashCount = 0;
    int maxFlashes = 4;

public:

    bool destroyed = false;

    void onHit()
    {
        if (!hitFlashing)
        {
            tookHit = true;
            hitFlashing = true;
            flashTimer = 0.f;
            flashCount = 0;
        }
    }

    sf::Color getFlashCol() {
    
        return sf::Color(red, green, blue, (uint8_t)255);
    }

    void update(float dt)
    {
        if (tookHit)
        {
            tookHit = false;
        }

        if (hitFlashing)
        {
            flashTimer += dt;
            if (red == 0)
            {
                red = 255;
                green = 255; 
                blue = 255;
            }
            else
            {
                red = 0;
                green = 0;
                blue = 0;
            }
            if (flashTimer >= flashDuration)
            {
                flashTimer = 0.f;
                flashCount++;
                if (flashCount >= maxFlashes)
                    hitFlashing = false;
            }
        }
        else
        {
            red = 255;
            green = 255;
            blue = 255;
        }
    }

    virtual void takeHit(int dmg_) = 0;
};

#endif