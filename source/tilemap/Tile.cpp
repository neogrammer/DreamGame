#include <tilemap/Tile.h>

void Tile::copyOverMe(const GameObject& o)
{
	copyOver(o);
}

Tile::Tile(Cfg::Textures texID_, sf::Vector2f pos_, sf::Vector2f vel_, sf::Vector2f off_, sf::Vector2f size_, sf::IntRect rect_)
	: GameObject{ texID_, pos_, vel_, off_, size_, rect_ }
{
	texture = texID_;
	rectPos = rect_.position;
	w = rect_.size.x;
	h = rect_.size.y;
	pos = pos_;
	
}

Tile::~Tile()
{
}

Tile::Tile(const Tile& o)
	: GameObject(o)
	, texture{ o.texture }
	, rectPos{ o.rectPos }
	, w{ o.w }
	, h{ o.h }
	, pos{ o.pos }
	, mDeets{ o.mDeets }
{
}

Tile& Tile::operator=(const Tile& o)
{
	copyOverMe(*this);
	texture = o.texture;
	rectPos = o.rectPos;
	w = o.w;
	h = o.h;
	pos = o.pos;
	mDeets = o.mDeets;

	return *this;
	// TODO: insert return statement here
}

Tile::Tile(Tile& o)
	: GameObject(*dynamic_cast<GameObject*>(&o))
	, texture{ o.texture }
	, rectPos{ o.rectPos }
	, w{ o.w }
	, h{ o.h }
	, pos{ o.pos }
	, mDeets{o.mDeets}
{
}

Tile& Tile::operator=(Tile& o)
{
	copyOverMe(*this);
	texture = o.texture;
	rectPos = o.rectPos;
	w = o.w;
	h = o.h;
	pos = o.pos;
	mDeets = o.mDeets;

	return *this;
	// TODO: insert return statement here
}

Tile::Tile(Tile&& o) noexcept
	: GameObject(std::move((GameObject&&)o))
	, texture{ std::move(o.texture) }
	, rectPos{ std::move(o.rectPos) }
	, w{ std::move(o.w) }
	, h{ std::move(o.h) }
	, pos{ std::move(o.pos) }
	, mDeets{ o.mDeets }
{

}

Tile& Tile::operator=(Tile&& o) noexcept
{
	copyOverMe((GameObject&&)(o));
	texture = std::move(o.texture);
	rectPos = std::move(o.rectPos);
	w = std::move(o.w);
	h = std::move(o.h);
	pos = std::move(o.pos);
	mDeets = std::move(o.mDeets);
	// TODO: insert return statement here
	return *this;
}



void Tile::setupDeets(TileDetails::Environment env_, TileDetails::Permanence perm_, TileDetails::Reaction react_, TileDetails::Visibility vis_)
{
	mDeets.environment = env_;
	mDeets.permanence = perm_;
	mDeets.reaction = react_;
	mDeets.visibility = vis_;
}

void Tile::setupEnvironmentDeet(TileDetails::Environment env_)
{
	mDeets.environment = env_;
}

void Tile::setupPermanenceDeet(TileDetails::Permanence perm_)
{
	mDeets.permanence = perm_;
}

void Tile::setupReactionDeet(TileDetails::Reaction react_)
{
	mDeets.reaction = react_; 
}

void Tile::setupVisibilityDeet(TileDetails::Visibility vis_)
{
	mDeets.visibility = vis_;
}
