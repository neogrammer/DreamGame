#pragma once

#include <variant>
#include <FSM/Events.h>

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

using PlayerAnimVar = std::variant<IdleState, StartedMovingState, DeadState,  MovingState, StartedMovingAndShootingState, ShootingState, MovingAndShootingState, JumpingState, FallingState, LandingState, JumpingAndShootingState, FallingAndShootingState, LandingAndShootingState, DyingState, HitState>;
