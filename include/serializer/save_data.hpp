#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP

#include <string>
#include "json.hpp"
#include "scene.hpp"

class SaveData {
public:
    SaveData(Scene& scene);

    json toJSON() const;
    void fromJSON(const json& j);

    Scene& scene;
};

#endif