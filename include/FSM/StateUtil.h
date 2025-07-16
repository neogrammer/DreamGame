#ifndef STATEUTIL_H_
#define STATEUTIL_H_
#include <string_view>

enum class StateEnum {
	Idle,
	Walk,
	Jump,
	Fall,
	Attack1,
	Attack2,
	AirKick,
	Hit,
	None
};
static constexpr std::string_view toString(StateEnum s)
{
	switch (s)
	{
	case StateEnum::Idle: return "Idle";
	case StateEnum::Walk: return "Walk";
	case StateEnum::Jump: return "Jump";
	case StateEnum::Fall: return "Fall";
	case StateEnum::Attack1: return "Attack1";
	case StateEnum::Attack2: return "Attack2";
	case StateEnum::AirKick: return "AirKick";
	case StateEnum::Hit: return "Hit";
	case StateEnum::None: return "None";
	}
	return "None"; // fallback
}

#endif