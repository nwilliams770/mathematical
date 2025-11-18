#include "json.hpp"
#include "save_data.hpp"
#include "scene.hpp"
#include "logging.hpp"

SaveData::SaveData(Scene& scene) : scene(scene) {}

json SaveData::toJSON() const
{
  json j;
  j[JsonKeys::SCENE] = scene.toJSON();
  return j;
}

void SaveData::fromJSON(const json& j)
{
  scene.fromJSON(j[JsonKeys::SCENE]);
}