# Assignment 6
  
## Description

Due to COVID-19 effects, we have had to modify the cirriculum a bit.
The two assignments here represent the last assignments in the class,
and arguably some of the most important ones.  To accommodate the
different interests students have and still provide adequate
assignments has been a challenge.  Instead of having a single final
project that can incorporate various aspects of computer graphics
principles learned through the term, I have decided to allow you to
choose 1 of the 2 assignments posted here.

Please choose and complete 1 of the 2 assignments below for full
credit.  Extra credit will be given for full or partial implementation
of the second assignment.

### Assignment 1 - Scene Graph

The Scene Graph is a key tool in computer graphics.  It is
simultaneously an optimization strategy, an organizational construct,
and an enabling technology to provide dynamic change in a scene.  In
this assignment, you will implement a Scene Graph and apply it to a
view of the Solar System.  The result of this assignment will be an
animated scene with the sun and several planets (complete with moons)
orbiting it.  You will utilize the Scene Graph to organize each
transformation (rotation about the sun, rotation about the planet,
rotation about the planet's axis) to show a dynamic scene with
textured spheres as planets.

### Assignment 2 - Particle System

A Particle System is a class of graphics effects that make use of
physical simulation, instancing, and lighting to create an effect or
interaction method.  This assignment will make use of your OBJ Readers
to read in a model that will be used as a particle.  A particle
emitter will be placed at the origin (pointing up along the y axis)
and instances of the model will be created, scaled, and then
positioned according to gravity.  Since we will only ever have a
single set of geometry loaded into memory (either CPU or GPU), this
will test your implementation of instancing and show how a single
model may be drawn differently many times without much additional
overhead.

