# Optimization
This file uses **dlib** library to optimize. 

## How to build using CMake
1. Download **cmake** from https://cmake.org/download/ 
2. If you have cmake version older than 3.14 or you already have the entire **/dlib** library downloaded locally:
    1. Move **/dlib** to same directory as **test.cpp**
3. If you have a cmake version newer than 3.14 and/or don’t want to download the entire **/dlib** library:
    1. Uncomment **lines 12-17** in **CMakeLists.txt**
    2. Comment **line 9** in **CMakeLists.txt**
4. In the **CMakeLists.txt** file
    1. Change **line 6**: project(**<project\_name>**)
    2. Change **line 25**: add_executable(**<executable\_name> <filepath>**)
    3. Change **line 28**: target\_link_libraries(**<executable\_name>** dlib::dlib)
5. Open up a terminal and navigate to the directory containing your cpp file
6. Execute the following commands  
  **mkdir build**  
**cd build**  
 **cmake ..**
  **cmake —build . —config Release**  
    
7. To run file
    1. **./<executable_name>** 

What's nice is that once you build **dlib**, you should only have to build it once! After that, re-run the 4th command to compile and link your cpp file.    


### References
**Dlib:** http://dlib.net/  
**Dlib and CMake:** http://dlib.net/compile.html                https://github.com/davisking/dlib/blob/master/examples/CMakeLists.txt  
**CMake:** https://cmake.org/  
**FFT:** https://www.drdobbs.com/cpp/a-simple-and-efficient-fft-implementatio/199500857?pgno=3

### Help/Contact
vehling@usc.edu
