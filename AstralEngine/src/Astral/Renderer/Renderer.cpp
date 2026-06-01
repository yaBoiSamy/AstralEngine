#include <Common.h>
#include "Renderer.h"
#include <glad/glad.h>

namespace Astral
{
    void Renderer::SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize) {
        auto [fbw, fbh] = framebufferSize;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, fbw, fbh);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::PresentFrame(Window& window) {
        window.SwapBuffers();
    }
}
