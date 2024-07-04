#ifndef RENDEROPTIONS_HPP
#define RENDEROPTIONS_HPP

class RenderOptions {
public:
    bool renderBoundingBoxes;
    bool renderFrustrum;

    RenderOptions() : renderBoundingBoxes(false) {}
};

#endif