# Lab 5 - Part 2 - Index Buffers

<img align="right" src="./media/lab.png" width="400px" alt="picture">

> "Rendering a rectangle more efficiently"

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

Last lab we rendered a triangle to the screen! There was a bit of setup code involved with Qt and OpenGL to prepare. As a recap:

* We had to initialize Qt and get window and OpenGL Graphics Context
* We had to setup a buffer that contained data for our vertices
* We had a minimal vertex and fragment shader that told OpenGL what to do with that data
* Finally, we use glDrawArrays to output our data to the screen.

Today we want to render some data in a slightly more efficient way, using what is called an "Index Buffer". Index buffers allow us to select which vertices we want to draw through an index. You will also get some exposure to detecting keyboard input from a user with Qt.

## Part 1 - Setting up your Environment

For this lab, you need to build your project using the standard CMake build process.


## Part 2 - Index Buffers

You will find in the code "TODO" sections in the BasicWidget.cpp.

Today your goal is to render:

- A triangle or a square depending on which indicies are selected to render
- Use of Qt event handlers
  - If a user presses the 'left arrow key' a triangle appears
  = If a user presses rhe 'right arrow key' a rectangle appears

## Part 3 - Shaders

### Vertex Shader Quick Glance

```cpp
// ==================================================================
#version 330 core

layout(location=0)in vec3 position; // We explicitly state which is the vertex information (The first 3 floats are positional data, we are putting in our vector)
layout(location=1)in vec3 vertexColor; // Our second attribute which is the color.

// Do not forget this!
out vec3 theColor;

void main()
{
  // gl_Position is a special glsl variable that tells us what
  // postiion to put things in.
  // It takes in exactly 4 things.
  // Note that 'w' (the 4th dimension) should be 1.
  gl_Position = vec4(position.x, position.y, position.z, 1.0f);

  // Store the vertex color that we take in as what we will output
  // to the next stage in the graphics pipeline.
  theColor = vertexColor;

}
// ==================================================================
```

### Fragment Shader Quick Glance

```cpp
  // ==================================================================
  #version 330 core
  out vec4 color;

  in vec3 theColor;

  void main()
  {
   // color is a vec4 representing color. Because we are in a fragment
   // shader, we are expecting in our pipeline a color output.
   // That is essentially the job of the fragment shader!
    color = vec4(theColor, 1.0);
  }
  // ==================================================================
```


## Helpful Resources

Some additional resources to help you through this lab assignment

- [songho tutorial on GL Vertex Array](http://www.songho.ca/opengl/gl_vertexarray.html)
- [Qt Docs](https://doc.qt.io/qt-5/)
- [docs.gl](http://docs.gl/)
- [Learn OpenGL](https://learnopengl.com) - Helpful webpage with many useful
  tutorials
  
## Deliverables

- A triangle or a square depending on which indicies are selected to render.
  - Use Keys to change scene
    - If a user presses 'left arrow key' a triangle appears
    = If a user presses 'right arrow key' a square appears
- Changing USE_QT_OPENGL macro to true and false should result in different rendering setups/execution.  BOTH must work.  
<img align="center" src="./media/lab.png" width="400px" alt="picture">

You must complete this lab by next class. You will run your lab in front of me at the start of the next lab when class starts and tell me what your group # was for that week.

(If you are taking this course online--I will view it)

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Add colors to your shapes! We will work on this next week, and figure out how to add attributes! Note that the provided shaders will work with color as is if you move ahead.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
