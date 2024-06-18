#ifndef SCENE_SERIALIZER_HPP
#define SCENE_SERIALIZER_HPP

class SaveData;

class SceneSerializer {
  public:
    static void save(const SaveData& data, const std::string& filename = "");
    static void load(SaveData& data, const std::string& filename);

  private:
    static std::string generateDefaultFileName();
};

#endif