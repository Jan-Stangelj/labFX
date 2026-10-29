#version 460 core

layout(location = 0) in vec2 uvIn;

layout(location = 0) out vec4 color;


layout(location = 0) uniform sampler2D texture0;

void main() {
    color = vec4(texture(texture0, uvIn).rgb, 1.0);
}