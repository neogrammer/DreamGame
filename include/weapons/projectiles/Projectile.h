#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include <misc/AnimObject.h>
class Animator;
class Projectile : public AnimObject
{
	AnimObject* owner{ nullptr };
	bool marked{ false };
public:
	Projectile() = delete;
	Projectile(AnimObject* owner_);
	Projectile(AnimObject* owner_, Cfg::Textures texID_, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f off_ = { 0.f,0.f }, sf::Vector2f size_ = { 0.f,0.f }, sf::IntRect rect_ = { {0,0},{0,0} });
	virtual ~Projectile() override = default;
	Projectile(const Projectile&) = default;
	Projectile& operator=(const Projectile&) = default;
	Projectile(Projectile&&) = default;
	Projectile& operator=(Projectile&&) = default;

	virtual void update(sf::RenderWindow& tv_, float dt_) override = 0;
	virtual void makeTransition() override = 0;
	virtual std::string getFSMState() override = 0;

	void destroy();
	bool isMarked();
};

#endif