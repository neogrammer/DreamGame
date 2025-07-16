#include <misc/Animator.h>
#include <iostream>
Animator::Animator(AnimObject* owner_)
	: owner{owner_}
{
	owner->currAnim = "Idle";
	owner->frameIndex = 0;
}

void Animator::setRect(const std::string& anim, const std::string& dir, int idx)
{
	owner->setRect(anim, dir, idx);
}

bool Animator::changeAnim(const std::string& name)
{
	auto found = owner->anims.find(name);
	if (found == owner->anims.end())
	{
		std::cout << "No anim with that name" << name << std::endl;
		return false;
	}
	owner->currAnim = name;
	owner->frameIndex = 0;

	return true;
}

void Animator::update(float dt_)
{

}