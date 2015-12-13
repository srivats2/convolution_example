1. This is a sample program that does convolution image filtering on 2D data. Implement Image2D class as a subclass of ImageBase class, and ImageFilterBase class that is an abstract class of ImageConvolutionFilter class to make main() function in main.cpp work as it is.
>>Done!
>>Added CImg display just to check if everything is OK.
>>CImg display is optional as not all setups would have X11...Please do comment out the lines with display() in case you do have X11 and wish to show the output

2. Create a subclass of ImageConvolutionFilter class to implement any one of the convolution filter (sobel/laplacian/mean/gaussian/other).
>>Created a subclass called GaussianFilterConvolution which will be a generic gaussian implementation
>>One can specify the sigma with the help of the constructor and it generates the filter (I have considered a 6*sigma as the actual gaussian)
>>I have added to main such that both the implementations are called (i.e. given and the gaussianfilterconvolution)
>>The constructor builds the 2D matrix filter using the new filter coefficients.

3. Implement (2) in multi-threading 
>> Have done this using OpenMP which is why I made is a requirement in the CMake setup itself. 
>> The function "perform_new_convolution" calls perform_new_filtering which is the 2D convolution but multithreaded using OpenMP.
>> In order to see if multithreading actually makes any difference I chose a larger image where the difference would be more obvious.
>> Below is the simple time test between using 1 thread and 4 threads and is pretty significant (9 seconds).
>> Tested on a dual core i5 - 4 threads. 

~/c/c/b/linux ❯❯❯ time ./convolution_test                                                                                                                                                                        ⏎
./convolution_test  60.84s user 0.03s system 372% cpu 16.345 total
~/c/c/b/linux ❯❯❯ time ./convolution_test
./convolution_test  25.38s user 0.03s system 99% cpu 25.427 total


4. Add modifications to the whole program. You can add functions, re-arrange the classes, and anything to make the codes better. Use your creativity and everything you know about C++. You are free to use external libraries too.
Thanks. I have used the CImg library which is header-only and OpenMP as far as libraries go. Also, one would need the JPEG library to run the large image convolution as it is a JPEG image under the 'data' folder. 
I have also written routines to which can copy data from the ImageBase* -> cimg_library::CImg<> and vice-versa which is why I was able to use the data members that were already defined


Also, please do excuse my variable names. I usually would have much clearer names so that it is easy for the reader. On the same lines I would usually have detailed comments which given my current time restrictions is not possible.

I always use CMake for all my projects and that is what I have done here. All the necessary setup will be done automatically once one runs CMake.

I am running Arch Linux(4.2.5-1) with GCC 5.3.0 and it compiles just fine (no warnings).
Also tested using GCC 4.7.4 (no warnings, similar performance for OpenMP).


