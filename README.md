# mathematical

# Notes

TODOS:

- Load from JSON to include size
- Render frustum and debug it to get better near clip plane
- Debug frustrum and maybe add opacity indicator on it to debug that

    All object render methods

 so I think a couple things might be wrong here, hoping to get your input. I'm doing this project to get better at graphics programming so really want to follow their standards and models while building up complexity in layers:

- Objects not scaling based on distance:
So maybe due to my own ignorance, I thought my perspective matrix would also help items scale based on distance but this isn't the case it seems like? What is typically used to do that?

- My partner made a solid point about how our objects: We have a Object base class and Point, Line, and Polygon all inherit from it. My partner was referencing SVG when he said that point and line don't really mean anything, it's only when they have like a stroke weight that it worth drawing. But in our world, a point kinda corresponded to a single pixel BEFORE dealing with some sort of perspective scaling. How do other rendering engines or in general graphics engines or game engines deal with these concepts?

- He also brought up a good point about the illusion of things fading out, like if an objcet is more than halfway towards the far clip, we should do something to make it seem like its fading out like alter opacity -- any thoughts?

- Taking into account scale based on perspective, does the matrix already do that?
- take into account opacity as things move further to the clip plane
- Consider a point not really having an inherent size
- Same with a line, if a line has no stroke weight it has no 'width' per se

- potentially refactor shapes to consider this, like having object have a stroke

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
