#pragma once
#include <variant>
#include <FSM/FSMEvent.h>
struct EventStartedShooting : FSMEvent { EventStartedShooting() : FSMEvent() { setName("StartedShooting"); } };
struct EventStartedShooting2 : FSMEvent { EventStartedShooting2() : FSMEvent() { setName("StartedShooting2"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventStartedMoving : FSMEvent { EventStartedMoving() : FSMEvent() { setName("StartedMoving"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventFell : FSMEvent { EventFell() : FSMEvent() { setName("Fell"); } };
struct EventHit : FSMEvent { EventHit() : FSMEvent() { setName("Hit"); } };
struct EventJumped : FSMEvent { EventJumped() : FSMEvent() { setName("Jumped"); } };
struct EventAirKicked : FSMEvent { EventAirKicked() : FSMEvent() { setName("AirKicked"); } };
struct EventLanded : FSMEvent { EventLanded() : FSMEvent() { setName("Landed"); } };
struct EventRecovered : FSMEvent { EventRecovered() : FSMEvent() { setName("Recovered"); } };

using PlayerEventVar = std::variant<EventStartedShooting, EventJumped, EventAirKicked, EventStartedMoving , EventStoppedMoving, EventFell, EventHit, EventLanded, EventStoppedShooting, EventRecovered>;