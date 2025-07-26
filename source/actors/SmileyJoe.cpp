#include <actors/SmileyJoe.h>
#include <misc/Animator.h>
#include <FSM/SmileyJoeFSM.h>


SmileyJoe::SmileyJoe()
	: AnimObject{ Cfg::Textures::SmileyJoe126x126, {}, {}, {}, {}, {{0,0},{126,120}} }, fsm{ std::make_unique<FSM_SmileyJoe>() }
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
	if (hitFlashing)
	{
		sf::Sprite spr{ Cfg::textures.get(Cfg::Textures::SmileyJoe126x126) };
		spr.setColor(sf::Color(getFlashCol().r, getFlashCol().g, getFlashCol().b, 255));
		spr.setPosition(getPos() - getOff());
		spr.setTextureRect(getRect());

		tv_.draw(spr);
	}
}
void SmileyJoe::update(sf::RenderWindow& tv_, float dt_)
{
	
	if (isRecovering())
	{
		recover();
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

	dispatch(*fsm, EventRecovered{});
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

void SmileyJoe::takeHit()
{
}

FSM_SmileyJoe& SmileyJoe::getFSM()
{
	return *fsm;
}

