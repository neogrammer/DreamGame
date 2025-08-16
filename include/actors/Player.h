#ifndef PLAYER_H__
#define PLAYER_H__
#include <misc/AnimObject.h>
#include <memory>
#include "../weapons/projectiles/horizontal/BusterBullet.h"
#include <misc/ShooterObject.h>
class FSM_Player;

class Player : public AnimObject, public ShooterObject
{
	std::unique_ptr<FSM_Player> fsm;
	float shootDelay{ 0.15f };
	float shootElapsed{ 0.f };
	float shootOnCooldown{ false };
public:
	sf::Sound landSnd{ Cfg::sounds.get(Cfg::Sounds::MM_Land) };
	sf::Sound jumpSnd{ Cfg::sounds.get(Cfg::Sounds::MM_Jump) };
	sf::Sound shotSnd{ Cfg::sounds.get(Cfg::Sounds::MM_Shot1) };
	bool canSetInitialState{ true };
	bool collisionOccurred{ false };
	sf::FloatRect collisionRect{};
	float shootPressedElapsed{};
	float shootPressedDelay{ 0.25f };
	bool shootPressed{ false };

	int maxBullets{ 3 };

	std::vector<BusterBullet> bullets;

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
	void shoot();
	void fall();
	void land();
	void hit();
	void recover();

	bool isIdle()   const;				
	bool isJumping()   const;			
	bool isMovingAndShooting()   const;  
	bool isJumpingAndShooting()   const; 
	bool isMoving()   const;			    
	bool isFalling()   const;		    
	bool isFallingAndShooting()   const; 
	bool isShooting()   const;		    
	bool isRecovering()   const;         
	bool isDead()   const;               
	bool isLanding()   const;            
	bool isLandingAndShooting() const;   

	bool canJump()     const;
	bool canWalk()     const;
	bool canShoot()     const;
	
	void setInitialState();

	void makeTransition() override final;
	std::string getFSMState() override final;

	FSM_Player& getFSM();

	void createBullet();


};


#endif