#ifndef PLAYER_H__
#define PLAYER_H__
#include <misc/AnimObject.h>
#include <memory>
#include <FSM/PlayerAnimFSM.h>

class Player : public AnimObject
{
	FSM_Player fsm;
	float shootDelay{ 0.3f };
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
	void shoot2();
	void stopShooting();
	void airKick();
	void fall();
	void land();
	void hit();
	void recover();

	inline bool isIdle()   const { return std::holds_alternative<IdleState>(fsm.getStateVariant()); }
	inline bool isJumping()   const { return std::holds_alternative<JumpState>(fsm.getStateVariant()); }
	inline bool isWalking()   const { return std::holds_alternative<WalkState>(fsm.getStateVariant()); }
	inline bool isFalling()   const { return std::holds_alternative<FallState>(fsm.getStateVariant()); }
	inline bool isShooting()   const { return std::holds_alternative<Attack1State>(fsm.getStateVariant()); }
	inline bool isAirKicking()   const { return std::holds_alternative<AirKickState>(fsm.getStateVariant()); }
	inline bool isRecovering()   const { return std::holds_alternative<HitState>(fsm.getStateVariant()); }
	inline bool isShooting2()   const { return std::holds_alternative<Attack2State>(fsm.getStateVariant()); }

	inline bool canJump()     const { return isIdle() || isWalking(); }
	inline bool canWalk ()     const { return !isRecovering() || !isShooting(); }
	inline bool canShoot()     const { return (!isJumping() && !isWalking() && !isFalling() && !isRecovering() && !isAirKicking() && !shootOnCooldown); }
};


#endif