#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec2 texCoords;

void main()
{
    // We write position 
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);
    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}