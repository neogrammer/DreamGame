#ifdef _MSC_VER
#pragma warning(disable: 4275)
#endif

#include <SFML/Graphics.hpp>
#include <optional>
#include <resources/Cfg.h>
#include <scenes/SceneMgr.h>
#include <misc/Camera.h>
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
		tv.create(sf::VideoMode{{1600U,900U},32U}, "DreamGame", sf::State::Windowed);
		tv.setVerticalSyncEnabled(true);
		tv.setMaximumSize(sf::Vector2u{ 1600u,900u });
		tv.setMinimumSize(sf::Vector2u{ 1600u,900u });

		sf::Clock timer;

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
			if (dt > 0.016f)
				dt = 0.016f;

			updateFrame(tv, dt);

			tv.clear(sf::Color(47, 147, 247, 255));

			renderScene();

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

	return 69;
}