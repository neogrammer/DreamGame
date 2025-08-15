#ifndef SMILEYJOE_H__
#define SMILEYJOE_H__
#include <misc/AnimObject.h>
#include <actors/ShootableObject.h>
#include <memory>

class FSM_SmileyJoe;

class SmileyJoe : public AnimObject, public ShootableObject
{
	std::unique_ptr<FSM_SmileyJoe> fsm;

	float targetX{ 900.f };
	bool goingLeft{ true };
	bool patrolling{ true };
	int rotateDir{ 0 };

	bool isHit{ false };
	float hitElapsed{ 0.f };
	float hitDelay{ 0.8f };

	int health{ 10 };
	int healthMax{ 10 };

	bool marked{ false };

public:

	using AnimObject::AnimObject;

	SmileyJoe();
	~SmileyJoe() final override = default;
	SmileyJoe(const SmileyJoe&) = default;
	SmileyJoe& operator=(const SmileyJoe&) = default;
	SmileyJoe(SmileyJoe&&) = default;
	SmileyJoe& operator=(SmileyJoe&&) = default;

	void input();
	void render(sf::RenderWindow& tv_) override final;
	void update(sf::RenderWindow& tv_, float dt_) override final;

	void walk();
	void stopMoving();
	void hit();
	void recover();

	void walkToNewTarget(float newTargetX);


	bool isIdle();       
	bool isMoving();     
	bool isRecovering(); 
	bool isDead();       
	bool canWalk();      
	
	void setInitialState();

	void makeTransition() override final;
	std::string getFSMState() override final;

	void takeHit(int dmg_) override final;

	FSM_SmileyJoe& getFSM();
	void mark(bool cond_);
	bool isMarked();
	void destroy();

};

#endif