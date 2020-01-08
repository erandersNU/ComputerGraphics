Overview
=====================================
During this class, I will provide code and the basic build scripts to get your started with labs and assignments.  In order to complete these activities, you must be able to fetch the source code from the established repository, make any necessary changes/additions, and then submit the project upon completion.  This document provides instruction on these steps.

The Build Environment
====================================
This class uses Qt 5.14.0 as our primary C++ library to handle window management, etc.  This is a fairly large library and can help with a number of things we will be doing (e.g. String manipulation and overdrawing).  Qt can be found at <a href="https://qt.io">https://qt.io</a>.  To install, click the "Download. Try. Buy." link at the top right, then go to "Go Open Source" in the lower right pane.  At the bottom of the next page is a button to "Download the Qt Online Installer" which will allow you to download the installer.  The installer is a small application that will allow you to select versions of Qt to use.  You DO NOT need to provide any user info (unless you want to) in order to install this.  Select "Latest Releases" on the side panel and then select 5.14.0 to install the latest Qt framework.

This class will also use CMake to manage our build.  CMake is a build preparation tool that takes an input (a text file called CMakeLists.txt) and produces various types of build scripts -- ranging from Visual Studio .sln files all the way to Unix Makefiles.  Download and install CMake at: <a href="https://github.com/Kitware/CMake/releases/download/v3.16.2/cmake-3.16.2-win64-x64.msi">http://www.cmake.org/download/</a> and select the appropriate platform.  I recomment using the binary releases (.msi/.dmg/.sh) rather than building this from source.

This class will primarily be building code in C++.  For this, you need a C++ compiler.  All of the tools in this class are meant to be cross-platform, but I do have some recommendations (for ease of setup and use).  

Windows:  Visual Studio
<br>
Mac:  clang
<br>
Linux:  gcc

Please note that Visual Studio Code does NOT come with a C++ compiler, it is only an IDE.

Fetching Source
==================================
I will be posting assignments and labs to a github repository prior to class each week.  To best interact with the repository, I recommend forking the repository.  Forking will make a copy of the remote repository so that you do not need to worry about affecting the remote master copy.  For submission, simply send me a link to your repository -- I will fetch it and build on my machine to determine your grade.  For a detailed discussion on forking git repositories, please see <a href="https://help.github.com/en/github/getting-started-with-github/fork-a-repo">this article.</a>

When dealing with multiple build environments, things happen.  I will make every attempt to build your code in my environment, but sometimes things may not go smoothly.  In this event, I will contact you and set up a time for you to sit down with me to go over your executable on your machine if necessary.

Using CMake
====================================
Once you have your general environment installed and the lab/assignment fetched, you are ready to create your build scripts.  To do this, run CMake.  For the GUI users, when CMake opens, it will be empty.  You will need to define 2 directories for it to work properly.  The source directory is the location that contains the CMakeList.txt file relevant for the project you are working on.  The build directory is when CMake will output the various scripts that it generates.  (I recommend creating a "build" folder inside the source directory and pointing it here).  Then, hit the "Configure" button.  It will likely fail as it will need to be pointed to the Qt installation.  There are 2 options to solve this problem.  You may click on the line where it indicates that QT5_DIR_NOT_FOUND and navigate to <QtDir>/5.14.0/<your_compiler>/lib/cmake/Qt5  OR you may create an environment variable called CMAKE_PREFIX_PATH so that it need not give this error each time.

For commandline users, the process is quite similar.  First navigate to the directory you would like to create the build scripts in.  Then, run cmake as follows:  cmake <path_to_source_dir> -DCMAKE_PREFIX_PATH=<QtDir>5.14.0/<your_compiler>/lib/Qt5

Commandline users may also modify their environment variables to add CMAKE_PREFIX_PATH there and not have to worry about this step each time.

Building the CMake Outputs
====================================
After running CMake, you will have all the scripts/files necessary to build your project in the directory you identified.  For those of you using make, simply navigate to this directory and run make.  For Visual Studio users, CMake produces a .sln file that you should load.  Please note, that it creates 3 different projects -- only one of them will actually create an executable.  To build and run this, you must first set the appropriate project as the active project.  Right click on the project and click on "Set as Active Project."  This will tell Visual Studio that the executable generated here should be the one to run.  Now, you are ready to hit the small green triangle (or hit F5) and Build and Run your code.

Submission
====================================
When you are ready to submit your project, push your forked repo to your own git repository and send me a link via e-mail.  Once I am able to get Blackboard to recognize assignments (I am currently working on this), submissions will proceed through Blackboard.  This will allow me to fetch your code and build it locally myself.  If, for some reason, I cannot build your code, I will contact you and set up a time to meet and get the issues fixed up.
