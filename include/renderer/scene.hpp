#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "json.hpp"
#include "object.hpp"

class Scene {
  public:
    Scene(const Renderer& renderer);
    ~Scene();

    void addObject(Object* obj);
    void removeObject(Object* obj);
    void editObject(Object* oldObj, Object* newObj);

    const std::vector<Object*> getObjects() const;
    void setName(const std::string& name);
    std::string getName() const;

    void clear();
    void render();

    json toJSON() const;
    void fromJSON(const json& j);

  private:
    std::vector<Object*> objects;
    const Renderer& renderer;
    std::string name;
};

#endif