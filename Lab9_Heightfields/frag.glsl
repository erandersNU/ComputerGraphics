#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// And our normal
in vec3 norm;
// And our fragment position for lighting
in vec3 fragPos;

// We always define a fragment color that we output.
out vec4 fragColor;

// Maintain our uniforms.
uniform sampler2D colorTex;              // our color texture

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(colorTex, texCoords);
}