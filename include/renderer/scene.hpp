#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "object.hpp"

class Scene {
  public:
    Scene();

    void addObject(Object* obj);

    void removeObject(Object* obj);

    void clear();

    void render();

  private:
    std::vector<Object*> objects;
};

#endif