//
// Created by nicks on 7/1/2022.
//

#ifndef GRAPHICS_FRAMEBUFFER_H
#define GRAPHICS_FRAMEBUFFER_H

#include <memory>
#include "Texture.h"

/**
 * A Framebuffer that can be used to accumulate buffers of OpenGL data, such as color and depth+stencil data,
 * for subsequent rendering passes.
 */
class Framebuffer {
public:
    /**
     * Constructs a new framebuffer with each of the specified buffer attachments.
     * @param attachColorBuffer should a texture be attached to accumulate color buffer data?
     * @param attachDepthAndStencilBuffer should a texture be attached to accumulate depth+stencil buffer data?
     */
    Framebuffer(bool attachColorBuffer = true, bool attachDepthAndStencilBuffer = false);
    ~Framebuffer();

    /**
     * Binds this framebuffer so that rendering calls will output their results in this framebuffer instead of the
     * screen.
     */
    void Bind();

    /**
     * Unbinds this framebuffer to restore rendering output to the screen.
     */
    void Unbind();

    /*
     * NOTE: I could have chosen to not throw any exceptions in the below methods and just return empty shared_ptrs,
     * but that just felt risky to me. I would rather not run the risk of assuming these textures aren't null and
     * trying to bind them.
     */

    /**
     * Gets the texture for the color buffer attachment if a color buffer attachment was created in the constructor.
     * @return the color buffer texture
     * @throws std::runtime_error if no color buffer was attached in the constructor
     */
    std::shared_ptr<Texture> GetColorTexture();

    /**
     * Gets the texture for the depth+stencil buffer attachment if such a buffer attachment was created in the constructor.
     * @return the depth+stencil buffer texture where the first 24 bits of each value contains depth information, and the final 8 bits contain stencil information
     * @throws std::runtime_error if no depth+stencil buffer was attached in the constructor
     */
    std::shared_ptr<Texture> GetDepthStencilTexture();
private:
    unsigned int m_fbo;

    // It's possible that these pointers could be null if no textures were attached (for whatever pointless reason)
    std::shared_ptr<Texture> m_colorTexture;
    std::shared_ptr<Texture> m_depthStencilTexture;
};


#endif //GRAPHICS_FRAMEBUFFER_H
