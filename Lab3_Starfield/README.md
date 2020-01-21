# Lab 3 - 3D starfield Screensaver (Applied Software Rasterization)

<img align="right" src="./media/stars.png" width="300px" alt="picture">


> Building your first screensaver--the classic starfield!

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

You will be working with some starter code provided. You will be working in the 'Stars.cpp' file for this assignment.

## Description

I have always been a fan of 'screen savers' and the creativity programmers put into designing them. A star field is a classic graphics example of a cheap screensaver effect that can be run on all sorts of computer systems. These computer systems need not have any graphics hardware either--we are now going to move our software rasterization to be run in real-time to create a screensaver with an impressive effect!

## Part 1 - Software Rendering with Qt [Reading - 10 minutes]

We are going to now use Qt to handle are drawing for us. While it was nice to have our PPM images (and we will need PPM later on for textures), really the only tool we actually need is the ability to plot a pixel on the screen.

Qt provides the class QImage, which allows us to draw directly into a
buffer of pixels.  We can then use the Qt native painting to render
our image to the screen.  Thus, every drawing operation we do in this
way is done to a backbuffer (image) that is not 'visible' to the
user. When we are ready to draw, we then flip the backbuffer to become
the frontbuffer, thus presenting the contents of the buffer to the
screen. The strategy of using multiple buffers (in this case, double
buffering) is described further
[here](https://wiki.osdev.org/Double_Buffering).

### Drawing Pixels or "stars" (StarList.h/.cpp)

For this lab, you are going to be drawing pixels directly to a QImage backbuffer. The backbuffer is a collection of raw pixels (i.e. RGBA values) that are displayed to the Qt Widget Renderer each frame.

In order to plot a pixel, Qt has provided a function to do so.

```cpp
image.setPixelColor(x, y, color);
```

This function will directly set the color of a specific pixel on the image that has been created. Each time a frame is rendered, the renderer (BasicWidget::paintEvent(..)) asks for a new frame to render.  This method of animation "uncaps" the frames per second that might be rendered.  This is important to realize because things can go too fast or too slow depending on how long a given machine might take to render a frame!


### Colors 

Each Star (defined as a struct in StarList.h) is able to have its own color defaulting to white. You are welcome to add more colors as you like or change them, though you only need two for the purpose of this assignment: White (for the stars) and Black (for the background).

Note: There are many different ways to define different color formats (R5G6B5, BGR, ARGB, etc.). The pixel type for our QImage is RGB888 - This tells the image (and renderer) that we are storing 3 values per pixel, ordered Red -> Green -> Blue.  Each value is stored as an 8-bit value, for a 24 bit word. 

## Part 2 - Perspective [Reading 10 minutes]

I have provided a slide deck here describing the probably of getting perspective: https://docs.google.com/presentation/d/1d8y7SskGl7C_vble2IX5a3YXM1pckKMku6XIESm8W98/edit?usp=sharing

## Part 3 - The Starfield [Modifying StarList.cpp]

**Your Task** is to modify the `UpdateAndRender()` function in Stars.cpp

There are **exactly** two lines that you need to modify.

## More Resources

Some additional resources to help you through this lab assignment

- [Lazy Foo SDL Tutorials](http://lazyfoo.net/tutorials/SDL/)
	  - This is the page where I learned how to setup SDL. Part of this lab is inspired by this websites tutorial.
- [learncpp.com](https://www.learncpp.com/)
	  - Handy page for learning C++
- [cpluscplus.com](http://www.cplusplus.com/)
	  - Another handy page for learning C++. I particularly like the references as well, which show how to use much of the standard library.

## Assignment Strategy

My suggested strategy for this lab is:

- First make sure you have white pixels (i.e. stars) that show up on the screen.
- Second, make sure you are comfortable navigating C++. This time there are multiple .cpp and .h files, though you should only have to make changes in Stars.cpp.
	- If there are unfamiliar C++ concepts, take some time to research them.
- Finally complete the star field.


## How to run your program

Your solution should build using the CMakeLists.txt file.  First, run CMake, then use the CMake output (Makefile, .sln, etc) to build and run the executable.

## Deliverables

- Run CMake and execute the **lab** executable to show a moving starfield in 3D with a field of view of 70 degrees.
 
## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Try making the stars spiral using the sin and cos function to make a vortex.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)

## F.A.Q

- Q: None so far!
	- A: Hurray! https://www.scratchapixel.com/ (Volume1) is probably a helpful resource.