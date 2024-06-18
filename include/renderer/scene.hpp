#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "json.hpp"
#include "object.hpp"
#include "render_options.hpp"

class Scene {
  public:
    Scene(const Renderer& renderer);
    ~Scene();

    void addObject(Object* obj);
    void removeObject(Object* obj);
    void editObject(Object* oldObj, Object* newObj);

    const std::vector<Object*> getObjects() const { return objects; }
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }

    void clear();
    void render(const RenderOptions& options);

    json toJSON() const;
    void fromJSON(const json& j);

  private:
    std::vector<Object*> objects;
    const Renderer& renderer;
    std::string name;
};

#endif