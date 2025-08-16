#include <actors/Player.h>
#include <misc/Animator.h>
#include <FSM/PlayerAnimFSM.h>
#include <optional>
#include <variant>
#include <stack>

Player::Player()
	: AnimObject{ Cfg::Textures::MegamanSheet130x160, {}, {}, {43.f, 65.f}, {52.f,63.f}, {{0,0},{130,160}} }
	, ShooterObject{ *this, "assets/anims/anchors/player.anc" }
	, fsm{ std::make_unique<FSM_Player>() }
{

	addFrames("assets/anims/megaman.anm");
	


	setPos({ getPos().x, 300.f });

	animator->setRect("Falling", "Right", 0);
	setFrameIndex(0);
	dispatch(*fsm, EventFell{});
}




bool Player::isIdle()   const { if (fsm == nullptr) return false; return std::holds_alternative<IdleState>(fsm->getStateVariant()); }
bool Player::isJumping()   const { if (fsm == nullptr) return false; return std::holds_alternative<JumpingState>(fsm->getStateVariant()); }
bool Player::isMovingAndShooting()   const { if (fsm == nullptr) return false; return  std::holds_alternative<MovingAndShootingState>(fsm->getStateVariant()); }
bool Player::isJumpingAndShooting()   const { if (fsm == nullptr) return false; return  std::holds_alternative<JumpingAndShootingState>(fsm->getStateVariant()); }
bool Player::isMoving()   const { if (fsm == nullptr) return false; return std::holds_alternative<MovingState>(fsm->getStateVariant()); }
bool Player::isFalling()   const { if (fsm == nullptr) return false; return std::holds_alternative<FallingState>(fsm->getStateVariant()); }
bool Player::isFallingAndShooting()   const { if (fsm == nullptr) return false; return  std::holds_alternative<FallingAndShootingState>(fsm->getStateVariant()); }
bool Player::isShooting()   const { if (fsm == nullptr) return false; return std::holds_alternative<ShootingState>(fsm->getStateVariant()); }
bool Player::isRecovering()   const { if (fsm == nullptr) return false; return std::holds_alternative<HitState>(fsm->getStateVariant()); }
bool Player::isDead()   const { if (fsm == nullptr) return false; return std::holds_alternative<DeadState>(fsm->getStateVariant()); }
bool Player::isLanding()   const { if (fsm == nullptr) return false; return std::holds_alternative<LandingState>(fsm->getStateVariant()); }
bool Player::isLandingAndShooting() const { if (fsm == nullptr) return false; return std::holds_alternative<LandingAndShootingState>(fsm->getStateVariant()); }

bool Player::canJump()     const { return (isIdle() || isMoving() || isMovingAndShooting() || isShooting()); }
bool Player::canWalk()     const { return !isRecovering() || !isShooting(); }
bool Player::canShoot()     const { return (!isRecovering() && !shootOnCooldown); }



void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
	{
		jump();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
	{
		setFacingLeft(true);
		walk();	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		setFacingLeft(false);
		walk();
	}
	else
		stopMoving();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
	{
		canSetInitialState = true;
		setInitialState();
		canSetInitialState = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		shoot();
	else
		if (isShooting() || isFallingAndShooting() || isJumpingAndShooting() || isLandingAndShooting() || isMovingAndShooting())
			stopShooting();
}
void Player::render(sf::RenderWindow& tv_)
{
	
	AnimObject::render(tv_);

	if (collisionOccurred)
	{
		sf::RectangleShape collBox;
		collBox.setSize(collisionRect.size);
		collBox.setPosition(collisionRect.position);
		collBox.setFillColor(sf::Color::Red);

		tv_.draw(collBox);
	}

}
void Player::update(sf::RenderWindow& tv_, float dt_)
{

	std::stack<int> tmp;
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isMarked())
		{
			tmp.push(i);
		}
	}

	while (!tmp.empty())
	{
		bullets.erase(bullets.begin() + tmp.top());
		tmp.pop();
	}


	if (shootPressed)
	{
		shootPressedElapsed += dt_;
		if (shootPressedElapsed > shootPressedDelay)
		{
			shootPressedElapsed = 0.f;
			shootPressed = false;
		}
	}

	if (isJumping() || isJumpingAndShooting())
	{
		setVel({ getVel().x, getVel().y + 2400.f * dt_ });
		if (getVel().y > 0.f)
			fall();
	}
	else if (isFalling() || isFallingAndShooting())
	{
		setVel({ getVel().x, getVel().y + 2400.f * dt_ });
	}

	for (auto& b : bullets)
	{
		b.update(tv_, dt_);
	}


	if (shootOnCooldown)
	{
		shootElapsed += dt_;
		if (shootElapsed > shootDelay)
		{
			shootElapsed = 0.f;
			shootOnCooldown = false;
		}
	}

	if (isRecovering())
	{
		recover();
	}

	AnimObject::update(tv_, dt_);
}

void Player::jump()
{
	if (fsm == nullptr) return;


	if (canJump())
	{
		jumpSnd.play();
		dispatch(*fsm, EventJumped{});
		setVel({ getVel().x, -1200.f });
	}
}
void Player::walk()
{
	if (fsm == nullptr) return;


	setVel({ (isFacingLeft() ? -300.f : 300.f),getVel().y});
	dispatch(*fsm, EventStartedMoving{});
	if (getCurrAnimName() == "Landing") {
		dispatch(*fsm, EventTransEnd{}, EventStartedMoving{});
		beginTransitioning();
	}
	else if (getCurrAnimName() == "StartedMoving") {
		beginTransitioning();
	}
}
void Player::stopMoving()
{

	if (fsm == nullptr) return;

	setVel({0.f, getVel().y});
	dispatch(*fsm, EventStoppedMoving{});
}


void Player::shoot1()
{

	if (fsm == nullptr) return;

	if (canShoot())
	{
		dispatch(*fsm, EventStartedShooting{});
		shootOnCooldown = true;
	}
	shootElapsed = 0.f;
}
void Player::stopShooting()
{

	if (fsm == nullptr) return;
	if (!shootOnCooldown && !shootPressed)
	{
		dispatch(*fsm, EventStoppedShooting{});
	}
}
void Player::shoot()
{
	if (fsm == nullptr) return;
	if (canShoot())
	{
		shootOnCooldown = true;
		createBullet();
		/*bullets.push_back(BusterBullet{});
		shootOnCooldown = true;*/
		dispatch(*fsm, EventStartedShooting{});
		shootElapsed = 0.0f;

	}
	shootPressedElapsed = 0.f;
	shootPressed = true;
	//std::cout << "Shoot Fireball" << std::endl;
	
}
void Player::fall()
{
	if (fsm == nullptr) return;

	dispatch(*fsm, EventFell{});
}
void Player::land()
{
	if (fsm == nullptr) return;

	if (getCurrAnimName() == "Falling" || getCurrAnimName() == "FallingAndShooting")
	{
		landSnd.play();
		dispatch(*fsm, EventLanded{});
		beginTransitioning();
		setVel({ getVel().x, 0.f });
	}
}
void Player::hit()
{
	if (fsm == nullptr) return;
	dispatch(*fsm, EventHit{});
}
void Player::recover()
{
	if (fsm == nullptr) return;
	dispatch(*fsm, EventRecovered{});
}

void Player::setInitialState()
{

	if (fsm == nullptr) return;
	if (canSetInitialState)
	{
		fsm->setInitialState(FallingState{});
		std::cout << "Falling" << std::endl;
		setPos({ 30.f, 300.f });
	}
}

void Player::makeTransition()
{
	if (fsm == nullptr) return;
	readyToTransition = false;
	dispatch(*fsm, EventTransEnd{});
}

std::string Player::getFSMState()
{
	if (fsm == nullptr) return "None";
	return toString(getStateEnum(fsm->getStateVariant())).data();
}

FSM_Player& Player::getFSM()
{
	return *fsm;
}

void Player::createBullet()
{
	std::string animName;

	if (currAnim == "Hit" || currAnim == "Dead" || currAnim == "Dying")
		return;

	int frameInd = 0;
	if (bullets.size() < maxBullets)
	{
		if (isFacingLeft())
		{
			if (currAnim == "Idle")
				animName = "Shooting";
			else if (currAnim == "StartedMoving")
				animName = "StartedMovingAndShooting";
			else if (currAnim == "Moving" && frameIndex < 2)
				animName = "StartedMovingAndShooting";
			else if (currAnim == "Moving" && frameIndex >= 2)
				animName = "MovingAndShooting";
			else if (currAnim == "Jumping")
				animName = "JumpingAndShooting";
			else if (currAnim == "Falling")
				animName = "FallingAndShooting";
			else if (currAnim == "Landing")
				animName = "LandingAndShooting";
			else
			{
				animName = currAnim;
				frameInd = (int)frameIndex;
			}

			shotSnd.play();
			bullets.push_back(BusterBullet{ this, Cfg::Textures::BusterBullet28x18, {getPos().x - getOff().x + frameAnchors[animName]["Left"][frameInd].x, getPos().y - getOff().y + frameAnchors[animName]["Left"][frameInd].y}, {-700.f,0.f}, {0.f,0.f}, {28.f,18.f},{{0,0},{28,18}} });
		}
		else
		{
			if (currAnim == "Idle")
				animName = "Shooting";
			else if (currAnim == "StartedMoving")
				animName = "StartedMovingAndShooting";
			else if (currAnim == "Moving" && frameIndex < 2)
				animName = "StartedMovingAndShooting";
			else if (currAnim == "Moving" && frameIndex >= 2)
				animName = "MovingAndShooting";
			else if (currAnim == "Jumping")
				animName = "JumpingAndShooting";
			else if (currAnim == "Falling")
				animName = "FallingAndShooting";
			else if (currAnim == "Landing")
				animName = "LandingAndShooting";
			else
			{
				animName = currAnim;
				frameInd = (int)frameIndex;
			}

			shotSnd.play();

			bullets.push_back(BusterBullet{ this, Cfg::Textures::BusterBullet28x18, {getPos().x - getOff().x + frameAnchors[animName]["Right"][frameInd].x, getPos().y - getOff().y + frameAnchors[animName]["Right"][frameInd].y}, {700.f,0.f}, {0.f,0.f}, {28.f,18.f},{{0,0},{28,18}} });
		}
	}
}
