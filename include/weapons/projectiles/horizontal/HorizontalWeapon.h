#pragma once
#include "../Projectile.h"

class HorizontalWeapon : public Projectile
{

public:
	using Projectile::Projectile;

	virtual void update(sf::RenderWindow& tv_, float dt_) override = 0;
	virtual void makeTransition() override = 0;
	virtual std::string getFSMState() override = 0;
};