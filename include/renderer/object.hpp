#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object {
  public:
    Object();

    virtual ~Object();

    virtual void render() = 0;
};

#endif