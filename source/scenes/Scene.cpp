#include <scenes/Scene.h>
#include <scenes/SceneMgr.h>

Scene::Scene(SceneMgr* sceneMgr_, scn::Name sceneName_) : sceneName{ sceneName_ }, manager{ sceneMgr_ }
{
}
