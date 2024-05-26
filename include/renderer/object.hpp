#ifndef OBJECT_HPP
#define OBJECT_HPP

class Renderer; // Forward declaration of Renderer
// only referencing so just needs to know about its existence

class Object {
  public:
    Object();
    virtual ~Object();

    virtual void render(const Renderer& renderer) = 0;
};

// Inline definitions
// Inline Definitions: The inline keyword ensures that the constructor and
// destructor definitions are included wherever the header file is included,
// preventing multiple definition errors. Linker Resolution: By providing these
// definitions, the linker can resolve calls to Object's constructor and
// destructor, even though the class itself is abstract.
inline Object::Object() {}
inline Object::~Object() {}

#endif