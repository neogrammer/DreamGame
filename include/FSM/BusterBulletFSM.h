#ifndef BUSTERBULLETFSM_H__
#define BUSTERBULLETFSM_H__
#include <optional>
#include <type_traits>
#include <variant>
#include <iostream>
#include <FSM/Events.h>
#include <FSM/FSM.h>


class FSM_BusterBullet : public FSM<FSM_BusterBullet, BusterBulletAnimVar>
{
public:
	FSM_BusterBullet() { state_ = IdleState{}; }

	std::optional<BusterBulletAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return IdleState{}; }
	
	template<typename State, typename Event>
	std::optional<BusterBulletAnimVar> On_Event(State&, const Event&)
	{
		return std::nullopt;     // ignore
	}

};
#endif