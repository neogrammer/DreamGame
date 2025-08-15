#ifdef _MSC_VER
#pragma warning(disable: 4275)
#endif

#include <SFML/Graphics.hpp>
#include <optional>
#include <resources/Cfg.h>
#include <scenes/SceneMgr.h>
#include <misc/Camera.h>


float transTimeElapsed;

class DreamGameApp
{
	sf::RenderWindow tv;
	SceneMgr sceneMgr{};


	void processEvent(const sf::Event& evt)
	{
		sceneMgr.handleEvent(evt);
	}
	void handleInput()
	{
		sceneMgr.input();
	}
	void updateFrame(sf::RenderWindow& tv_, float dt_)
	{
		sceneMgr.update(tv_, dt_);
	}
	void renderScene()
	{
		sceneMgr.render(tv);
	}

public: 
	void run()
	{

		tv.create(sf::VideoMode{ {1600U,900U},32U }, "DreamGame", sf::State::Windowed);
		tv.setVerticalSyncEnabled(true);
		tv.setMaximumSize(sf::Vector2u{ 1600u,900u });
		tv.setMinimumSize(sf::Vector2u{ 1600u,900u });

		sf::Clock timer;
		int fpsCount = 0;
		int fps = 0;
		float fpsTimerElapsed = 0.f;
		while (tv.isOpen())
		{


			while (const std::optional event = tv.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					tv.close();
				}
				else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
				{
					if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
						tv.close();
				}
				else if (auto* evt = event->getIf<sf::Event::Resized>())
				{
				
				
					
				}

				processEvent(event.value());
				
			}

			
			handleInput();

			float dt = timer.restart().asSeconds();
			//if (dt > 0.016f)
			//	dt = 0.016f;

			updateFrame(tv, dt);

			tv.clear(sf::Color(47, 147, 247, 255));
			
			renderScene();
			sf::Text txt{ Cfg::fonts.get(Cfg::Fonts::SplashFont)};
			fpsCount++;
			fpsTimerElapsed += dt;
			if (fpsTimerElapsed >= 1.f)
			{
				fps = fpsCount;
				fpsCount = 0;
				fpsTimerElapsed = 0.f;
			}
			std::string str;
			str.append(std::to_string(fps));
			txt.setString(str);
			txt.setCharacterSize(44U);
			txt.setFillColor(sf::Color::White);
			txt.setPosition({ 40.f,40.f });
			tv.draw(txt);

			tv.display();

			// Remainder of main loop
		}

	}
};

int main()
{


	Cfg::Initialize();

	DreamGameApp game;
	
	game.run();

	return 0;
}