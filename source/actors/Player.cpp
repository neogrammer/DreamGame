#include <actors/Player.h>
#include <misc/Animator.h>
#include <FSM/DuckFold.h>

Player::Player()
	: AnimObject{ Cfg::Textures::PlayerSheet132x170, {}, {}, {}, {132.f,170.f}, {{0,0},{132,170}} }
	, fsm{}
{
	addFrames("assets/anims/player.anm");
	animator->setRect("Idle", "Right", 0);
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
		if (isShooting())
			stopShooting();
}
void Player::render(sf::RenderWindow& tv_)
{
	std::string_view animName = toString(fsm.getStateEnum());
	if (animName != getCurrAnimName() && animName != "None")
	{
		setCurrAnimName(animName.data());
		setRect(animName.data(), isFacingLeft() ? "Left" : "Right", 0);
	}
	
	AnimObject::render(tv_);
}
void Player::update(sf::RenderWindow& tv_, float dt_)
{
	if (isJumping())
	{
		setVel({getVel().x, getVel().y + 200.f * dt_ });
		if (getVel().y > 0.f)
			fall();
	}
	else if (isFalling())
	{
		setVel({ getVel().x, getVel().y + 200.f * dt_ });
		if (getPos().y >= 900.f - 170.f - 38.f)
		{
			land();
			setVel({ getVel().x, 0.f});
			setPos({getPos().x , 900.f - 170.f - 38.f });
		}
	}

	if (isWalking())
	{
		if (isFacingLeft())
			setVel({ -300.f, getVel().y });
		else
			setVel({ 300.f, getVel().y });
	}
	else
		stopMoving();

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
		setVel({ getVel().x, -300.f });
	}
}
void Player::walk()
{
	dispatch(fsm, EventStartedMoving{});
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
}
void Player::shoot2()
{
	dispatch(fsm, EventStartedShooting2{});
}
void Player::stopShooting()
{
	dispatch(fsm, EventStoppedShooting{});
}
void Player::airKick()
{
	dispatch(fsm, EventAirKicked{});
}
void Player::fall()
{
	dispatch(fsm, EventFell{});
}
void Player::land()
{
	dispatch(fsm, EventLanded{});
}
void Player::hit()
{
	dispatch(fsm, EventHit{});
}
void Player::recover()
{
	dispatch(fsm, EventRecovered{});
}