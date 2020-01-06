# Assignment 1 - Modern C++ PPM Library

*TODO*: Please edit the following information in your assignment

* Name and partners name (At most 1 partner for this assignment): 
* How many hours did it take you to complete this assignment? 
* Did you collaborate or share ideas with any other students/TAs/Professors? 
* Did you use any external resources? 
  * (tbd if any)
  * (tbd if any)
  * (tbd if any)
* (Optional) What was the most interesting part of the assignment? How would you improve this assignment?
  
## Description

C++ is the standard programming language for programming in the computer graphics, gaming, entertainment, and other industies that require high performance. While we can learn computer graphics in any general purpose language, the long term outlook for jobs appears to remain in C++ (And besides, once you learn how to work in C++, you could work in other languages as needed. We'll also see the GLSL language which is C-based). For this exercise(and all that follow), you will be using modern C++. This means C++11 and beyond (C++11 is the standard of the language in the year 2011. There are further versions C++14, C++17, C++20, etc).

For this first exercise you are going to build an image parser in C++. This project will introduce you to some common C++ libraries we will use throughout the course. It will also introduce you to how image data is stored. The **deliverables** section describes the expected output.

# C++ Introduction

Read and type out the examples below to get some practice. Understanding each of them will help you complete the final deliverable.

## Part 0 - C++ and the Standard Template Library (STL)

C++ comes with several general purpose libraries that have been built for us. This is a good thing, as it avoids us from having to do a lot of work. The Standard **Template** Library is also *templated*. This means it has been programmed in a way that it can work with many data structures. If you have used languages like Java, then you are likely familiar with the concept of a generic class. The next sections will describe parts of the Standard Template Library (STL) that will be helpful in achieving your task.

## Part 1 - Primitive data types

C++ has many different data types built in by default. Below is a table of the default data types that are provided. A more complete set is found [here](https://www.geeksforgeeks.org/c-data-types/):

<table>
  <tbody>
    <tr>
      <th>Data Type</th>
      <th>Size in Bytes</th>
      <th>Range</th>	    
    </tr>
    <tr>
      <td>long int</td>
      <td>4</td>
      <td>-2,147,483,648 to 2,147,483,647</td>	    
    </tr>
    <tr>
      <td>unsigned int</td>
      <td>4</td>
      <td>0 to 4,294,967,295</td>	    
    </tr>
    <tr>
      <td>signed char</td>
      <td>1</td>
      <td>-128 to 127</td>	    
    </tr>
    <tr>
      <td>unsigned char</td>
      <td>1</td>
      <td>0 to 255</td>	    
    </tr>
    <tr>
      <td>float</td>
      <td>4</td>
      <td>+/- 1.4023x10^-45 to 3.4028x10^+38</td>	    
    </tr>
    <tr>
      <td>double</td>
      <td>8</td>
      <td>+/- 4.9406x10^-324 to 1.7977x10^308</td>	    
    </tr>	  
  </tbody>
</table>

What is important to understand is that we need to select the appropriate data type for the information we are storing. This control means we have a greater responsibilitiy as programmers, with the tradeoff being we can really optimize our programs.

Here is a C++ example showing different data types and their sizes programmatically. We will cover input and output in the next part.

```cpp
// Compile with:
// g++ datasize.cpp -o datasize
#include <iostream>

int main(){

	// Most of the time a 'signed int' is abbreviated as simply an 'int'e.
	std::cout << "Data size of int in bytes = " << sizeof(int) << std::endl;
	// Most of the time a 'signed char' is abbreviated as simply a 'char'.	
	std::cout << "Data size of char in bytes = " << sizeof(char) << std::endl;
	
	std::cout << "Data size of float in bytes = " << sizeof(float) << std::endl;
	std::cout << "Data size of double in bytes = " << sizeof(double) << std::endl;

	return 0;
}

```

## Part 2 - Basic I/O 

To start, click on this URL (And then hit the C++11 tab): http://www.cplusplus.com/reference/iostream/. Take a moment to browse the Objects you have available. It may also be worth bookmarking that website as a reference.

<table>
  <tbody>
    <tr>
      <th>Object</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>cin</td>
      <td align="left">Handles user input</td>
    </tr>
    <tr>
      <td>cout</td>
      <td align="left">Handles output of text</td>
    </tr>
    <tr>
      <td>cerr</td>
      <td align="left">Handles output of text for error purposes</td>
    </tr>
    <tr>
      <td>clog</td>
      <td align="left">Handles output of text for logging purposes</td>
    </tr>	  
  </tbody>
</table>

Try the following example below. You will compile this from a terminal window.

```cpp
// Compile with:
// g++ io.cpp -o io
#include <iostream> // The standard input/output library

// Entry-point to our program.
int main(){

	// We output some text. Note we start with std:: because this
	// is part of the standard library namespace.
	std::cout << "Hello" << std::endl;
	std::cout << "How old are you?" << std::endl;
	
	
	// Let's use some of the primitive variable types in C++
	// to store input.
	int age;
	
	// Now we want to get c++ input (i.e. cin)
	std::cin >> age;
	
	std::cout << "That is great you are " << age << std::endl;

	return 0;
}
```

## Part 3 - Writing and Reading data from Files

Read this section to learn about file handling in C++ | [Read about this topic in anothers words here](http://www.cplusplus.com/doc/tutorial/files/)

The datasets we are going to be working with in graphics are several kilobytes to several megabytes. Files of this size are far too large to store within a source file (Many graphics datasets are even in gigabytes in domains like medical visualization). So in order for us to manipulate data within our programs, we are going to read and write modified data into files using C++'s file libraries.

Here is an example of creating a new file and writing output to it.

```cpp
// Compile with:
// g++ output.cpp -o output
#include <iostream>
#include <fstream>

int main(int argc, char** argv){


    // Opens a file to output
    std::ofstream outFile;
    // Write to a new file called 'temp.txt'
    // This overwrites a previous file, or otherwise
    // creates a new file if it does not exist.
    outFile.open("temp.txt");
    
    // We can work with files similar to how we
    // work with cout and cin.
    outFile << "# Some image data" << std::endl;
    outFile << "P3" << std::endl;

    // Closes the file we are streaming data to
    outFile.close();

    return 0;
}
```

Here is an example for writing out files.

```cpp
// Compile with:
// g++ input.cpp -o input
#include <iostream>
#include <fstream>
#include <string> // new library!

int main(int argc, char** argv){


    // Opens a file to output
    // You will notice the name is 'ifstream'
    // This means 'input file stream'
    std::ifstream inFile;

    // Now we are going to read in some data.
    // I want to actually make our program more flexible
    // and read in a file from the command line.
    // To do this, we'll use the argc, and argv**
    // arguments of our main function.
    // So when we run our program, we will type on the command-line:
    // ./input objects/bunny.obj"
    
    // Let's enforce that there needs to be one argument.
    // argc is the "argument count" parameter.
    if (argc != 2){
        std::cout << "Oops, exactly two arguments needed.\n";
        std::cout << "ProgramName file_path.\n";
        return 0;
    }
    // Now we can open our file.
    // Think about why this is argv[1].
    // Try printing it out to see what this is.
    inFile.open(argv[1]);
    
    // Lets also check to make sure the filepath is correct.
    if(inFile.is_open()){
        // Now we can do some work
        // We'll learn about strings in a moment,
        // but we are using getline to read in
        // one string of text at a time, until
        // we have nothing left to read.
        std::string line;   // A string object.
        while(getline(inFile,line)){
            std::cout << line << std::endl;
        }
    }
    
    // Closes the file we are reading from
    inFile.close();

    return 0;
}

```


## Part 4 - Working with Strings

Wonderful, we can read and write data to files! But files in graphics (and other domains) are often very structured. This means that if we want to access various parts of the file, then we might need better granularity than accessing them one line at a time.

Strings are typically implemented as character arrays, such that each index is an unsigned char, and is terminated with the null character [see character sequences](http://www.cplusplus.com/doc/tutorial/ntcs/).

<table>
  <tbody>
    <tr>
      <th>0</th>
      <th>1</th>
      <th>2</th>
      <th>3</th>
      <th>4</th>
      <th>5</th>	    
    </tr>
    <tr>
      <td>'h'</td>
      <td>'e'</td>
      <td>'l'</td>
      <td>'l'</td>
      <td>'o'</td>
      <td>'\0'</td>
    </tr>
  </tbody>
</table>

In our previous example, we saw the std::string data type. This is provided through the <string> library, which provides us a slightly more convenient way to work with textual data.
	
The [reference page](http://www.cplusplus.com/reference/string/string/) provides several handy methods for performing operations like searching strings, adding characters, and navigating them. Here is a very brief example. Use the reference to see more examples.

```cpp
// Compile with:
// g++ string.cpp -o string
#include <iostream>
#include <string>

int main(){
    // Create a string
    std::string fullName = "Mike Shah";
    // Store a portion of the string
    std::string firstName = fullName.substr(0,4);
    std::string lastName = fullName.substr(5,9);
    // Output our strings
    std::cout << "First: " << firstName << std::endl;
    std::cout << "Last: " << lastName << std::endl;

    // Iterate through our string one
    // character at a time.
    // We break if we find a space.
    // You will also note two ways
    // to access a strings individual
    // characters.
    unsigned int i =0;
    while(i < fullName.length()){
        if(fullName.at(i)==' '){
            // Terminate from our loop
            break;
        }
        std::cout << fullName[i];
        ++i;
    }


    return 0;
}
```

## Part 5 - Handy Container Data Structures - The Vector

Often we will want to store different collections of data. This is very useful in situations where we do not know how much data either during compile-time(i.e. before we are running the program). This means we need a flexible expanding data structure to store data. The <vector> header includes the std::vector which is the standard tool to do this.

Below is a brief example.

```cpp
// g++ vector.cpp -o vector
#include <iostream>
#include <vector>

int main(int argc, char** argv){

    // Create a vector which stores
    // 'unsigned char' data.
    std::vector<unsigned char> myData;
    
    // Add data into our vector.
    for(unsigned int i = 65; i < 91; ++i){
        myData.push_back(i);
    }

    // Iterate through our container structure
    // and print out the data in our vector.
    for(unsigned int i = 0; i < myData.size(); ++i){
        std::cout << myData[i];
    }

    return 0;
}
```

[See the other container data structures](http://www.cplusplus.com/reference/stl/)

## Part 6 - Object-Oriented Programming and Classes

C++ is a programming language with Object-Oriented capabilities. C++ was initially "C with classes" when Bjarne Strousoupe first added classes to the language. Classes are the primary mechanism that allows users to build their own data types. The custom data type, which is a class, is often referred to as a 'blueprint' for an 'object'.

Posted below is a simple example. I would suggest as a complete resource this 'classes' section of the tutorial: http://www.cplusplus.com/doc/tutorial/ (Read at a minimum classes(1)).

```cpp
// compile with: g++ class.cpp -o class

class PPM{
public: // Member Functions/Variables available

    // Constructor called when object
    // is first created.
    PPM(unsigned int width, unsigned int height){
        // Allocate some memory
        pixelData = new unsigned char[width*height*3];
    }
    // Destructor called when object is
    // destroyed.
    ~PPM(){
        // Reclaim our memory when we are done.
        delete[] pixelData;
    }
    
private:    // Data not visible to a user of 
            // this object.
    unsigned char* pixelData;

};


int main(){

    // Create an instance an object with 
    // a data type of 'PPM'
    PPM myPPM(64,128);

    return 0;
}
```


### Aside:

If you have programmed in C++ before, then you may also know that *structs* are another way to create custom data type. In C++, structs and classes are equivalent. The only difference is a struct by default make their members public, whereas a class makes its members private. By convention, structs are also used as [POD data types](https://en.wikipedia.org/wiki/Passive_data_structure).


## Part 7 - Final notes

With a little bit of prior programming experience and experimentation you can pick up C++. More C++ will be introduced as needed as we solve additional problems. At this point, you are starting to get a little dangerous with your new C++ knowledge!

# PPM Library

For this assignment you are going to implement a PPM library. PPM is a data format for structuring image data. You likely have used or saved images formatted as .jpg, .bmp, .png, or .gif, and now you will understand .ppm. 

## Images

<img align="right" src="./media/RGB-animation.gif" width="400px" alt="RGB Animation">

Images are made up of pixels, which are located with an x,y coordinate. That is, a 64x128 image, is 64 pixels wide, and 128 pixels high. Within each pixel (say pixel (2,100)) are three values, that specify the red, green, and blue components for that individual pixel. The higher the value from a range of 0-255, the more that color is expressed.

The PPM format looks something like this:

```
P3
# some_image.ppm (Note this is just a comment)
64 128
255
 0  0  0    0  0  0    0  0  0   125 0  125 .... 60 more triples.
 0  0  0    0 225 7    0  0  0    0  0  0   .... 60 more triples.
 0  0  0    0  0  0    0 15  7    0  0  0   .... 60 more triples.
15  0 15    0  0  0    0  0  0    0  0  0   .... 124 more rows follow.
```

1. The first line is the 'header' data of the file, which describes which specific format of PPM data you are loading.
2. The second line begins with a '#' which is merely a comment. This line should be ignored when reading in data.
3. The third line specifies the width (64 pixels) and the height(128) pixels.
4. The fourth line specifies the maximum value for an individual color value(i.e. the red, green, or blue component). So values will range from 0 to 255.
	- One thing to note here, is that if we are only storing values between 0-255, we can use an 'unsigned char' to be efficient.

### Structure of our library

You are given a include/PPM.h file which describes the interface to your class. You will implement the functionality for that class in the src/PPM.cpp file. A corresponding main.cpp file is where the program will run. 

### Deliverables

* Implement the PPM Library such that an image can be loaded, then a darker version of the image can be saved out.
	* Make sure to commit your changes to the code repository.

### Rubric

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>70% (Core)</td>
      <td align="left">Core - Does your code compile, use good programming style, etc.</td>
    </tr>
    <tr>
      <td>20% (Intermediate)</td>
      <td align="left">Does/would your darken filter work? Did you remember to reclaim allocated memory in your destructor?</td>
    </tr>
    <tr>
      <td>10% (Advanced)</td>
      <td align="left">Can you handle PPMs that have comments in them? Does your parser work with PPMs with only one value on a line, or will multiple RGB values on a line break the parser? If a PPM's max's out at a value of 15, do you scale that to 255?</td>
    </tr>
  </tbody>
</table>

* Core is the material everyone can get through. I expect everyone to complete this. Coming to class, listening to lectures, and reviewing materials should be sufficient.
* Intermediate is a little more difficult. Very likely you will have to utilize office hours, piazza, etc.
* Advanced is more challenging. You will have to spend more time and very likely use outside materials. I do not expect everyone to complete the advanced section.

## More Resources

- C++ Related
	- A Standard Tutorial: http://www.cplusplus.com/doc/
	- The ISO Standard for the language: https://isocpp.org
		- Typically the latest and greatest information will always be here.
	- Thoughts on vectors vs lists
		- https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html
- Image Library related
	- The PPM Format Specification
		- http://netpbm.sourceforge.net/doc/ppm.html

## F.A.Q

- Q: Why are some of the comments weirdly formatted in this assignment?
	- A: They are formatted such that a tool called [doxygen](http://www.doxygen.nl/) can take these comments and create a nice html help page. For future assignments where I provide support code, this is helpful to have. It is also good programming practice to document things well!

