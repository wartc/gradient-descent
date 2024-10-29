#version 460 core

layout (location = 0) in vec4 vPos;

uniform mat4 view;
uniform mat4 proj;

out vec4 fPos;

void main() {
    gl_Position = proj * view * vPos;
    fPos = vPos;
}
