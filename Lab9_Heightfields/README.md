# Lab 10 - Terrain

<img align="right" src="./media/terrain.JPG" width="400px" alt="picture">

> "Land ahead!"

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

Last lab we created a multiple point lights to create atmosphere.

- We learned about using structs and arrays in our shader code.
- We learned about attenuation (i.e. the reduction of light over a distance) with the point light. 

Today we are going to create a more 'breathtaking' scene by adding terrain using a colormap and a heightmap.

## Part 1 - C++/glsl Refresh - Inheritance and Shader Review

### Task 1 - Inheritance in C++

Today we are introducing the 'TerrainQuad class' which inherits from our 'Renderable' class. The code below means that our TerrainQuad class inherits all of the public members of Object. When we create a TerrainQuad, both the TerrainQuad and Renderable constructor will be called. Take a moment to see what the TerrainQuad Class adds.

### Task 2 - Review of buffers

Take a moment to look at this snippet of code representing a vertex shader(vert.glsl). See all of the `glEnableVertexAttribArray` and `glVertexAttribPointer`'s.

```c
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec3 normals; // Our second attribute - normals.
layout(location=2)in vec2 texCoord; // Our third attribute - texture coordinates.
layout(location=3)in vec3 tangents; // Our third attribute - texture coordinates.
layout(location=4)in vec3 bitangents; // Our third attribute - texture coordinates.
```

Note how the corresponding layout matches exactly that from our vertex buffer object.

```cpp
        // Vertex Buffer Object (VBO)
        // Create a buffer (note we’ll see this pattern of code often in OpenGL)
        // TODO: Read this and understand what is going on
        glGenBuffers(1, &m_vertexPositionBuffer); // selecting the buffer is
                                                // done by binding in OpenGL
                                                // We tell OpenGL then how we want to 
                                                // use our selected(or binded)
                                                //  buffer with the arguments passed 
                                                // into the function.
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        // Finally pass in our vertex data
        glVertexAttribPointer(  0,   // Attribute 0, which will match layout in shader
                                3,   // size (Number of components (2=x,y)  (3=x,y,z), etc.)
                                GL_FLOAT, // Type of data
                                GL_FALSE, // Is the data normalized
                                sizeof(float)*m_stride, // Stride - Amount of bytes between each vertex.
                                                // If we only have vertex data, then
                                                // this is sizeof(float)*3 (or as a
                                                // shortcut 0).
                                                // That means our vertices(or whatever data) 
                                                // is tightly packed, one after the other.
                                                // If we add in vertex color information(3 more floats), 
                                                // then this becomes 6, as we
                                                // move 6*sizeof(float)
                                                // to get to the next chunk of data.
                                                // If we have normals, then we
                                                // need to jump 3*sizeof(GL_FLOAT)
                                                // bytes to get to our next vertex.
                                0               // Pointer to the starting point of our
                                                // data. If we are just grabbing vertices, 
                                                // this is 0. But if we have
                                                // some other attribute,
                                                // (stored in the same data structure),
                                                // this may vary if the very
                                                // first element is some different attribute.
                                                // If we had some data after
                                                // (say normals), then we 
                                                // would have an offset of 
                                                // 3*sizeof(GL_FLOAT) for example
        );

        // Add three floats for normal coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*3));

        // Add two floats for texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*6));

        // Add three floats for tangent coordinates
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*8));

        // Add three floats for bi-tangent coordinates
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*11));
```

## Part 2 - Heightmaps

Today the trick is to use 'height data' from an image file to set the y value of our triangle strip. Within the TerrainQuad::init function, you will see all of the data initialized.

As with most things in graphics, there are multiple ways to solve this problem.  The first makes use of C++ to get the job done.  It will first read in the heightmap data and then determine
the appropriate y coordinate by querying the pixel data in a QImage object.  This is a fine way of doing things, particularly if the geometry (heights) will never be changing.  The y coordinate
would be defined as something like:

```cpp
float y = (float)heightMap.getPixelR(z,x)/scale;
```

We must scale here because the pixel range will likely be 0-255 -- a much larger range than we might want!

We can also do things by using multiple textures!  This is the method we are implementing in this lab.  As a "default" implementation, you should be able to texture the TerrainQuad trivially
with either the height data OR the color data.  As usual, this works by using a sampler2D in the fragment shader and paying attention to the texture coordinates to extract the relevant
color (or greyscale) data.  When we move towards implementing heightmaps in the GPU, a few changes must be made.

1:  The quad that we want to manipulate must be more than just 2 triangles -- heights will only get assigned per vertex, so we need a much denser sampling of our xz plane.

2:  We want to more efficiently render our densely sampled quad.  This means we want to use Triangle Strips.  There are multiple ways to "stripify" our data, this lab we are choosing a relatively
easy way to do this.  TODO - Read and understand TerrainQuad::init(..)

3:  We need to access multiple textures -- a heightmap texture in our vertex shader and a colormap texture in our fragment shader.  This requires a little bit of extra scaffolding to ensure that
the correct sampler is reading the correct texture!

4:  We need to set up access to multiple textures in the host (.cpp files).  TODO -- Read and understand the use of glActiveTexture(..) in TerrainQuad::draw(..)

5:  We need to draw our Triangle Strip data!  TODO -- Implement the appropriate draw call in TerrainQuad::draw(..)

```

## Helpful Resources

- [SDL API Wiki](https://wiki.libsdl.org/CategoryAPI)
- [docs.gl](http://docs.gl/) useful programming resource
- Start writing some OpenGL 3.3 from here! [learnopengl.com](https://learnopengl.com/) Use this time for graphics!
- Working with height fields (i.e. heightmaps) https://courses.cs.washington.edu/courses/csep557/06au/projects/modeler/heightfield.html
- Notes on triangle strips: http://www.learnopengles.com/tag/triangle-strips/

## Deliverables

1. Create a heightmapped terrain!
2. (Not graded) Review the support code and understand how inheritance works.

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Integrate your previous lab into this project.
- Integrate a 'mouselook' into this lab from y our previous codebase.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
