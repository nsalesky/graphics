//
// Created by nicks on 7/1/2022.
//

#include <glad/glad.h>

#include "Framebuffer.h"
#include "Constants.h"
#include <stdexcept>

Framebuffer::Framebuffer(bool attachColorBuffer, bool attachDepthAndStencilBuffer) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    if (attachColorBuffer) {
        unsigned int colorTextureID;
        glGenTextures(1, &colorTextureID);
        glBindTexture(GL_TEXTURE_2D, colorTextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureID, 0);

        glBindTexture(GL_TEXTURE_2D, 0); // unbind the color texture

        m_colorTexture = std::make_shared<Texture>(colorTextureID, TextureType::DIFFUSE);
    }

    if (attachDepthAndStencilBuffer) {
        unsigned int depthStencilTextureID;
        glGenTextures(1, &depthStencilTextureID);
        glBindTexture(GL_TEXTURE_2D, depthStencilTextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT, 0,
                     GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTextureID, 0);

        glBindTexture(GL_TEXTURE_2D, 0); // unbind the depth-stencil texture

        m_depthStencilTexture = std::make_shared<Texture>(depthStencilTextureID, TextureType::DEPTH_AND_STENCIL);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fbo);
}

void Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::shared_ptr<Texture> Framebuffer::GetColorTexture() {
    if (!m_colorTexture) {
        throw std::runtime_error("No color buffer was attached in the constructor!");
    }

    return m_colorTexture;
}

std::shared_ptr<Texture> Framebuffer::GetDepthStencilTexture() {
    if (!m_depthStencilTexture) {
        throw std::runtime_error("No depth+stencil buffer was attached in the constructor!");
    }

    return m_depthStencilTexture;
}