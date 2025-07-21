#ifndef INTROSTAGE_H__
#define INTROSTAGE_H__

#include <stages/Stage.h>
#include <resources/Cfg.h>

class IntroStage : public Stage
{

public:
	IntroStage();
	~IntroStage() override final;
	IntroStage(const IntroStage&)  = delete;
	IntroStage& operator=(const IntroStage&)  = delete;
	IntroStage(IntroStage&&)  = delete;
	IntroStage& operator=(IntroStage&&)  = delete;


	void handleEvent(const sf::Event& event) override final;
	void input() override final;

	void update(float dt) override final;
	void render(sf::RenderWindow& window) override final;

	
	// Optional: return true when scene wants to trigger switch

	void onEnter();  // called when scene becomes active
	void onExit();   // called when scene deactivates

	void updateDynamicElements(float dt) override final;

};

#endif