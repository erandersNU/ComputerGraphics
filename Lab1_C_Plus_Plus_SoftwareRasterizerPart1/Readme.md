# Lab 1 - C++ Software Rasterizer Part 1

<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/c/c2/LineBresenham.gif" width="400px" alt="picture">

> Fundamentals of C++ && Fundamentals of Graphics

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

You will be working on your own laptop today. For this lab you will need to be able to view PPM images.

### How do I view a PPM image?

1. On linux type `display myImage.ppm` (You may need to install image magick library)
2. Download your respository locally after you commit any changes. Then view your .ppm in an image editor like GIMP(https://www.gimp.org).
3. If you are working on the Khoury servers, depending on your terminal and ssh client, you can actually view images. Your client will need X11 support(https://unix.stackexchange.com/questions/276168/what-is-x11-exactly), which is the protocol for viewing imagse across ssh. 
	- Note when you ssh, you will perform `ssh -Y khouryname@login.khoury.neu.edu`
4. (least recommended) Use this web interface and drag in your PPM: http://paulcuth.me.uk/netpbm-viewer/

## Description

Hooray, in lab 0 we discovered if we can properly run OpenGL 3.3 or greater on our machines. But we are going to travel back in time a bit and understand how rasterization takes place in graphics while we also build our C++ skills.

Software Renders while not optimal for real-time performance are still used for:

- Offline rendering tasks
- Debugging GPU code by emulating graphics on the CPU.
- A fallback renderer if there is no GPU hardware available.
- A great way to understand graphics programming!

For this lab, you will build the **g**reat **l**ooking software render (Note: I had to find something that had a 'gl' prefix).  Sometimes puns can be pretty rough.

## Part 1 - Setting up your Environment

For this lab, you only need run `clang++ -std=c++11 main.cpp -o main` to compile the source code from a terminal. If **clang++** is not available, you may use g++ instead (likely folks on Windows will have to do this).

In the Developer Command Prompt for Visual Studio, you can simply use `cl main.cpp` to build the .exe.

## Part 2 - Filled in Triangles

<img align="right" src="http://www.sunshine2k.de/coding/java/TriangleRasterization/generalTriangle.png" width="400px" alt="picture">

Today's lab is a bit of a thinking exercise. You and your partner will have to think about how to rasterize and fill in a triangle. Your goal is to generate a .ppm image with 3 differently colored triangles.

### Tips

1. Make sure glFillMode (from GL.h) is set to FILL when you are drawing your triangle.

## Helpful Resources

Some additional resources to help you through this lab assignment

- Reference on C++
  - http://www.cplusplus.com/
- Another nice tutorial on the C++ language.
  - https://www.learncpp.com/
- Rasterization resource 0
  - http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
- Rasterization resource 1
  - https://medium.com/@thiagoluiz.nunes/rasterization-algorithms-computer-graphics-b9c3600a7587
- Rasterization resource 2
  - http://developers-club.com/posts/257107/
- Rasterization resource 3
  - https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation
- Rasterization resource 4 (Video on Barycentric coordinates)
  - https://www.youtube.com/watch?v=HYAgJN3x4GA

## Deliverables

- Implement `void triangle(Vec2 v0, Vec2 v1, Vec2 v2,TGA& image, ColorRGB c)` and make three calls to the function so that when run a single image showing three differently filled colored triangles are displayed.

You must complete this lab by next class. You will run your lab in front of me at the start of the next lab when class starts and tell me what your group # was for that week.

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- (Wu's Algorithm https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm)
- Consider optimizing Bresenham's algorithm
  - http://www.idav.ucdavis.edu/education/GraphicsNotes/Bresenhams-Algorithm.pdf

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
