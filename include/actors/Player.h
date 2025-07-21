#ifndef PLAYER_H__
#define PLAYER_H__
#include <misc/AnimObject.h>
#include <memory>
#include <FSM/PlayerAnimFSM.h>


class Player : public AnimObject
{
	FSM_Player fsm;
	float shootDelay{ 0.2f };
	float shootElapsed{ 0.f };
	float shootOnCooldown{ false };
public:
	Player();
	~Player() final override = default;
	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;

	void input();
	void render(sf::RenderWindow& tv_) override final;
	void update(sf::RenderWindow& tv_, float dt_) override final;

	void jump();
	void walk();
	void stopMoving();
	void shoot1();
	void stopShooting();
	void fall();
	void land();
	void hit();
	void recover();

	inline bool isIdle()   const { return std::holds_alternative<IdleState>(fsm.getStateVariant()); }
	inline bool isJumping()   const { return std::holds_alternative<JumpingState>(fsm.getStateVariant()); }
	inline bool isMovingAndShooting()   const { return  std::holds_alternative<MovingAndShootingState>(fsm.getStateVariant()); }
	inline bool isJumpingAndShooting()   const { return  std::holds_alternative<JumpingAndShootingState>(fsm.getStateVariant()); }
	inline bool isMoving()   const { return std::holds_alternative<MovingState>(fsm.getStateVariant()); }
	inline bool isFalling()   const { return std::holds_alternative<FallingState>(fsm.getStateVariant()); }
	inline bool isFallingAndShooting()   const { return  std::holds_alternative<FallingAndShootingState>(fsm.getStateVariant()); }
	inline bool isShooting()   const { return std::holds_alternative<ShootingState>(fsm.getStateVariant()); 	}
	inline bool isRecovering()   const { return std::holds_alternative<HitState>(fsm.getStateVariant()); }
	inline bool isDead()   const { return std::holds_alternative<DeadState>(fsm.getStateVariant()); }
	inline bool isLanding()   const { return std::holds_alternative<LandingState>(fsm.getStateVariant()); }
	inline bool isLandingAndShooting() const{ return std::holds_alternative<LandingAndShootingState>(fsm.getStateVariant()); }

	inline bool canJump()     const { return (isIdle() || isMoving() || isMovingAndShooting() || isShooting()); }
	inline bool canWalk ()     const { return !isRecovering() || !isShooting(); }
	inline bool canShoot()     const { return (!isRecovering() && !shootOnCooldown); }
	

	void makeTransition() override final;
	std::string getFSMState() override final;

	FSM_Player& getFSM();


};


#endif