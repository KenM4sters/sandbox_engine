# Sandbox Engine - C++, openGL
---
## Objectives
- To create a simple scene where users can add, move, scale and delete objects, as well as use a 
range of postprocessing effects.
- Project structure should be very modular, and serve as base for future projects.
- All naming conventions and formats of classes/structs should be extremely consistent. 
---
## Progress - 11/03
## Good
- Generally happy with how the GLFW window and OpenGL context is loaded in terms of file structure and use of classes/structs, and that mostly applies to the rest of the application too, with the exception of the Camera class.
- Very happy with how my naming conventions have been throughout the development so far - so long as I'm not forced to change, I will definitely be sticking to this standard for the foreseable future.
## Needs improvement
### The Camera Class
- As mentioned, the way that I've implemented the Perspective Camera, although adequate, feels way too forced and connected with the rest of the scene objects. The camera really shouldn't be passed around anywhere and should be available for all game objects to read from, but not mutate. I'm thinking of maybe making the Camera either static, or as a wider part of some "Game" class that all game objects inherit from?
### Render System
- At the moment, my render system involves creating meshes from geometries and materials and adding buffer attributes like normals and texture coordinates manually, at the cost of creating new glbuffers. Initially, I liked this idea of seperating the a game object into 3 different classes, but this doesn't really implement well with loading external 3d models - I need a single, revised way of rendering where an obejct can take in a single vector of some struct that defines all the buffer attributes that are needeed, as well as container of textures - high priority.
### Const Keyword
- I have a bad habit of assuming mutability, and then only specifiying for non-mutability if it's really necessary/obvious to me that that something shouldn't be changed. As a result, the const keyword can be found very sparsly throughout the program, and almost never for functions - high priority (maybe I should use rust more often...)
### Uses of smart pointers, regular pointers and references
- I feel as if I need to clamp down on being consistent with these different ways of passing my reference. While I realise that not all of them may be viable in any particular circumstance (references can't be null, for example), not much thought goes into which one I should use at the moment - Being honest with myself, it's generally just what I feel like using, which obviously should not be the case - high priority.
---
## Progress - 12/03
- In the middle of a complete refactoring of the rendering system (meshes, lights, shaders, textures etc...), with the ambition to achieve something much less verbose and with cleaner abstractions. 
## The Idea
### Background
- All of the game objects in the scene need their shaders to be aware of the positions of all the lights and the camera in order for proper shading. Originally, I achieved this by literally passing pointers to the lights and cameras into the meshes so that they can set the apropriate uniforms in their draw functions, which I really wasn't comfortable with. 
### Solution
- In essence, the plan is to not give meshes access to the camera or lights, but instead have their shaders preset with the necessary information. All shaders will start their lives in the scene with their compilation, and subsequently binded and have their uniforms set to the camera's position, view matrix and perspective matrix data.
- Next, their passed to the lights render system by reference that loops through them and sets uniforms to all the lights data (positions, intensity etc...).
- Only then are they passed to the Meshes, where the only uniforms that need to be set are the world transformations (model matrix).
- The whole process is like a conveyerbelt of shaders, where the camera, lights and gameobjects are all lined up in order, ready to take them when they can reach them, only they can change them without taking off the conveyorbelt (they're always passed by reference).
- This is completely impromptu, and I've had difficulty finding examples of how other people implement their rendering systems, but it sounds very viable to me and I'm looking forward to seeing how it goes. 
---
## Progress 13/03
- After a lot of code restructuring, everything is rendering again now, except it's so much cleaner and easier to implement - very happy with how the project is structured now, despite perhas seeming a little abstract at first. 
- With that completed, the focus now will be on loading 3D models ussing Assimp, which should be signifcantly easier now than with the previous structure. Additionally, I need to start on integrating some kind of collision detection system so that I can begin to change the "fly" camera into more of an FPS one, where you forced to move around a height-mapped plane instead of a flat one.
- 3 very important aspects of the engine to get right, so I've decided to make a new git branch called "experimental", and will likely add more in case I need to rebase. 
## Progress 14/03
- Models can now be loaded and transformed.
- BufferGeometry class has been significantly improved to be flexible in terms of the data that it can creater buffers for in memory for rendering.
- 


