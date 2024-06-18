#include "camera.hpp"
#include "view_frustrum.hpp"


ViewFrustrum::ViewFrustrum(float fieldOfViewY, float aspectRatio, float nearClip, float farClip)
  : fieldOfViewY(fieldOfViewY), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip)
{}

void ViewFrustrum::update(const Camera& camera)
{

}