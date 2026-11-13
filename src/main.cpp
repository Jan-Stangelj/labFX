#include "init.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "texture2d.hpp"
#include "debugCamera.hpp"
#include "stopwatch.hpp"
#include "sampler.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

int main(void) {

    init(true);

    window w;
    w.create(1920, 1080, "labFX");
    glViewport(0, 0, 1920, 1080);

    GLuint emptyVao = 0;
    glGenVertexArrays(1, &emptyVao);
    glBindVertexArray(emptyVao);

    constexpr GLfloat vertices[] = {
        //  x          y         z         u         v
        0.5f,  0.5f, 0.0f, 100.0f, 100.0f, // top right
        0.5f, -0.5f, 0.0f, 100.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 100.0f // top left
    };
    buffer vertexBuffer;
    vertexBuffer.create(sizeof(vertices), vertices);

    constexpr GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    }; 
    buffer indexBuffer;
    indexBuffer.create(sizeof(indices), indices);

    texture2d texture;
    texture.create("../assets/textures/red_brick.png", GL_RGB8, true);
    texture.generateMipmaps();

    sampler sampl;

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f));
    buffer modelMatrixBuffer;
    modelMatrixBuffer.create(sizeof(glm::mat4), &modelMatrix);

    debugCamera cam;

    shader simpleShader;
    simpleShader.loadFromFile("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    double deltaTime = 0.0f;
    bool mouseCaptured = false;
    bool running = true;
    while (running) {

        stopwatch time;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) running = false;

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_RIGHT) mouseCaptured = w.captureMouse(true);
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP   && event.button.button == SDL_BUTTON_RIGHT) { mouseCaptured = false; w.captureMouse(false); }
            if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) { mouseCaptured = false; w.captureMouse(false); }

            if (event.type == SDL_EVENT_MOUSE_MOTION && mouseCaptured) cam.updateDirection(event.motion.xrel, -event.motion.yrel);
        }

        if (mouseCaptured) cam.updateOrigin(deltaTime);
        cam.apply(0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexBuffer.bind(bufferTarget::SHADER_STORAGE_BUFFER, 0);
        indexBuffer.bind( bufferTarget::SHADER_STORAGE_BUFFER, 1);
        texture.bind(0);
        sampl.bind(0);
        modelMatrixBuffer.bind(bufferTarget::UNIFORM_BUFFER, 1);
        simpleShader.use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        w.swapBuffers();

        deltaTime = time.get();

    }

    quit();
    return 0;

}
