#pragma once

#include <variant>
#include <FSM/Events.h>

struct IdleState {};
struct WalkState {};
struct JumpState {};
struct FallState {};
struct AirKickState {};
struct Attack1State {};
struct Attack2State {};
struct HitState {};

using PlayerAnimVar = std::variant<IdleState, WalkState, JumpState, FallState, AirKickState, Attack1State, Attack2State, HitState>;
