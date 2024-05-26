#include "algorithm"
#include "scene.hpp"

Scene::Scene() {};

void Scene::addObject(Object* obj) { objects.push_back(obj); }

void Scene::removeObject(Object* obj)
{
  auto idx = std::find(objects.begin(), objects.end(), obj);

  if (idx != objects.end())
  {
    objects.erase(idx);
  }
}

void Scene::clear() { objects.clear(); }

void Scene::render()
{
  // for (Object* obj : objects)
  // {
  //   obj->render();
  // }
}