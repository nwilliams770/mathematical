#ifndef RENDEROPTIONS_HPP
#define RENDEROPTIONS_HPP

class RenderOptions {
public:
    bool renderBoundingBoxes;
    bool renderFrustum;

    RenderOptions() : renderBoundingBoxes(false) {}
};

#endif