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
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return WalkState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "StartedShooting1" << std::endl; return Attack1State{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting2& e) { std::cout << "StartedShooting2" << std::endl; return Attack2State{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e) { std::cout << "Jumped" << std::endl; return JumpState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Fell" << std::endl; return FallState{}; }

	std::optional<PlayerAnimVar> On_Event(WalkState& s, const EventStoppedMoving& e) { std::cout << "StoppedMoving" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(WalkState& s, const EventJumped& e) { std::cout << "StartedJump" << std::endl; return JumpState{}; }
	std::optional<PlayerAnimVar> On_Event(WalkState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(WalkState& s, const EventFell& e) { std::cout << "Fell" << std::endl; return FallState{}; }

	std::optional<PlayerAnimVar> On_Event(JumpState& s, const EventFell& e) { std::cout << "Fell" << std::endl; return FallState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpState& s, const EventAirKicked& e) { std::cout << "AirKicked" << std::endl; return AirKickState{}; }

	std::optional<PlayerAnimVar> On_Event(AirKickState& s, const EventLanded& e) { std::cout << "Landed" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(AirKickState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	
	std::optional<PlayerAnimVar> On_Event(FallState& s, const EventLanded& e) { std::cout << "Landed" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(FallState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Recovered" << std::endl; return IdleState{}; }

	std::optional<PlayerAnimVar> On_Event(Attack1State& s, const EventStoppedShooting& e) { std::cout << "StoppedShooting1" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(Attack1State& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(Attack2State& s, const EventStoppedShooting& e) { std::cout << "StoppedShooting1" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(Attack2State& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	constexpr StateEnum getStateEnum() const
	{
		if (std::holds_alternative<IdleState>(state_)) return StateEnum::Idle;
		else if (std::holds_alternative<HitState>(state_)) return StateEnum::Hit;
		else if (std::holds_alternative<WalkState>(state_)) return StateEnum::Walk;
		else if (std::holds_alternative<Attack1State>(state_)) return StateEnum::Attack1;
		else if (std::holds_alternative<Attack2State>(state_)) return StateEnum::Attack2;
		else if (std::holds_alternative<AirKickState>(state_)) return StateEnum::AirKick;
		else if (std::holds_alternative<JumpState>(state_)) return StateEnum::Jump;
		else if (std::holds_alternative<FallState>(state_)) return StateEnum::Fall;
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