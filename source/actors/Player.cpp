#include <actors/Player.h>
#include <misc/Animator.h>
#include <FSM/DuckFold.h>

Player::Player()
	: AnimObject{ Cfg::Textures::MegamanSheet130x160, {}, {}, {43.f, 65.f}, {52.f,63.f}, {{0,0},{130,160}} }
	, fsm{}
{
	addFrames("assets/anims/megaman.anm");
	animator->setRect("Idle", "Right", 0);
	setFrameIndex(0);
}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		shoot1();
	else
		if (isShooting() || isFallingAndShooting() || isJumpingAndShooting() || isLandingAndShooting() || isMovingAndShooting())
			stopShooting();
}
void Player::render(sf::RenderWindow& tv_)
{

	AnimObject::render(tv_);
}
void Player::update(sf::RenderWindow& tv_, float dt_)
{

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
	if (canJump())
	{
		dispatch(fsm, EventJumped{});
		setVel({ getVel().x, -1200.f });
	}
}
void Player::walk()
{
	setVel({ (isFacingLeft() ? -300.f : 300.f),getVel().y});
	dispatch(fsm, EventStartedMoving{});
	if (getCurrAnimName() == "Landing") {
		dispatch(fsm, EventTransEnd{}, EventStartedMoving{});
		beginTransitioning();
	}
	else if (getCurrAnimName() == "StartedMoving") {
		beginTransitioning();
	}
}
void Player::stopMoving()
{
	setVel({0.f, getVel().y});
	dispatch(fsm, EventStoppedMoving{});
}
void Player::shoot1()
{
	if (canShoot())
	{
		dispatch(fsm, EventStartedShooting{});
		shootOnCooldown = true;
	}
	shootElapsed = 0.f;
}
void Player::stopShooting()
{
	if (!shootOnCooldown)
		dispatch(fsm, EventStoppedShooting{});
}
void Player::fall()
{
	dispatch(fsm, EventFell{});
}
void Player::land()
{
	if (getCurrAnimName() == "Falling" || getCurrAnimName() == "FallingAndShooting")
	{
		dispatch(fsm, EventLanded{});
		beginTransitioning();
		setVel({ getVel().x, 0.f });
	}
}
void Player::hit()
{
	dispatch(fsm, EventHit{});
}
void Player::recover()
{
	dispatch(fsm, EventRecovered{});
}

void Player::makeTransition()
{
	readyToTransition = false;
	dispatch(fsm, EventTransEnd{});
}

std::string Player::getFSMState()
{
	return toString(getStateEnum(fsm.getStateVariant())).data();
}

FSM_Player& Player::getFSM()
{
	return fsm;
}

