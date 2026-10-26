#include "init.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "texture2d.hpp"

int main(void) {

    init(true);

    window w;
    w.create(800, 600, "labFX");
    glViewport(0, 0, 800, 600);
    
    constexpr GLfloat vertices[] = {
        //  x          y         z         u         v
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f // top left
    };
    constexpr GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    }; 

    GLuint emptyVao = 0;
    glGenVertexArrays(1, &emptyVao);
    glBindVertexArray(emptyVao);

    buffer vertexBuffer;
    vertexBuffer.create(sizeof(vertices), vertices);

    buffer indexBuffer;
    indexBuffer.create(sizeof(indices), indices);

    texture2d texture;
    texture.create("../assets/textures/red_brick.png", GL_RGB8, true);
    texture.generateMipmaps();

    constexpr GLfloat color[] = {
        //  r         g         b         a
        0.5f, 1.0f, 0.5f, 1.0f
    };

    buffer colorMixBuffer;
    colorMixBuffer.create(sizeof(color), color);

    GLuint ubo = 0;
    glCreateBuffers(1, &ubo);
    glNamedBufferStorage(ubo, sizeof(color), color, 0);

    shader simpleShader;
    simpleShader.loadFromFile("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) running = false;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexBuffer.bind(bufferTarget::SHADER_STORAGE_BUFFER, 0);
        indexBuffer.bind( bufferTarget::SHADER_STORAGE_BUFFER, 1);
        texture.bind(0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
        simpleShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        w.swapBuffers();
    }

    quit();
    return 0;

}
