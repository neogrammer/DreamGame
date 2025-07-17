#ifndef STATEUTIL_H_
#define STATEUTIL_H_
#include <string_view>

enum class StateEnum {
	Idle,
	StartedMoving,
	Moving,
	Jumping,
	Falling,
	Landing,
	Shooting,
	StartedMovingAndShooting,
	MovingAndShooting,
	JumpingAndShooting,
	FallingAndShooting,
	LandingAndShooting,
	Hit,
	Dying,
	Dead,
	None
};
static constexpr std::string_view toString(StateEnum s)
{
	switch (s)
	{
	case StateEnum::Idle: return "Idle";
	case StateEnum::StartedMoving: return "StartedMoving";
	case StateEnum::Moving: return "Moving";
	case StateEnum::Jumping: return "Jumping";
	case StateEnum::Falling: return "Falling";
	case StateEnum::Landing: return "Landing";
	case StateEnum::Shooting: return "Shooting";
	case StateEnum::StartedMovingAndShooting: return "StartedMovingAndShooting";
	case StateEnum::MovingAndShooting: return "MovingAndShooting";
	case StateEnum::JumpingAndShooting: return "JumpingAndShooting";
	case StateEnum::FallingAndShooting: return "FallingAndShooting";
	case StateEnum::LandingAndShooting: return "LandingAndShooting";
	case StateEnum::Hit: return "Hit";
	case StateEnum::Dying: return "Dying";
	case StateEnum::Dead: return "Dead";
	case StateEnum::None: return "None";
	}
	return "None"; // fallback
}

#endif