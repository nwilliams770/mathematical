#ifndef SCENE_SERIALIZER_HPP
#define SCENE_SERIALIZER_HPP

#include "save_data.hpp"
#include "json.hpp"

class SceneSerializer {
  public:
    static void save(const SaveData& data, const std::string& filename = "");
    static void load(SaveData& data, const std::string& filename);

  private:
    static std::string generateDefaultFileName();
};

#endif