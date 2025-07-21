#include <stages/Stage.h>



Stage::Stage()
{
}

Stage::~Stage() {}

void Stage::updateDynamicElements(float dt)
{
}

Tilemap& Stage::getTilemap()
{
	return tmap;
}
