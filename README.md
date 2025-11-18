# mathematical

# Notes

TODOS:

- Load from JSON to include size
- Render frustum and debug it to get better near clip plane
- Debug frustrum and maybe add opacity indicator on it to debug that

DO THESE FIRST:

1. Line with a Stroke Weight
When dealing with a line that has a stroke weight, you are correct that the toPolygon method should return 4 vertices, representing the four corners of the rectangle that represents the line's thickness. Here’s how it would work:

cpp
Copy code
std::vector<Vec3> Line::toPolygon() const {
    float halfWeight = strokeWeight / 2.0f;
    Vec3 direction = (end - start).normalized();
    Vec3 perpendicular = Vec3(-direction.y, direction.x, direction.z).normalized() * halfWeight;

    return {
        start - perpendicular,
        start + perpendicular,
        end + perpendicular,
        end - perpendicular
    };
}
2. projectTo2DAndSize
You're right. With the new approach, projectTo2DAndSize is not necessary for the drawing process. Instead, each vertex of the polygon is projected independently, and the size is implied by the relative positions of the projected vertices.

3. Using SDL_RenderDrawLine vs. Bresenham's Algorithm
I used SDL_RenderDrawLine for simplicity, but since this is a learning project and you want to minimize library use, you should indeed use your own Bresenham's algorithm. The important part is that you handle the vertices correctly and draw lines between them.

4. Filling Polygons
To fill polygons instead of just drawing the outline, you would typically use a polygon filling algorithm. One common algorithm is the scanline fill algorithm. SDL does not have built-in support for polygon filling, so you would need to implement this yourself.

Here’s a high-level approach to filling a polygon:

Sort the Vertices: Sort the vertices of the polygon by their y-coordinates.
Edge Table and Active Edge Table: Construct an edge table and use an active edge table during scan conversion to track intersections.
Fill the Spans: For each scanline, fill the spans between intersections.
Implementation
Let’s walk through how you can implement the changes:

Clip and Draw Polygon
cpp
Copy code
void Renderer::drawPolygon(const std::vector<Vec3>& vertices) const {
    // Project vertices to 2D screen coordinates
    std::vector<std::pair<int, int>> projectedVertices;
    for (const auto& vertex : vertices) {
        auto [x, y] = projectTo2D(vertex);
        projectedVertices.emplace_back(x, y);
    }

    // Fill the polygon
    fillPolygon(projectedVertices);
}
Fill Polygon Method
cpp
Copy code
void Renderer::fillPolygon(const std::vector<std::pair<int, int>>& vertices) const {
    // Edge table and active edge table logic
    // Implement the scanline fill algorithm

    // Sort the vertices by y-coordinate
    std::vector<std::pair<int, int>> sortedVertices = vertices;
    std::sort(sortedVertices.begin(), sortedVertices.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Edge table
    struct Edge {
        int yMax;
        float xMin, inverseSlope;
    };
    std::vector<std::vector<Edge>> edgeTable;

    // Initialize the edge table
    for (size_t i = 0; i < sortedVertices.size(); ++i) {
        auto [x1, y1] = sortedVertices[i];
        auto [x2, y2] = sortedVertices[(i + 1) % sortedVertices.size()];

        if (y1 != y2) {
            float inverseSlope = static_cast<float>(x2 - x1) / static_cast<float>(y2 - y1);
            edgeTable[y1].push_back(Edge{y2, static_cast<float>(x1), inverseSlope});
        }
    }

    // Active edge table
    std::vector<Edge> activeEdgeTable;
    int currentY = sortedVertices.front().second;

    // Scanline fill
    while (!activeEdgeTable.empty() || currentY <= sortedVertices.back().second) {
        // Add edges to active edge table
        for (const auto& edge : edgeTable[currentY]) {
            activeEdgeTable.push_back(edge);
        }

        // Remove edges from active edge table
        activeEdgeTable.erase(std::remove_if(activeEdgeTable.begin(), activeEdgeTable.end(),
            [currentY](const Edge& edge) { return edge.yMax <= currentY; }), activeEdgeTable.end());

        // Sort active edge table by xMin
        std::sort(activeEdgeTable.begin(), activeEdgeTable.end(), [](const Edge& a, const Edge& b) {
            return a.xMin < b.xMin;
        });

        // Fill spans between pairs of intersections
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
            int xStart = static_cast<int>(activeEdgeTable[i].xMin);
            int xEnd = static_cast<int>(activeEdgeTable[i + 1].xMin);
            for (int x = xStart; x <= xEnd; ++x) {
                SDL_RenderDrawPoint(renderer, x, currentY);
            }
        }

        // Increment y and update xMin values in active edge table
        ++currentY;
        for (auto& edge : activeEdgeTable) {
            edge.xMin += edge.inverseSlope;
        }
    }
}
Integrate Clipping and Drawing
Now integrate the clipping and drawing logic into the rendering methods:

For Points:

cpp
Copy code
void Point::render(const Renderer& renderer, const Camera& camera, const RenderOptions& options) {
    auto polygon = toPolygon();
    renderer.renderPolygon(polygon, camera.getFrustum());
}
For Lines:

cpp
Copy code
void Line::render(const Renderer& renderer, const Camera& camera, const RenderOptions& options) {
    auto polygon = toPolygon();
    renderer.renderPolygon(polygon, camera.getFrustum());
}
For Polygons:

cpp
Copy code
void Polygon::render(const Renderer& renderer, const Camera& camera, const RenderOptions& options) {
    auto polygon = toPolygon();
    renderer.renderPolygon(polygon, camera.getFrustum());
}
Rendering Scene
Ensure the scene rendering method uses the updated render methods:

cpp
Copy code
void Renderer::renderScene(const Scene& scene, const ViewFrustum& frustum, const Camera& camera, const RenderOptions& options) {
    for (const auto& object : scene.getObjects()) {
        auto polygon = object->toPolygon();
        std::vector<Vec3> clippedPolygon = polygon;

        // Clip the polygon against the frustum planes
        auto planes = frustum.getFrustumPlanes();
        for (const auto& plane : planes) {
            clippedPolygon = MathUtility::sutherlandHodgmanClip(clippedPolygon, plane.normal, plane.distance);
        }

        // Render the clipped polygon
        if (!clippedPolygon.empty()) {
            drawPolygon(clippedPolygon);
        }
    }
}
Summary
Convert All Objects to Polygons: Implement toPolygon methods for points, lines, and polygons.
Clip Polygons: Clip polygons using the Sutherland-Hodgman algorithm against the frustum planes.
Generalized Draw Polygon Method: Implement a method to draw the resulting clipped polygons.
Implement Scanline Fill Algorithm: To fill the polygons instead of just drawing outlines.
Update Render Methods: Update the render methods of Point, Line, and Polygon to utilize the new clipping and drawing methods.
By treating everything as polygons and handling clipping uniformly, you achieve a clean and consistent rendering pipeline that adheres to modern graphics programming practices.

# Suggested Order and Next Steps for Renderer Project

## Suggested Order

1. **2D Transformations**
2. **Handling Auto-Save**
3. **Dealing with 3D Space**
4. **Creating a GUI**

## Next Steps and Hints

### 2D Transformations

1. **Translation**: Move objects in 2D space.
   - Apply translation matrices to your objects' coordinates.
   - `x' = x + tx`, `y' = y + ty`

2. **Rotation**: Rotate objects around a point (usually the origin or the object's center).
   - Use rotation matrices:
   - `x' = x * cos(θ) - y * sin(θ)`, `y' = x * sin(θ) + y * cos(θ)`

3. **Scaling**: Change the size of objects.
   - Apply scaling matrices to your objects' coordinates.
   - `x' = x * sx`, `y' = y * sy`

4. **Combining Transformations**: Combine multiple transformations into a single transformation matrix.

### Auto-Save

1. **Periodic Saves**: Use a timer to periodically save the scene.
2. **Save on Quit**: Ensure the scene is saved when the application is closed.

### Moving to 3D Space

1. **Understanding 3D Geometry**: Familiarize yourself with 3D vectors, matrices, and transformations.
2. **Projection**: Implement perspective or orthographic projection to convert 3D coordinates to 2D screen coordinates.
3. **Rendering Pipeline**: Adapt your rendering pipeline to handle 3D objects.

### Developing a GUI

1. **Choosing a Library**: Decide on a GUI library (e.g., ImGui).
2. **Building Basic UI**: Start with simple UI elements for creating and manipulating objects.
3. **Enhancing Functionality**: Add more advanced features for scene management.

1. Basic Object Rendering:
Begin by implementing classes for basic geometric objects like points, lines, and polygons.
Implement methods to render these objects in the terminal using simple ASCII art or basic graphical representations.
2. Static Scene Rendering:
Create a scene class to manage the state of the scene and store objects.
Implement a rendering loop to iterate over objects in the scene and render them to the terminal.
Start with a static scene where objects are positioned at fixed coordinates within the terminal.
3. Dynamic Object Placement:
Add support for dynamic object placement by allowing users to specify the position and properties of objects via command-line input.
Update the rendering logic to adjust object positions based on user input and changes to the scene state.
4. Terminal Window Resizing:
Handle terminal window resizing events by detecting changes in the terminal window size.
Update the viewport dimensions and adjust the rendering process accordingly to ensure objects are correctly positioned within the resized terminal window.
5. Interactive User Controls:
Implement basic user controls for navigating the scene, such as panning, zooming, and rotating the viewpoint.
Allow users to interactively manipulate objects by applying translations, rotations, and scaling operations.
Refinement and Optimization:
Refine the rendering pipeline and optimize performance as needed.
Add error handling and validation to ensure robustness and reliability.
Fine-tune the user interface and improve usability based on user feedback.
By following this iterative approach, you can start with a simple implementation of your terminal-based math visualization project and gradually add features and functionality as you progress. This approach allows you to build upon your existing codebase and incrementally enhance the project while maintaining a manageable scope.

Addressing your concerns:

1. Rendering Beyond the Screen:

In a terminal-based renderer, objects will need to be aware of the terminal's dimensions to determine if they are rendering beyond the screen boundaries.
One approach is to pass the terminal dimensions to the render() method of each object. The object can then use this information to adjust its rendering accordingly, ensuring that it stays within the visible portion of the terminal.
Alternatively, you could have the Scene class manage the rendering process and provide each object with its position relative to the viewport. The object can then use this information to determine if it should render itself.

2. Object Requirements for Rendering:

For an object to render itself, it typically needs information about its position, size, and appearance.
Position: The object should know its coordinates relative to the viewport or the terminal window.
Size: The object should have dimensions to determine its boundaries for rendering.
Appearance: The object may have attributes such as color or texture that define its visual representation.
Additionally, the object may need access to terminal-specific APIs or libraries to perform rendering operations.
Considering your early project phase, it's beneficial to start thinking about these aspects early on, even if you're not implementing them immediately. Planning ahead helps ensure that your design can accommodate future requirements and facilitates a smoother development process as your project evolves.

Am I sure this is right? Yes, addressing considerations such as rendering boundaries and object requirements early on in the design phase helps lay a solid foundation for your terminal-based renderer project, even if implementation details are not finalized.
