# Sandbox Engine - C++, openGL
---
## Objectives
- To create a simple scene where users can add, move, scale and delete objects, as well as use a 
range of postprocessing effects.
- Project structure should be very modular, and serve as base for future projects.
- All naming conventions and formats of classes/structs should be extremely consistent. 
## Progress - 11/03
## Good
---
- Generally happy with how the GLFW window and OpenGL context is loaded in terms of file structure and use of classes/structs, and that mostly applies to the rest of the application too, with the exception of the Camera class.
- Very happy with how my naming conventions have been throughout the development so far - so long as I'm not forced to change, I will definitely be sticking to this standard for the foreseable future.
## Needs improvement
---
### The Camera Class
- As mentioned, the way that I've implemented the Perspective Camera, although adequate, feels way too forced and connected with the rest of the scene objects. The camera really shouldn't be passed around anywhere and should be available for all game objects to read from, but not mutate. I'm thinking of maybe making the Camera either static, or as a wider part of some "Game" class that all game objects inherit from?
### Render System
- At the moment, my render system involves creating meshes from geometries and materials and adding buffer attributes like normals and texture coordinates manually, at the cost of creating new glbuffers. Initially, I liked this idea of seperating the a game object into 3 different classes, but this doesn't really implement well with loading external 3d models - I need a single, revised way of rendering where an obejct can take in a single vector of some struct that defines all the buffer attributes that are needeed, as well as container of textures - high priority.
### Const Keyword
- I have a bad habit of assuming mutability, and then only specifiying for non-mutability if it's really necessary/obvious to me that that something shouldn't be changed. As a result, the const keyword can be found very sparsly throughout the program, and almost never for functions - high priority (maybe I should use rust more often...)

