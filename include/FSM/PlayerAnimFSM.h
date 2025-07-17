#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>
#include <FSM/AnimStates.h>
#include <type_traits>
#include <variant>
#include <iostream>
#include <FSM/StateUtil.h>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e) { std::cout << "Jumping" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventTransEnd& e) { std::cout << "StoppedMoving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStoppedMoving& e) { std::cout << "StoppedMoving" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedShooting& e) { std::cout << "StoppedMoving" << std::endl; return StartedMovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventHit& e) { std::cout << "StoppedMoving" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStoppedMoving& e) { std::cout << "StoppedMoving" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventJumped& e) { std::cout << "StartedJump" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventFell& e) { std::cout << "Fell" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedShooting& e) { std::cout << "Hit" << std::endl; return MovingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "StoppedMoving" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "StoppedMoving" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventJumped& e) { std::cout << "StoppedMoving" << std::endl; return JumpingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventFell& e) { std::cout << "StoppedMoving" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "StoppedMoving" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "StoppedMoving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventJumped& e) { std::cout << "StoppedMoving" << std::endl; return JumpingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventFell& e) { std::cout << "StoppedMoving" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventFell& e) { std::cout << "Fell" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventStartedShooting& e) { std::cout << "Dying" << std::endl; return JumpingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventLanded& e) { std::cout << "Landed" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventStartedShooting& e) { std::cout << "Hit" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedShooting& e) { std::cout << "Hit" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventTransEnd& e) { std::cout << "Hit" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedMoving& e) { std::cout << "Hit" << std::endl; return MovingState{}; }

	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventFell& e) { std::cout << "Hit" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Hit" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedMoving& e) { std::cout << "Hit" << std::endl; return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventJumped& e) { std::cout << "Hit" << std::endl; return JumpingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventStoppedShooting & e) { std::cout << "Hit" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventFell& e) { std::cout << "Hit" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }


	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLanded& e) { std::cout << "Hit" << std::endl; return LandingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventDied& e) { std::cout << "Hit" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventTransEnd& e) { std::cout << "Hit" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Hit" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStartedMoving& e) { std::cout << "Hit" << std::endl; return MovingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Hit" << std::endl; return IdleState{}; }

	std::optional<PlayerAnimVar> On_Event(DyingState& s, const EventTransEnd& e) { std::cout << "Hit" << std::endl; return DeadState{}; }


	constexpr StateEnum getStateEnum() const
	{
		if (std::holds_alternative<IdleState>(state_)) return StateEnum::Idle;
		else if (std::holds_alternative<HitState>(state_)) return StateEnum::Hit;
		else if (std::holds_alternative<DyingState>(state_)) return StateEnum::Dying;
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

	constexpr std::string_view getStateName() const
	{
		return toString(getStateEnum());
	}

	template<typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&)
	{
		return std::nullopt;     // ignore
	}
};
#endif