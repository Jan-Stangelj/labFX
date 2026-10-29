#version 460 core

struct vertex {
    float position[3];
    float uv[2];
};

layout(binding = 0, std430) readonly buffer verticesBuffer {
    vertex vertices[];
};
layout(binding = 1, std430) readonly buffer indicesBuffer {
    uint indices[];
};

layout(binding = 0, std140) uniform cameraMatrixBuffer {
    mat4 viewMatrix;
    mat4 projectionMatrix;
};
layout(binding = 1, std140) uniform modelMatrixBuffer {
    mat4 modelMatrix;
};

vec3 getPosition(vertex v) { return vec3(v.position[0], v.position[1], v.position[2]); }
vec2 getUV(vertex v) { return vec2(v.uv[0], v.uv[1]); }

layout(location = 0) out vec2 uvOut;

void main() {
    vertex v = vertices[indices[gl_VertexID]];

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(getPosition(v), 1.0);

    uvOut = getUV(v);
}