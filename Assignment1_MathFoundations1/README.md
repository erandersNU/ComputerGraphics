# Assignment 2 - Math Foundations Library (Vector and Matrix)

<img align="right" width="300px" src="http://gamedevelopertips.com/wp-content/uploads/2017/11/image13-570x500.png">

> A linear algebra framework for graphics

*TODO*: Please edit the following information in your assignment

* Name and partners name (At most 1 partner for this assignment): 
* How many hours did it take you to complete this assignment? 
* Did you collaborate or share ideas with any other students/TAs/Professors? 
* Did you use any external resources? 
  * (tbd if any)
  * (tbd if any)
  * (tbd if any)
* (Optional) What was the most interesting part of the assignment? How would you improve this assignment?

## Logistics

You will be working on your laptop to implement part of a C++ math library with two structures Vector4f and Matrix4f.

# Description

Building a custom math library is something I believe every graphics program should go through at least one time. At the very least, it is a good way to learn some more modern C++. Math libraries also make programmers think about optimization. For this assignment, we are going to start building out our math library, and we will add to it as we need to for our software rasterizer.

# Part 1 - Designing a Custom Math Library in C++

Included in our repository is the [OpenGL Mathematics library (GLM)](https://glm.g-truc.net/0.9.9/index.html). It has been well tested and is designed for C++. So why build our own C++ Math Library? Here is why:

1. Consistency
   - We can name our API as we need. Refactoring an open source library would take quite a bit of time.
2. Performance
   - By building the library ourselves, we can optimize as we need for the architecture we are developing on. We have the flexibility to implement a better algorithm for matrix multiply for example in the future.
     - Pragmatically will our library be as fast as something like GLM? For performance it might be close, likely for compile-time it will be faster because it is smaller (as we will omit features we do not need).
3. Features
   - We have complete control over the features we implement. We control the destiny of this library.
4. Portability
   - We have the source, so any platform that supports C++ can use this library.
5. Education
   - As mentioned before, doing this once is good for the programmers soul.

### Further discussion

Further discussion by Sean Middleditch on developing [Custom Math Libraries](https://www.youtube.com/watch?v=v4Ubu7BMXXk)

# Part 2 - C++ operators

In order make our math library easy to use, we are going to overload several operators for doing various vector and matrix operations. An example is provided below to show how to create a Vector2D and overload the add operator.

```cpp
// Compile with: g++ -std=c++11 operator.cpp -o operator
#include <iostream>

// Small example of C++ templates
struct Vector2D{
    // Member variables
    float x,y;
	
    // Constructor
    Vector2D(float _x, float _y):x(_x),y(_y){
    }    

};

// Here is an example of overloading the '+' operator.
// '+' itself is just a function--it may be helpful to think
// '+' as just a one character function name in this case.
// The 'const' property means we are not modifying a or b.
// Each of a and b are also passed by reference to avoid an
// additional copy.
Vector2D operator +(const Vector2D& a, const Vector2D& b){
    Vector2D result(0,0);
    
    result.x = a.x + b.x;    
    result.y = a.y + b.y;    

    return result;
}

int main(){

    Vector2D vec1(1,1);    
    Vector2D vec2(77,66);    
    // A new vector is returned as a result of '+' operations
    // and assigned to 'test'
    Vector2D test = vec1 + vec2;

    // Validate the results of our test operation.
    std::cout << "test is (" << test.x << "," << test.y << ")" << std::endl;

    return 0;
}
```

For another useful introduction see [functions 2](http://www.cplusplus.com/doc/tutorial/functions2/) and [Classes 2](http://www.cplusplus.com/doc/tutorial/templates/) which covers operators on the [cplusplus tutorial](http://www.cplusplus.com/doc/tutorial/).

### C++ Style Note

Generally for well-defined mathematical data structures like vector and matrix, it is a fine practice to overload the operators ([],+,-,/,-=,+=,etc.).

# Part 3 - Implementing Vector4f.h and Matrix4f.h

From the code repository, you will see the function prototypes for the library. Understanding the fundamentals of math is important for computer graphics, and the exercise of building a library will help you practice your C++. The good news is that one good math library really only needs to be written once (Unless math changes...in which case we have bigger problems!). On occassion we will be adding functions as needed throughout the semester to the math library.

## The Task

Implement the functions with 'TODO' in Vector4f.h and Matrix4f.

### Requirements

1. The one requirement is that there are NO loops in your code.

## Questions to ponder (Not graded)

The following are a list of questions about the design of our library. 

1. In C++ what are two instances where you would use the keyword const?
2. What does 'inline' do? Why might a programmer use it?
3. Why do you think our library is implemented as a header only library? 
	- (Sometimes you will see this, and you may research [.inl files](https://stackoverflow.com/questions/1208028/significance-of-a-inl-file-in-c) in C++)
4. Would it be helpful to implement the '<<' operator? What might you use this for?
5. For the floating-point data type, could it be dangerous to overload '=='?
	- How might you mitigate this? [reference](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/)
6. I have not provided any requirements on error checking. In general this is to maximize performance. However, what might you add to the library in a 'debug' version, or perhaps a safer version of the library?
	- See [Exceptions](http://www.cplusplus.com/doc/tutorial/exceptions/),[std::out_of_range](https://en.cppreference.com/w/cpp/error/out_of_range)

You may add your notes here:

1. *answer to number 1*
2. *answer to number 2*
3. *answer to number 3*
4. *answer to number 4*
5. *answer to number 5*
6. *answer to number 6*

# Part 4 - Testing Vector4f.h and Matrix4f.h

A unit test is a standalone test that checks for the correctness of a specific use case in your code. In our case, we are testing if we have a working math library implementation. 

```cpp
// Create a 1-vector
bool unitTest1(){
  Vector4f a(1.0f,1.0f,1.0f,1.0f);
  
  if(a.x == 1.0f && a.y == 1.0f && a.z == 1.0f && a.w==1){
    return true;
  }
    return false;
}
```

I have provided 2 unit tests as samples in main.cpp that you may use to check if the math works. You may write additional unit tests like the above to validate your work. I will be testing your library against the GLM library to ensure it works. A sample of the [GLM library documentation](https://glm.g-truc.net/0.9.2/api/a00001.html) is provided here which will be helpful for building more tests.

### Compiling and running the support code

Use the CMake configuration and build process discussed in previous assignments/labs/class.

## Deliverables

- Implement Vector4f.h and Matrix4f.h
 
### Rubric

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>70% (Core)</td>
	    <td align="left"><ul><li>Does your code compile, use good programming style, etc.</li></ul></td>
    </tr>
    <tr>
      <td>30% (Intermediate)</td>
	    <td align="left"><ul><li>Do you pass all of the unit tests?</li></ul></td>
    </tr>
    <tr>
      <td>5% Bonus (Advanced)(Optional)</td>
      <td align="left"><ul><li>Did you successfully use parallelism (threads, SIMD, etc) to speed up your library for Matrix4f?</li></ul></td>
    </tr>
  </tbody>
</table>

* Core is the material everyone can get through. I expect everyone to complete this. Coming to class, listening to lectures, and reviewing materials should be sufficient.
* Intermediate is a little more difficult. Very likely you will have to utilize office hours, piazza, etc.
* Advanced is more challenging. You will have to spend more time and very likely use outside materials. I do not expect everyone to complete the advanced section.

## More Resources

Some additional resources to help you through this assignment.

- Math Related
	1. [Handy Course on Vector and Matrix Math](http://chortle.ccsu.edu/vectorlessons/vectorIndex.html#10)
	2. [Dot Product better explained](https://betterexplained.com/articles/vector-calculus-understanding-the-dot-product/)

## Going Further

What is that, you finished Early? Did you enjoy this assignment? Here are some (optional) ways to further this assignment.

- Implement the functions with the SIMD AVX Intrinsics (either AVX, AVX2, or AVX512).
- Implement more functions you think may be of use!
	- We will eventually implement the transformations.
- Implement Vector2f, Vector3f, and Matrix2f, and Matrix3f.  Consider using templates for this!
- Consider changing all of your classes and structures into templates.
  - [C++ Templates Tutorial](http://www.cplusplus.com/doc/oldtutorial/templates/)
  - For this course, we will however only need floating point precision for most of our work.

### Template code example

```cpp
// compile: clang++ -std=c++11 Vector2DTemplate.cpp -o example
// run: ./example
#include <iostream>

// Small example of C++ templates
template <class T>
struct Vector2D{
    T x,y;
	
    // Note that default gives us the compiler generated
    // constructor.
    // If we wanted to forbid this, we could use 'delete'
    // and force users to have to use our other constructor.
    Vector2D() = default;

	// Constructor for our 2D vector.
    Vector2D(T _x, T _y):x(_x),y(_y){
    }

};

int main(){

    // Notice here we 'instantiate' the type within the <>'s
    // This creates a Vector2D with the specified type 'T'.
    // The caveat is that our member functions should all work with
    // any given type.
    // If they do not--then you may have to explore template specialization
    // See: http://www.gotw.ca/gotw/049.htm
    // e.g. What would it mean to compute the dot product of two strings?
    // You might have a specialization that handles that(if it makes sense)
    // or otherwise rule that operation out.
    Vector2D<int> myVecInt(1,2);
    Vector2D<bool> myVecBool(true,false);

    return 0;
}
```

## F.A.Q

- Q: Why are we not supporting operation X?
	- A: Add it! We will add as needed.
- Q: Can I add more tests?
	- A: Yes.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
