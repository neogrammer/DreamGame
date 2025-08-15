#include "BusterBullet.h"
#include <misc/Animator.h>

BusterBullet::BusterBullet(AnimObject* owner_, Cfg::Textures texID_, sf::Vector2f pos_, sf::Vector2f vel_, sf::Vector2f off_, sf::Vector2f size_, sf::IntRect rect_)
	: HorizontalWeapon{ owner_, texID_, pos_, vel_, off_, size_, rect_ }
	, fsm { std::make_unique<FSM_BusterBullet>() }
{
	addFrames("assets/anims/bullets/BusterBullet.anm");
	currAnim = "Idle";

	animator->setRect("Idle", (isFacingLeft()) ? "Left" : "Right", 0);
	setFrameIndex(0);
	dispatch(*fsm, EventStartedMoving{});
}

void BusterBullet::makeTransition()
{
	if (fsm == nullptr) return;
	readyToTransition = false;
	//dispatch(*fsm, EventTransEnd{});
}

std::string BusterBullet::getFSMState()
{
	return fsm->getStateName().data();
}

void BusterBullet::update(sf::RenderWindow& tv_, float dt_)
{
	if (currAnim == "")
		currAnim = "Idle";


	AnimObject::update(tv_, dt_);
}

void BusterBullet::render(sf::RenderWindow& wnd_)
{
	AnimObject::render(wnd_);
}