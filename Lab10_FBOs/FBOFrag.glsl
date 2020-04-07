#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;

// We always define a fragment color that we output.
out vec4 fragColor;

// Maintain our uniforms.
uniform sampler2D FBOTex;              // our primary texture

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  // The variable 'color' will now contain whatever would have been on screen if we were rendering directly.
  vec3 color = texture(FBOTex, texCoords).rgb;
  // We can now modify things a bit to provide some nice post-processing effects.
  // TODO - Implement some type of post-processing effect here.
  fragColor = vec4(color, 1.0);
}