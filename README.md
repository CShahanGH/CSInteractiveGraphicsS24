# Interactive Graphics

During the 2024 winter semester at ETSU I developed a 3d graphics game from scratch using c++ and OpenGL

## Summary of Topics 

Introduction to Computer Graphics
* Raster Images
* RGB Color
* Alpha Compositing

OpenGL Graphics Pipeline
* What is a GPU?
* Vertex Specification
* Vertex Shader
* Rasterization
* Fragment Shader

Graphics
* 2D Vector Math
  - Calculating a vector between two points
  - Calulating the magnitude
  - Normalizing a vector
 
Scene Graph
* Responsibilities of the vertex buffer
* Responsibilities of the graphics object
* Responsibilities of the scene
* Responsibilities of the renderer
* How to calculate the reference frame of child objects

Texture Mapping
* Demonstrate how clamping and repeating works
* Demonstrate how nearest neighbor and bilinear filtering works
* Explain the process of setting up a texture in OpenGL

Indexed Arrays
* Demonstrate how to set up an indexed buffer
* Demonstrate how to set up a dynamic buffer

3D
* Explain the parameters to set up the perspective projection matrix
* Set up the vertices of a simple 3D object

Render Loop
* Write a simple algorithm of the render loop
* Briefly describe each step in the render loop
* Explain what frame rate is
* Explain what delta time is
* Calculate new position given delta time and speed

Camera Control
* Describe the process of making the camera look forward
* Explain what spherical coordinates are
* Describe the process of converting spherical coordinates to a reference frame

Lighting
* Explain what ambient lighting is
* Explain what diffuse lighting is
* Explain what the angle of incidence is
* Calculate the surface normal
* Explain what specular lighting is
* Create a very basic material structure (C++)

Curves
* Generate the vertices of a circle given its parametric equation
* Explain what a quadratic Bezier curve is
* Generate the vertices of a quadratic Bezier curve given its parametric equation
* Explain what a Bezier patch is

Drawing Review and Instancing
* Explain the major benefit of drawing with an indexed buffer
* Explain what instancing is
* Describe the process of buffer allocation when using instancing and dynamic drawing

Ray Casting
* Calculate a ray, given the start and end of a line segment
* Calulate a point along the ray given its offset
* Determine the specifications of a plane
* Given the algorithm, determine whether or not a ray intersects a plane

Bounding Box
* Explain what a bounding box is
* Calculate the planes and reference frame of an AABB
* Describe how to determine if a ray and a bounding box are intersecting

## Summary of Classes

### BaseObject

Base object is the the base class for every object and gives all objects a logger 

### Bounding Box

A bounding box is simple put a gemetric shape (generally a cuboid since its a bounding box) that definnes the size and spacial location of another 3d object. Bounding boxes are commonly used for collision detection.
The Bounding Box class has implementations to determine if it's intersecting with a Ray, overlapping with another BoundingBox, or on top of another bounding box 


