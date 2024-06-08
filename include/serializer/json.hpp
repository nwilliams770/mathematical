#ifndef JSON_HPP
#define JSON_HPP

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace JsonKeys {
    const std::string COLOR = "color";
    const std::string COLOR_RED = "r";
    const std::string COLOR_GREEN = "g";
    const std::string COLOR_BLUE = "b";
    const std::string COLOR_ALPHA = "a";

    const std::string VERTICES = "vertices";
    const std::string X = "x";
    const std::string Y = "y";

    const std::string SCENE = "scene";
    const std::string METADATA = "metadata";
    const std::string NAME = "name";
    const std::string OBJECTS = "objects";
}

#endif