#ifndef GAMEOBJECT_H__
#define GAMEOBJECT_H__
#include <SFML/Graphics.hpp>
#include <resources/Cfg.h>
#include <iostream>
class GameObject : public sf::Sprite
{
	Cfg::Textures mTexID;

	sf::Vector2f mPos{};
	sf::Vector2f mVel{};

	sf::Vector2f mOff{};
	sf::Vector2f mSize{};
	sf::IntRect mRect{};

	bool mVisible{ true };
	bool mAlive{ true };

	sf::Vector2f mPrevPos{};
	sf::Vector2f mPrevVel{};

	void setPosition(sf::Vector2f position);
protected:
	void copyOver(const GameObject& o);

	

	// internally handled by deriving class
	void setOff(sf::Vector2f off_);
	void setSize(sf::Vector2f size_);
	void setRect(sf::IntRect rect_);
	void setTexID(Cfg::Textures tex_);

	void updatePrevPos();
	void updatePrevVel();
public:

	GameObject(Cfg::Textures texID_ = Cfg::Textures::UNKNOWN, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f off_ = { 0.f,0.f }, sf::Vector2f size_ = { 0.f,0.f }, sf::IntRect rect_ = { {0,0},{0,0} });
	
	GameObject(const GameObject& o);
	GameObject(GameObject& o);

	GameObject& operator=(const GameObject& o);
	GameObject& operator=(GameObject& o);

	GameObject(GameObject&& o) noexcept;
	GameObject& operator=(GameObject&& o) noexcept;

	

public:
	virtual ~GameObject();
	// callable by anyone
	void setAlive(bool cond_);
	void setVisible(bool cond_);
	void setPos(sf::Vector2f pos_);
	void setVel(sf::Vector2f vel_);
	void move(sf::Vector2f amt);
	bool isVisible() const;
	bool isAlive() const;
	sf::Vector2f getPos() const;

	sf::Vector2f getOff() const;
	sf::Vector2f getVel() const;
	Cfg::Textures getTexID() const;
	sf::IntRect getRect() const;
	sf::Vector2f getSize() const;

	sf::Vector2f getPrevPos() const;
	sf::Vector2f getPrevVel() const;

	virtual void render(sf::RenderWindow& tv_);
	virtual void update(sf::RenderWindow& tv_, float dt_);

	

};

#endif