#ifndef PLAYER_H__
#define PLAYER_H__
#include <misc/AnimObject.h>
#include <memory>

class FSM_Player;

class Player : public AnimObject
{
	std::unique_ptr<FSM_Player> fsm;
	float shootDelay{ 0.2f };
	float shootElapsed{ 0.f };
	float shootOnCooldown{ false };
public:
	bool canSetInitialState{ true };
	bool collisionOccurred{ false };
	sf::FloatRect collisionRect{};

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


};


#endif