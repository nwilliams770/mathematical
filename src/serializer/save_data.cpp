#include "json.hpp"
#include "save_data.hpp"
#include "scene.hpp"
#include "logging.hpp"

SaveData::SaveData(Scene& scene) : scene(scene) {
  LOG("SaveData constructor called with at address: " + std::to_string(reinterpret_cast<uintptr_t>(&scene)));
};

json SaveData::toJSON() const
{
  LOG("SaveData toJSON called");
  json j;
  j[JsonKeys::SCENE] = scene.toJSON();
}

void SaveData::fromJSON(const json& j)
{
  LOG("SaveData fromJSON called");
  scene.fromJSON(j[JsonKeys::SCENE]);
}