#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex;

out vec4 vertexColor;
out vec2 textCoords;

void main() {
    gl_Position = vec4(position, 1.0f);
    vertexColor = vec4(color, 1.0f);
    textCoords = tex;
}