#include <weapons/projectiles/Projectile.h>
#include <misc/Animator.h>


Projectile::Projectile(AnimObject * owner_)
	:AnimObject{ Cfg::Textures::UNKNOWN, {0.f,0.f}, {0.f,0.0f}, {0.f,0.f}, {0.f,0.f}, {{0,0},{0,0}} }
	, owner{owner_}
{
}

Projectile::Projectile(AnimObject* owner_, Cfg::Textures texID_, sf::Vector2f pos_, sf::Vector2f vel_, sf::Vector2f off_, sf::Vector2f size_, sf::IntRect rect_)
	: AnimObject{ texID_, pos_, vel_, off_, size_,  rect_ }
	, owner{owner_}
{
}

void Projectile::destroy()
{
	marked = true;
}

bool Projectile::isMarked()
{
	return marked;
}

int Projectile::getPower()
{
	return power;
}

void Projectile::setPower(int power_)
{
	power = power_;
}
