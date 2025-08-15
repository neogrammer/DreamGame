#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <misc/AnimObject.h>

class Animator
{
public:
	AnimObject* owner;
	~Animator() = default;
	Animator(AnimObject* owner_);
	Animator(const Animator&) = delete;
	Animator& operator=(const Animator&) = delete;
	Animator(Animator&&) = delete;
	Animator& operator=(Animator&&) = delete;

	void setRect(const std::string& anim, const std::string& dir, int idx);
	bool changeAnim(const std::string& name);
	void update(float dt_);

	
	
};

#endif