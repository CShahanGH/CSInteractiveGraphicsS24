# Interactive Graphics

During the 2024 winter semester at ETSU I developed a 3d graphics game from scratch using c++ and OpenGL with glfw

##Summary of Game 

This is a simple 3d platformer game. The goal of the player is the jump on a series of platform and claim the trophy object. 

## Summary of Classes

### BaseObject

Base object is the the base class for every object and gives all objects a logger 

### Bounding Box

A bounding box is simple put a gemetric shape (generally a cuboid since its a bounding box) that definnes the size and spacial location of another 3d object. Bounding boxes are commonly used for collision detection.
The Bounding Box class has implementations to determine if it's intersecting with a Ray, overlapping with another BoundingBox, or on top of another bounding box 

### Camera

The Camera is the POV of the user. The camera can move forward, backward, lef, and right, and can rotate left, right, up, and down. The camera can also lock on different objects and have free motion with the user's mouse. 

### Generate

Generate creates 3d and 2d objects such as a Cuboid, XZ Plane, XY Plane. Cuboid with Normals, XZ Plane with Normals, XZ Line Circle, Line Cylinder. 

### Geometric Line

Geometric line creates a line giving a start point and a direction 

### Geometric Plane 

The geometric plane class creates a floor and can determine if it's intersecting with a line or ray 

### Graphics Environment

Graphics environment handles multiple initalizes, renders graphics, and processes user inputs 

### Graphics Object

Graphics object defines the reference frame, vertexbuffer, parent objects, children objects, animation, material, indexbuffer, boudning box, and behavior of each graphics object. 

### Highlight Behavior 

Highlight behavior makes an object glow whenever the object is intersecting with a ray (ex. whenever the mouse hovers on an object it glows)

### IAnimation

Interface for animations

### Ibehavior

Interface for behaviors

### Indexbuffer

Index buffer creates iboIds, adds index data to the gl buffer data

### JumpAnimation

JumpAnimation creates an animation for an object to move in the postive y direction 

### MoveAnimation

MoveAnimation creates an animation for an object to move in the negavtive z directon 

### ObjectManger

ObjectManager creates an unordered map of graphics objects and can return an object in the map. 

### Ray

Ray creates an invisible ray giving aa start point and a direction. 

### Renderer

Renderer contains the vaoID, shader, scene, view, and project. The Renderer is responsible is rendering the scene the camera is viewing and rendering each object. 

### RotateAnimation

RotateAnimation rotates an object around the y axis 

### Scene

Scene contains graphic objects and sets the light intensity. 

### Shader

Shader is responsible for compiling the shader program and adding uniforms. 

### Textfile

Textfile handles opening, reading, and trimming files.

### Timer 

Timer keeps track of how many how long the program is running and is useful for animations.

### Vertexbuffer

Vertex buffer contains all the information of each vertex needed for the gpu to render it. 





## Topics Covered

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
