#ifndef SMILEYJOEFSM_H__
#define SMILEYJOEFSM_H__
#include <optional>
#include <type_traits>
#include <variant>
#include <iostream>
#include <FSM/Events.h>
#include <FSM/FSM.h>


class FSM_SmileyJoe : public FSM<FSM_SmileyJoe, SmileyJoeAnimVar>
{
public:
	FSM_SmileyJoe() { state_ = IdleState{}; }

	std::optional<SmileyJoeAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return MovingState{}; }
	std::optional<SmileyJoeAnimVar> On_Event(MovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<SmileyJoeAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<SmileyJoeAnimVar> On_Event(DyingState& s, const EventTransEnd& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	template<typename State, typename Event>
	std::optional<SmileyJoeAnimVar> On_Event(State&, const Event&)
	{
		return std::nullopt;     // ignore
	}

};
#endif