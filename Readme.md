# Image Processing
- This is a project to learn about image processing and how to do it.
- Also to use SOLID principles to make a good program.
- The project uses NO EXTERNAL Libraries. to import. 

## CPPImageCompression SDK

The CPPImageCompression SDK provides a simple and easy-to-use interface for compressing images. The SDK currently supports two compression algorithms:

* NaiveBlur
  * simple averagined 
* NaiveBlurThreaded
  * just threaded it for it to perform a little faster
* FastGaussianBlur
  * Currenly not performing as nessary was based on a java implimentation that was not working as expected.
  * will be fixed in the future.
  * https://blog.ivank.net/fastest-gaussian-blur.html


To use the SDK, you first need to create a new `Args` object. The `Args` object stores the command line arguments that are used to configure the compression algorithm.

```c++
Args args(argc, argv);
```


Once you have created an `Args` object, you can call the `getAlgo()` function to get the current compression algorithm.

```c++
ESupportedImageBlurringAlgos algo = args.getAlgo();
```


## TGA format Specifications 
- https://www.fileformat.info/format/tga/egff.htm

### C style crude read write.

http://www.paulbourke.net/dataformats/tga/tgatest.c

- a bit difficult for me to understand but it gives me the type struct and also 
- this gives me what might be nessary to read and write here. 
- Memory layout specifications also found here. http://www.paulbourke.net/dataformats/tga/
- https://www.conholdate.app/viewer/view/rVqTeZPLAL/tga-file-format-specifications.pdf?default=view&preview= This was more helpful for the specifications 

# Bluring
- Leart about convolution in my AI class will use the conspets from there and work on it 
- here will be my first attept without the randome wights that will be sample an average.

# Convolution
convolution is a way to apply a filter to an image. the idea is to take and convolute a function over data. 


# Future goals with this project.
- Addition of some libraries like Catch for testing.
- Threaded file reading and writing.
- More image processing functions.
- More file formats.
- writing a generaic threaded for loop (if possible).

# Instructions to use the project. 
- Clone the project.
- compile the CMakeLists.txt file.
- run the program with the following command.

this is on the mac/ unix 
you can also use source 
```git
./CppImageCompression -s <source> -d <destination> -b <blurFactor> -a <algorithm>
```
- Supported Argumetnts 
- ```-s <input file> ``` : the file to read from.
- ```-o <output file> ``` : the file to write to.
- ```-b <Blur Level 0-1> ``` : amount of blur. 
- ```-a <type of blur algorythm> ``` : the type of blur to use.
- ```--help ``` : help menu.

## Check out the Wiki for more indepth information about the project.
like 
- ImageData Class Diagram https://github.com/jaibeer72/CppImageCompression/wiki/ImageData-Class-Design