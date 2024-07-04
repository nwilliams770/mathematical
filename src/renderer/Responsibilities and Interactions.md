Responsibilities and Interactions
Camera Class:

Generates the view matrix based on the camera's position and orientation.
Generates the projection matrix based on the frustum parameters (field of view, aspect ratio, near clip, far clip).
View Frustum Class:

Uses the camera's matrices to update the frustum planes.
Determines if objects are inside the frustum for culling purposes.
Renderer Class:

Manages the rendering process.
Calls the Camera to get the view and projection matrices.
Calls the View Frustum to check if objects are within the frustum.
Projects coordinates to screen space and draws using SDL.
System Design Adjustments
Camera Class
The Camera class remains responsible for generating the matrices: