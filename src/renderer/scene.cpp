#include "algorithm"
#include "scene.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "logging.hpp"

Scene::Scene(const Renderer& renderer) : renderer(renderer)
{
  LOG("Scene constructor called");
};
Scene::~Scene() {
  LOG("Scene destructor called");
  clear();
}

void Scene::addObject(Object* obj)
{
  objects.push_back(obj);
  LOG_ARGS("Object added to scene, total objects now:", objects.size());

}

void Scene::removeObject(Object* obj)
{
  auto idx = std::find(objects.begin(), objects.end(), obj);

  if (idx != objects.end())
  {
    objects.erase(idx);
  }
}

void Scene::editObject(Object* oldObj, Object* newObj)
{
  if (!oldObj) {
    throw std::invalid_argument("oldObj cannot be nullptr");
  }

  if (!newObj) {
      throw std::invalid_argument("newObj cannot be nullptr");
  }

  auto it = std::find(objects.begin(), objects.end(), oldObj);
  if (it != objects.end()) {
    delete *it;
    *it = newObj;
  } else {
    throw std::runtime_error("oldObj not found in the scene");
  }
}

const std::vector<Object*> Scene::getObjects() const { return objects; }
void Scene::setName(const std::string& name) { this->name = name; }
std::string Scene::getName() const { return name; }

json Scene::toJSON() const {
  json j;
  j[JsonKeys::NAME] = name;

  for (const auto& obj : objects) {
    j[JsonKeys::OBJECTS].push_back(obj->toJSON());
  }

  return j;
};

void Scene::fromJSON(const json& j) {
  LOG("Scene fromJSON called");
  clear();
  name = j[JsonKeys::METADATA][JsonKeys::NAME];

  for (const auto& item : j[JsonKeys::OBJECTS]) {
    size_t vertexCount = item[JsonKeys::VERTICES].size();
    Object* obj = nullptr;

    if (vertexCount == 1) {
      LOG("Point detected when loading from file");
      obj = new Point();
    } else if (vertexCount == 2) {
      LOG("Line detected when loading from file");
      obj = new Line();
    } else if (vertexCount >= 3) {
      LOG("Polygon detected when loading from file");
      obj = new Polygon();
    }

    if (obj) {
      obj->fromJSON(item);
      addObject(obj);
      LOG("Object loaded and added to scene");
    }
  }
};

void Scene::clear()
{
  for (auto obj : objects)
  {
    delete obj;
  }
  objects.clear();
  LOG("Scene cleared");
}

void Scene::render(const RenderOptions& options)
{
  for (Object* obj : objects)
  {
    obj->render(renderer, options);
  }
}