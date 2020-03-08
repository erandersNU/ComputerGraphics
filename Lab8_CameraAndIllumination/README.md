# Lab 8 - Camera and Illumination

<img align="right" src="http://www.mshah.io/comp/Spring18/graphics/Lab/7/lab.png" width="400px" alt="picture">

> "Lights--Camera--Action!"

**Lab materials must be pushed to your repository one week from now before the next class begins**

**Read:** *Labs are designed to be finished in class if you work
  diligently, but expected to take 1-2 hours outside of class. They
  are often more 'tutorial' in style, and sometimes the solution may
  even be provided in pieces for you to type in and
  experiment. Copying & Pasting is discouraged however--make mistakes,
  play, and you will further learn the material.*

## Modify this section

- How many hours did it take you to complete this lab?
- Did you collaborate with any other students/TAs/Professors?
- Did you use any external resources? (Cite them below)
  - tbd
  - tbd
- (Optional) What was your favorite part of the lab?
- (Optional) How would you improve the lab?

## Logistics

You will be working on your own laptop today.

## Description

Last lab we rendered a colored triangle and a square to the screen. As a recap:

- We created two textured and moving quads.

Today we are going to spend half of our time manipulating our 'view
matrix' (i.e. the camera), and the other half of the time modifying
both our vertex and fragment shaders to emulate lights in our scene.

**The good news**: For part 2 I have provided a correct
  shader. Understanding it will be important for when you implement
  normal mapping later on.

### Known hacks in this lab

- The normals are all fixed and pointing in the same direction. I took a short-cut for simplicity. :)

## Part 1 - Camera

A good camera can make or break a 3D scene. Today we are going to
implement a very simple one!

Moving should be relatively straightforward (think about which vector
you need to modify and what direction), but for the mouseLook, you
will have to think a little bit about what you are manipulating.

Note: For the mouselook, you may have to scale (i.e. multiply some
floating point number) how sensitive your mouse is relative to how
much you move around the screen.


## Part 2 - Light

Note: You may use the slides for guidance on completing this task. The
deliverables section describes your task with some hints.

### Vertex Shader in a glance

This is what you are suppose to implement. Study it.

```c
// ==================================================================
#version 330 core
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec3 normals; // Our second attribute - normals.
layout(location=2)in vec2 texCoord; // Our third attribute - texture coordinates.
layout(location=3)in vec3 tangents; // Our third attribute - texture coordinates.
layout(location=4)in vec3 bitangents; // Our third attribute - texture coordinates.

// If we are applying our camera, then we need to add some uniforms.
// Note that the syntax nicely matches glm's mat4!
uniform mat4 model; // Object space
uniform mat4 view; // Object space
uniform mat4 projection; // Object space

// Export our normal data, and read it into our frag shader
out vec3 myNormal;
// Export our Fragment Position computed in world space
out vec3 FragPos;
// If we have texture coordinates we can now use this as well
out vec2 v_texCoord;


void main()
{

    gl_Position = projection * view * model * vec4(position, 1.0f);

    myNormal = normals;
    // Transform normal into world space
    FragPos = vec3(model* vec4(position,1.0f));

    // Store the texture coordinatests which we will output to
    // the next stage in the graphics pipeline.
    v_texCoord = texCoord;
}
// ==================================================================

```


### Fragment Shader in a glance

This is what you are suppose to implement. Study it.

```c
// ==================================================================
#version 330 core

// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// Our light source data structure
struct PointLight{
    vec3 lightColor;
    vec3 lightPos;
    float ambientIntensity;

    float specularStrength;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pointLights[1];


// Used for our specular highlights
uniform mat4 view;


// Import our normal data
in vec3 myNormal;
// Import our texture coordinates from vertex shader
in vec2 v_texCoord;
// Import the fragment position
in vec3 FragPos;

// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 

void main()
{
    // Compute the normal direction
    vec3 norm = normalize(myNormal);
    
    // Store our final texture color
    vec3 diffuseColor;
    diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;

    // (1) Compute ambient light
    vec3 ambient = pointLights[0].ambientIntensity * pointLights[0].lightColor;

    // (2) Compute diffuse light
    // From our lights position and the fragment, we can get
    // a vector indicating direction
    // Note it is always good to 'normalize' values.
    vec3 lightDir = normalize(pointLights[0].lightPos - FragPos);
    // Now we can compute the diffuse light impact
    float diffImpact = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = diffImpact * pointLights[0].lightColor;

    // (3) Compute Specular lighting
    vec3 viewPos = vec3(0.0,0.0,0.0);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = pointLights[0].specularStrength * spec * pointLights[0].lightColor;

    // Calculate Attenuation here
    // distance and lighting... 

    // Our final color is now based on the texture.
    // That is set by the diffuseColor
    vec3 Lighting = diffuseLight + ambient + specular;

    // Final color + "how dark or light to make fragment"
    if(gl_FrontFacing){
        FragColor = vec4(diffuseColor * Lighting,1.0);
    }else{
        // Additionally color the back side the same color
         FragColor = vec4(diffuseColor * Lighting,1.0);
    }
}

```

## Helpful Resources

- [docs.gl](http://docs.gl/) useful programming resource
- Start writing some OpenGL 3.3 from here! [learnopengl.com](https://learnopengl.com/) Use this time for graphics!
- [Mip mapping](http://www.tomshardware.co.uk/ati,review-965-2.html)
- [Full video explaining Normal mapping](https://www.youtube.com/watch?v=6_-NNKc4lrk) (A special kind of texturing)

## Deliverables

1. Implement movement of the camera
2. Implement 'mouselook' in the camera
3. Implement *some* model of light in your scene.

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Try to make your camera move smoothly!
- Implement a 'jump' operation for your camera
- Try to implement specular shading for your object using the provided specular.ppm and container.ppm

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
