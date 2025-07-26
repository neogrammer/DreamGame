#ifndef STAGE_H__
#define STAGE_H__

#include <SFML/Graphics.hpp>
#include <stages/StageName.h>
#include <tilemap/Tilemap.h>

class Stage
{
protected:

	bool gameOver{ false };
	bool victory{ false };
	bool playerQuitting{ false };

	Tilemap tmap;
	sf::RenderWindow* mWnd;
public:


	Stage();
	virtual ~Stage() = 0;
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	Stage(Stage&&) = delete;
	Stage& operator=(Stage&&) = delete;

	virtual void handleEvent(const sf::Event& event) {}
	virtual void input() {}

	void setWindow(sf::RenderWindow* wnd_);

	virtual void update(float dt) {  }
	virtual void render(sf::RenderWindow& window) {}

	inline void readyUp(bool gameOver_, bool victory_, bool playerQuitting_) { gameOver = gameOver_; victory = victory_; playerQuitting = playerQuitting_; }
	inline bool readyToSwitch() { return (gameOver || victory || playerQuitting); }
	// Optional: return true when scene wants to trigger switch

	virtual void onEnter() {}  // called when scene becomes active
	virtual void onExit() {}   // called when scene deactivates

	inline bool isGameOver() const { return gameOver; }
	inline bool isVictory() const  { return victory; }
	inline bool isPlayerQuitting() const { return playerQuitting; }

	virtual void updateDynamicElements(float dt);

	Tilemap& getTilemap();


};


#endif