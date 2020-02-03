# Lab 5 - Part 1 - First Shape

<img align="right" src="./media/lab.png" width="400px" alt="picture">

> "Diving into OpenGL"

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

Previously we built the primary primitive for our software renderer--the triangle! Now we are going to recreate that scene with OpenGL. Today's lab also requires a little bit of patience, as we get acquainted with the support code.

Today your goal is to render:

- A smaller triangle than what is given (This requires decreasing some data
values).
- A triangle of a different color (something other than orange)
- A background color different than green

## Part 1 - Setting up your Environment

For this lab, you need to build the project using the standard CMake build process.

## Part 2 - Shaders at a glance

Take a look at the shaders in your program. See where they are stored, and what they are calling. Remembering what Shaders are, and think about what you need to modify (or rather, which of the two shaders you need to modify). 

Both shaders are here for your reference in case you want a fresh copy of either.

### Example Vertex Shader

```cpp
#version 330 core

in vec4 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, position.w);
};
```

### Example Fragment Shader
```cpp
#version 330 core

out vec4 color;

void main()
{
      color = vec4(1.0f, 0.5f, 0.0f, 1.0f);
};
```

## Part 3 - Buffer Objects

Remember, a vertex buffer object is something that is storing some data and sent to the GPU. Think about what this means when attemptin to solve today's task. [This tutorial](http://www.songho.ca/opengl/gl_vbo.html) provides a nice explanation of Vertex Buffer Objects (though the code is for a slightly older version of OpenGL).


## Helpful Resources

Some additional resources to help you through this lab assignment

- [Cornell Math review](https://www.cs.cornell.edu/courses/cs1110/2012fa/assignments/assignment5/index.php)
- [Learn OpenGL](https://learnopengl.com) - Helpful webpage with many useful
  tutorials


## Deliverables

- A smaller triangle(than what is given) that runs in OpenGL that has a different color background, and  different triangle color.

<img align="center" src="./media/success.png" width="400px" alt="success">

You must complete this lab by next class. You will run your lab in front of me at the start of the next lab when class starts and tell me what your group # was for that week.

(If you are taking this course online--I will view it)

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Try to draw two triangles at once.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
