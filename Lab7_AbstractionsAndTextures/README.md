# Lab 7 - Abstraction and Textures

<img align="right" src="http://www.mshah.io/comp/Spring18/graphics/Lecture/6/lecture.PNG" width="400px" alt="picture">

> "What's another layer of abstraction anyway?"

**Lab materials must be pushed to your repository one week from now before the next class begins**

**Read:** *Labs are designed to be finished in class if you work diligently, but expected to take 1-2 hours outside of class. They are often more 'tutorial' in style, and sometimes the solution may even be provided in pieces for you to type in and experiment. Copying & Pasting is discouraged however--make mistakes, play, and you will further learn the material.*

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

- We created a colored traingle
- We created a perspective camera
- We learned about uniforms

Today we are going to really think about what is going on in our program, and abstract our render. This will help you understand object-oriented programming in C++ as well as think about what code is executing on the CPU and the GPU.

**The good news**: For part 1 I have already done the abstraction. You will have to learn how to use it however!

## Part 1 - Code Review

During your co-ops, internships, and jobs you will often do a code review. Today you will review my code for understanding the design of our abstraction, and to help connect the concepts that we have learned so far. The slides should help, but being able to dive into the code is a valuable skill to have. Once again start with the headers to see how the code works. 

Discuss with your partner the following:

1. What are the advantages/disadvantages of the "Renderable" class?: *Add your answer here*
2. Why do we call Renderable::draw(..) with the matrix info as parameters?: *Add your answer here*
3. How you can move models in the scene?: *Add your answer here*

## Part 2 - Textures

Note: You may use the slides for guidance on completing this task. The deliverables section describes your task with some hints.

### Vertex Shader in a glance

It is worth taking another moment to review a few parts of the vertex shader.

* The **layout** corresponds to our [glEnableVertexAttribArray](http://docs.gl/gl3/glEnableVertexAttribArray) function.
  * Currently we are taking in position data (x,y,z). You'll need to figure out how to take in texture data, and what the corresponding data type should be.
* The **out** qualifier means we are sending data to the next part of the pipeline. From the vertex shader this means we will send data to the fragment shader.
* **uniforms** are values that are passed from CPU to GPU. They are variables that can talk in a way back in forth to modify what is going on.


```c
// ==================================================================
#version 330 core
layout(location = 0) in vec3 position;
// TODO:  Add an input for texture coordinates

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec2 texCoords;

void main()
{
    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);
    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}
// ==================================================================

```

### Fragment Shader in a glance

It is worth taking another moment to review a few parts of the fragment shader.

* The **in** qualifier means we are taking in information from a previous stage of the pipeline (in this case, our vertex shader).
  * The variable should match in datatype and name.
  * Think of these variables scope as 'existing on the GPU' if that is helpful, and that is why the names should match.
* Lookup what a **sampler2D** is.
  * You can see how it is used in 'Object::update' as a hint for how to create one. Another hint is that a uniform **should** match the name in the shader exactly as it is created.

```c
// ==================================================================
#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// We always define a fragment color that we output.
out vec4 fragColor;

// TODO:  Add a sampler to retrieve our color data from!

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(tex, texCoords);
}
// ==================================================================

```

## Helpful Resources

- [docs.gl](http://docs.gl/) useful programming resource
- Start writing some OpenGL 3.3 from here! [learnopengl.com](https://learnopengl.com/) Use this time for graphics!
- [Mip mapping](http://www.tomshardware.co.uk/ati,review-965-2.html)
- [Full video explaining Normal mapping](https://www.youtube.com/watch?v=6_-NNKc4lrk) (A special kind of texturing)

## Deliverables

1. Fill in the texture coordinates for our renderable in BasicWidget::initializeGL().
2. Fill in vert.glsl to take in the texture coordinates (Should be a 1-liner)
3. Add in the sampler2D for frag.glsl (Another 1-line code change)
4. Draw two spinning quads that are textured.
      - You will have to add in another object and modifying the transform somewhere in the code.

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Try changing vertex colors and see if it effects the texture.
- Try changing the color of the texture in the fragment shader.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
