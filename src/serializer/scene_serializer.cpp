#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include "logging.hpp"
#include "save_data.hpp"
#include "scene_serializer.hpp"

void SceneSerializer::save(const SaveData& data, const std::string& filename)
{
  LOG("SceneSerializer save called");
  std::string fileToSave = filename.empty() ? generateDefaultFileName() : filename;
  std::ofstream file(fileToSave);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not open file for writing: " + fileToSave);
  }
  json j = data.toJSON();
  // LOG("Serialized JSON: " + j.dump(4));
  file << j.dump(4);
  file.close();
}

void SceneSerializer::load(SaveData& data, const std::string& filename)
{
  LOG("SceneSerializer load called with filename: " + filename);
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file for reading: " + filename);
  }
  json j;
  file >> j;
  // LOG("Deserialized JSON: " + j.dump(4));

  data.fromJSON(j);
  file.close();
}

std::string SceneSerializer::generateDefaultFileName()
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << "_backup.json";
  return ss.str();
}

