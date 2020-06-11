# CGTea
A mini-version of GTea written in C++ in which the view is based on wxWidget.
The library part (Model) and the controllers need still a lot of improvements.
For now, I am implementing the algorithms, reports, actions, ... based on the Java code.

There are three main dependencies:
- The Eigen library should be copied in the main directory.
- wxWidget is also needed for the graphic-user interface. However, the library parts can be used without this library.
- The boost library should be installed: 
     ```
     $ sudo apt-get install build-essentials libboost-all-dev libmetis-dev metis
     ```
