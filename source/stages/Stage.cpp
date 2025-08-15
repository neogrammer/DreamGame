#include <stages/Stage.h>



Stage::Stage()
{
}

Stage::~Stage() {}

void Stage::setWindow(sf::RenderWindow* wnd_)
{
	mWnd = wnd_;
}

void Stage::updateDynamicElements(float dt)
{



}

Tilemap& Stage::getTilemap()
{
	return tmap;
}
