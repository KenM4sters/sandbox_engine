#pragma once 
#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/s_shader_resource.h"
#include "../resources/texture.h"

/**
 * The PostProcessing class completely changes the way that the scene is rendered to the window.
 * Instead of rendering a scene as usual, if PostProcessing is enabled, then the entire scene is instead
 * rendered as a texture to a quad that is drawn to perfectly fit the window dimensions. 
 * 
 * The benefit of this is that we can very easily manipulate fragment data of a texture and even the
 * quad vertex data itself, allowing for a whole host of so called "postprocesssing" techniques to 
 * enhace the visual output of our program. Some examples would include inverting colors, bloating and blurring
 * them to achieve a "bloom" effect, and so on...
*/

class PostProcessing {
    public:
        ~PostProcessing() {
            #ifdef SANDBOX_DEBUG 
                std::cout << "PostProcessing is being destroyed!" << std::endl;
            #endif
        }
        unsigned int width_, height_;
        Texture2D tex_ = Texture2D(SANDBOX_OBJECT, "diffuse");
        Shader* shader_;
        // Constructor handles generating a custom buffer and setting necessary texture data
        // so that its render to recieve the data from rendering our scene to this custom frame buffer.
        PostProcessing(unsigned int width, unsigned int height, SShaderResource* shader);
        // Binds our new framebuffer so that the scene renders to this buffer instead of the standard one that we actually see.
        // Remember - we don't want our scene to originally render to the screen (we don't want to see it just yet).
        void BeginRender(); 
        // Rebind the standard framebuffer since we're done with rendering the scene...
        void EndRender();
        // ...and now we want to render a quad to the standard framebuffer set in EndRender() that we can actually
        // see, since this quad has been textures with the visual output of our scene in our custom framebuffer. 
        void RenderQuad();

    private:
        unsigned int FBO_, VAO_, RBO_;
        // Allocate memory for a basic quad.
        void InitQuad(); 

};