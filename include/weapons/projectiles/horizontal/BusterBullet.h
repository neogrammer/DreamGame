#pragma once
#include "HorizontalWeapon.h"
#include <FSM/BusterBulletFSM.h>

class BusterBullet : public HorizontalWeapon
{

public:

	std::unique_ptr<FSM_BusterBullet> fsm;

	BusterBullet(AnimObject* owner_, Cfg::Textures texID_ = Cfg::Textures::BusterBullet28x18, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f off_ = { 0.f,0.f }, sf::Vector2f size_ = { 0.f,0.f }, sf::IntRect rect_ = { {0,0},{0,0} });
    ~BusterBullet() final override = default;
	BusterBullet(const BusterBullet&) = default;
	BusterBullet& operator=(const BusterBullet&) = default;
	BusterBullet(BusterBullet&&) = default;
	BusterBullet& operator=(BusterBullet&&) = default;
	void makeTransition() override final;
	std::string getFSMState() override final;
	void update(sf::RenderWindow& tv_, float dt_) override final;
	void render(sf::RenderWindow& wnd_);

};