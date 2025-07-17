#ifndef ANIMSTATES_H__
#define ANIMSTATES_H__

#include <variant>
#include <string_view>
//#include <FSM/Events.h>

struct IdleState {};
struct StartedMovingState {};
struct MovingState {};
struct StartedMovingAndShootingState {};
struct MovingAndShootingState {};
struct JumpingState {};
struct FallingState {};
struct LandingState {};
struct ShootingState {};
struct JumpingAndShootingState {};
struct FallingAndShootingState {};
struct LandingAndShootingState {};
struct DyingState {};
struct DeadState {};
struct HitState {};



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
	Count,
	None
};

static const std::string_view toString(StateEnum s)
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

template <typename StateVariant>
constexpr StateEnum getStateEnum(StateVariant state_)
{
	if (std::holds_alternative<IdleState>(state_)) return StateEnum::Idle;
	else if (std::holds_alternative<HitState>(state_)) return StateEnum::Hit;
	else if (std::holds_alternative<DyingState>(state_)) return StateEnum::Dying;
	else if (std::holds_alternative<DeadState>(state_)) return StateEnum::Dead;
	else if (std::holds_alternative<StartedMovingState>(state_)) return StateEnum::StartedMoving;
	else if (std::holds_alternative<MovingState>(state_)) return StateEnum::Moving;
	else if (std::holds_alternative<StartedMovingAndShootingState>(state_)) return StateEnum::StartedMovingAndShooting;
	else if (std::holds_alternative<MovingAndShootingState>(state_)) return StateEnum::MovingAndShooting;
	else if (std::holds_alternative<JumpingState>(state_)) return StateEnum::Jumping;
	else if (std::holds_alternative<FallingState>(state_)) return StateEnum::Falling;
	else if (std::holds_alternative<LandingState>(state_)) return StateEnum::Landing;
	else if (std::holds_alternative<ShootingState>(state_)) return StateEnum::Shooting;
	else if (std::holds_alternative<JumpingAndShootingState>(state_)) return StateEnum::JumpingAndShooting;
	else if (std::holds_alternative<FallingAndShootingState>(state_)) return StateEnum::FallingAndShooting;
	else if (std::holds_alternative<LandingAndShootingState>(state_)) return StateEnum::LandingAndShooting;
	else return StateEnum::None;
}


using PlayerAnimVar = std::variant<IdleState, StartedMovingState, DeadState,  MovingState, StartedMovingAndShootingState, ShootingState, MovingAndShootingState, JumpingState, FallingState, LandingState, JumpingAndShootingState, FallingAndShootingState, LandingAndShootingState, DyingState, HitState>;

#endif