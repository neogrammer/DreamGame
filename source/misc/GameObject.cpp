#include <misc/GameObject.h>

void GameObject::setAlive(bool cond_)
{
	mAlive = cond_;
}

void GameObject::setVisible(bool cond_)
{
	mVisible = cond_;
}

void GameObject::setPos(sf::Vector2f pos_)
{
	mPos = pos_;
}

void GameObject::setPosition(sf::Vector2f position)
{
	sf::Sprite::setPosition(position);
}

void GameObject::setCol(sf::Color col_)
{
	hitColor = col_;
}

void GameObject::copyOver(const GameObject& o)
{
	mTexID = o.mTexID;
	mPos = o.mPos;
	mVel = o.mVel;
	mOff = o.mOff;
	mSize = o.mSize;
	mRect = o.mRect;
	mVisible = o.mVisible;
	mAlive = o.mAlive;
	mPrevPos = o.mPrevPos;
	mPrevVel = o.mPrevVel;
}

void GameObject::move(sf::Vector2f amt)
{
	mPrevPos = getPos();
	setPos(getPos() + amt);
}

void GameObject::setOff(sf::Vector2f off_)
{
	mOff = off_;
}

void GameObject::setSize(sf::Vector2f size_)
{
	mSize = size_;
}

void GameObject::setRect(sf::IntRect rect_)
{
	mRect = rect_;
}

void GameObject::setVel(sf::Vector2f vel_)
{
	mVel = vel_;
}

void GameObject::setTexID(Cfg::Textures texID_)
{
	mTexID = texID_;
}

void GameObject::updatePrevPos()
{
	if (mAlive && (abs(mVel.x) > 0.f || abs(mVel.y) > 0))
	{
		mPrevPos = mPos;
	}
}

void GameObject::updatePrevVel()
{
	if (mAlive && (abs(mVel.x) > 0.f || abs(mVel.y) > 0))
	{
		mPrevVel = mVel;
	}
}

void GameObject::render(sf::RenderWindow& tv_)
{
	if (mVisible && mAlive)
	{
		if (mTexID == Cfg::Textures::UNKNOWN)
		{
			sf::RectangleShape shp{ {0.f,0.f }};

			if (mSize.y == 0.f || mSize.x == 0.f)
				shp.setSize({ 64.f,64.f });
			else
				shp.setSize(mSize);

			shp.setFillColor(sf::Color::Green);
			shp.setPosition(mPos - mOff);

			tv_.draw(shp);
		}
		else
		{
			setPosition(mPos - mOff);
			setTextureRect(mRect);
			setCol(hitColor);
			setTexture(Cfg::textures.get(mTexID));

			tv_.draw(*this);
		}
	}
		
	updatePrevPos();
	updatePrevVel();

}

void GameObject::update(sf::RenderWindow& tv_, float dt_)
{
	mPos += mVel * dt_;
}

GameObject::GameObject(Cfg::Textures texID_, sf::Vector2f pos_, sf::Vector2f vel_, sf::Vector2f off_, sf::Vector2f size_, sf::IntRect rect_)
	: sf::Sprite{ Cfg::textures.get(texID_) }
	, mTexID{ texID_ }, mPos{ pos_ }
	, mVel{ vel_ }, mOff{ off_ }
	, mSize{ size_ }, mRect{ rect_ }
	, mVisible{ true }
	, mAlive{ true }
	, mPrevPos{ pos_ }
	, mPrevVel{ vel_ }
{
}


GameObject::~GameObject()
{
}

GameObject::GameObject(const GameObject& o)
	: sf::Sprite{ Cfg::textures.get(o.mTexID) }
	, mTexID{ o.mTexID }
	, mPos{ o.mPos }
	, mVel{ o.mVel }, mOff{ o.mOff }
	, mSize{ o.mSize }, mRect{ o.mRect }
	, mVisible{ o.mVisible }
	, mAlive{ o.mAlive }
	, mPrevPos{ o.mPrevPos }
	, mPrevVel{ o.mPrevVel }
{
	// copy o's fields into this->fields
}

GameObject::GameObject(GameObject& o)
	: sf::Sprite{ Cfg::textures.get(o.mTexID) }
	, mTexID{ o.mTexID }
	, mPos{ o.mPos }
	, mVel{ o.mVel }, mOff{ o.mOff }
	, mSize{ o.mSize }, mRect{ o.mRect }
	, mVisible{ o.mVisible }
	, mAlive{ o.mAlive }
	, mPrevPos{ o.mPrevPos }
	, mPrevVel{ o.mPrevVel }
{
	// copy o's fields into this->fields
}


GameObject& GameObject::operator=(const GameObject& o)
{
	// copy o's fields into this->fields
	mTexID = o.mTexID;
	mPos = o.mPos;
	mVel = o.mVel;
	mOff = o.mOff;
	mSize = o.mSize;
	mRect = o.mRect;
	mVisible = o.mVisible;
	mAlive = o.mAlive;
	mPrevPos = o.mPrevPos;
	mPrevVel = o.mPrevVel;

	// TODO: insert return statement here
	return *this;
}


GameObject& GameObject::operator=(GameObject& o)
{
	// copy o's fields into this->fields
	mTexID = o.mTexID;
	mPos = o.mPos;
	mVel = o.mVel;
	mOff = o.mOff;
	mSize = o.mSize;
	mRect = o.mRect;
	mVisible = o.mVisible;
	mAlive = o.mAlive;
	mPrevPos = o.mPrevPos;
	mPrevVel = o.mPrevVel;

	// TODO: insert return statement here
	return *this;
}

GameObject::GameObject(GameObject&& o) noexcept
	: sf::Sprite{ Cfg::textures.get(o.mTexID) }
	, mTexID{ std::move(o.mTexID) }
	, mPos{ std::move(o.mPos) }
	, mVel{ std::move(o.mVel) }, mOff{ std::move(o.mOff) }
	, mSize{ std::move(o.mSize) }, mRect{ std::move(o.mRect) }
	, mVisible{ std::move(o.mVisible) }
	, mAlive{ std::move(o.mAlive) }
	, mPrevPos{ std::move(o.mPrevPos) }
	, mPrevVel{ std::move(o.mPrevVel) }
{
	// move o's fields into this->fields

}

GameObject& GameObject::operator=(GameObject&& o) noexcept
{
	// move o's fields into this->fields
	mTexID = std::move(o.mTexID);
	mPos = std::move(o.mPos);
	mVel = std::move(o.mVel);
	mOff = std::move(o.mOff);
	mSize = std::move(o.mSize);
	mRect = std::move(o.mRect);
	mVisible = std::move(o.mVisible);
	mAlive = std::move(o.mAlive);
	mPrevPos = std::move(o.mPrevPos);
	mPrevVel = std::move(o.mPrevVel);


	// TODO: insert return statement here
	return *this;
}

bool GameObject::isVisible() const
{
	return mVisible;
}

bool GameObject::isAlive() const
{
	return mAlive;
}

sf::Vector2f GameObject::getPos() const
{
	return mPos;
}

sf::Vector2f GameObject::getOff() const
{
	return mOff;
}

sf::Vector2f GameObject::getVel() const
{
	return mVel;
}

Cfg::Textures GameObject::getTexID() const
{
	return mTexID;
}

sf::IntRect GameObject::getRect() const
{
	return mRect;
}

sf::Vector2f GameObject::getSize() const
{
	return mSize;
}

sf::Vector2f GameObject::getPrevPos() const
{
	return mPrevPos;
}

sf::Vector2f GameObject::getPrevVel() const
{
	return mPrevVel;
}
