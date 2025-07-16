#ifndef STAGE_H__
#define STAGE_H__

#include <SFML/Graphics.hpp>
#include <stages/StageName.h>

class Stage
{

	bool gameOver{ false };
	bool victory{ false };
	bool playerQuitting{ false };

public:
	Stage();
	virtual ~Stage() = 0;
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	Stage(Stage&&) = delete;
	Stage& operator=(Stage&&) = delete;

	virtual void handleEvent(const sf::Event& event) {}
	virtual void input() {}

	virtual void update(float dt) {}
	virtual void render(sf::RenderWindow& window) {}

	inline void readyUp(bool gameOver_, bool victory_, bool playerQuitting_) { gameOver = gameOver_; victory = victory_; playerQuitting = playerQuitting_; }
	inline bool readyToSwitch() { return (gameOver || victory || playerQuitting); }
	// Optional: return true when scene wants to trigger switch

	virtual void onEnter() {}  // called when scene becomes active
	virtual void onExit() {}   // called when scene deactivates

};


#endif