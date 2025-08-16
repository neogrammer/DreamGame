#include <actors/SmileyJoe.h>
#include <misc/Animator.h>
#include <FSM/SmileyJoeFSM.h>
#include <resources/Cfg.h>

SmileyJoe::SmileyJoe()
	: AnimObject{ Cfg::Textures::SmileyJoe126x126, {}, {}, {}, {126.f,120.f}, {{0,0},{126,120}}}, fsm{std::make_unique<FSM_SmileyJoe>()}
{

	addFrames("assets/anims/enemies/SmileyJoe.anm");

	setPos({ 1300.f, 900.f - 64.f - 120.f - 4.f });

	animator->setRect("Idle", "Left", 0);
	setFrameIndex(0);
	
}




void SmileyJoe::input()
{
	
}
void SmileyJoe::render(sf::RenderWindow& tv_)
{

	
	AnimObject::render(tv_);
	

	
	if (isHit)
	{
		sf::Sprite spr{ Cfg::textures.get(Cfg::Textures::SmileyJoe126x126) };
		
		if (hitElapsed >= 5 * (hitDelay / 5))
		{
			spr.setColor(sf::Color(0, 50, 50, 255));
		}
		else if (hitElapsed >= 4 * (hitDelay / 5))
		{
			spr.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (hitElapsed >= 3 * (hitDelay / 5))
		{
			spr.setColor(sf::Color(0, 50, 50, 255));
		}
		else if (hitElapsed >= 2 * (hitDelay / 5))
		{
			spr.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (hitElapsed >= 1 * hitDelay / 5)
		{
			spr.setColor(sf::Color(0, 50, 50, 255));
		}
		else
		{
			spr.setColor(sf::Color(255, 255, 255, 255));
		}
		spr.setPosition(getPos() - getOff());
		spr.setTextureRect(getRect());

		tv_.draw(spr);
	}
	


}
void SmileyJoe::update(sf::RenderWindow& tv_, float dt_)
{
	if (isHit)
	{
		hitElapsed += dt_;
		if (hitElapsed > hitDelay)
		{
			isHit = false;
			hitElapsed = 0.f;
		}
		
	}


	if (isRecovering())
	{
		recover();
	}
	else
	{
		if (!hitFlashing)
		{
			if (patrolling)
			{

				if (fabsf(targetX - getPos().x) < 0.0001f)
				{
					rotateDir = 1 - rotateDir;

					if (rotateDir == 0)
					{
						walkToNewTarget(getPos().x + 500.f);
					}
					else
					{
						walkToNewTarget(getPos().x - 500.f);
					}
				}

				if (targetX - getPos().x < -0.0001f)
				{
					setFacingLeft(true);
				}
				else
				{
					if (targetX - getPos().x > 0.0001f)
					{
						setFacingLeft(false);
					}
				}

				setVel({ getVel().x + (targetX - getPos().x) * dt_  , getVel().y });
				
			}
			else
			{
				setVel({ 0.f,getVel().y });
			}
		}
	}

	
	ShootableObject::update(dt_);
	AnimObject::update(tv_, dt_);
}

void SmileyJoe::walk()
{
	if (fsm == nullptr) return;


	setVel({ (isFacingLeft() ? -300.f : 300.f),getVel().y });
	dispatch(*fsm, EventStartedMoving{});
}
void SmileyJoe::stopMoving()
{
	if (fsm == nullptr) return;


	setVel({ 0.f, getVel().y });
	dispatch(*fsm, EventStoppedMoving{});
}
void SmileyJoe::hit()
{
	if (fsm == nullptr) return;

	onHit();
	dispatch(*fsm, EventHit{});
}
void SmileyJoe::recover()
{
	if (fsm == nullptr) return;
	setCol(sf::Color::White);
	isHit = false;
	dispatch(*fsm, EventRecovered{});
}

void SmileyJoe::walkToNewTarget(float newTargetX)
{

	if (fsm == nullptr) return;
	dispatch(*fsm, EventStartedMoving{});

	if (newTargetX < getPos().x)
		setFacingLeft(true);
	else if (newTargetX > getPos().x)
		setFacingLeft(false);
	targetX = newTargetX;

}

bool SmileyJoe::isIdle()
{
	if (fsm == nullptr) return false;

	return std::holds_alternative<IdleState>(fsm->getStateVariant()); 

}
 
bool SmileyJoe::isMoving()
{
	if (fsm == nullptr) return false;

     return std::holds_alternative<MovingState>(fsm->getStateVariant());
}

inline bool SmileyJoe::isRecovering()
{
	if (fsm == nullptr) return false;
	return std::holds_alternative<HitState>(fsm->getStateVariant());
}

inline bool SmileyJoe::isDead()
{
	if (fsm == nullptr) return false;

	return std::holds_alternative<DeadState>(fsm->getStateVariant());
}

inline bool SmileyJoe::canWalk()
{
	if (fsm == nullptr) return false;

	return std::holds_alternative<IdleState>(fsm->getStateVariant());
}


void SmileyJoe::makeTransition()
{
	if (fsm == nullptr) return;
	readyToTransition = false;
	dispatch(*fsm, EventTransEnd{});
}

std::string SmileyJoe::getFSMState()
{
	if (fsm == nullptr) 
		return "None";
	else
		return toString(getStateEnum(fsm->getStateVariant())).data();
}

void SmileyJoe::takeHit(int dmg_)
{

	health -= dmg_;
	if (health <= 0)
	{
		destroy();
	}
	setCol(sf::Color::Blue);
	isHit = true;
}

void SmileyJoe::destroy()
{
	marked = true;
}

FSM_SmileyJoe& SmileyJoe::getFSM()
{
	return *fsm;
}

void SmileyJoe::mark(bool cond_)
{
	marked = cond_;
}

bool SmileyJoe::isMarked()
{
	return marked;
}