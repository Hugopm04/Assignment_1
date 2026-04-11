**Program 1 Notes**

***Task 1***

For the first task I started by coming up with how I could separate the work for the threads, and did that by splitting the task up by dividing the amount of rows by the amount of threads. I then assigned the rows and the starting rows to the threads but initially forgot to actually use it in the mandelbrot serial function so it did nothing. But after getting it to work I tested it with two threads and got a 1.99x speedup, which was expected, but then when I tried with 3 threads I only got a 1.64x speedup, which was less than with two threads. 
I wondered if I had done something wrong but when testing with 4 threads it was a 2.45x speedup, so it seemed to be working. 

After thinking for a while I figured that it was due to the division giving a way harder to process part to one of the threads and thus slowing down the process.

***Task 2***

The code that I made for task 1 should work for task 2 as well as long as one specifies the amount of threads in the run command with the flag -t. My processor has 32 threads, so I did not run it with each number between 1 and 32 but enough to make a solid graph. 

![img.png](img.png)
This is the graph that was created and from it one can see that the speedup is not linear, but has some bumps on the way depending on the amount of threads. The significant ones are 3, 16 and 24.

The amount of threads seems to however lead to an increase in performance in every scenario except for 3 threads. My best explanation for this phenomenon is that the sections are not evenly difficult to process. I say this due to how the picture looks, some rows are nearly fully black while other rows are mostly white, and since the brightness of each pixel is proportiojnal to the computational cost, this means that the mostly white rows will take way longer than the nearly black ones. When the picture is divided in certain numbers of threads some threads will get a way whiter row than others, and in these scenarios the other threads will have to wait for that one complex one. Thus, I also expect the three thread scenario to be so slow due to the second thread getting the center of the picture. When that happens in gets nearly all the difficult pixels, while they were split evenly in the two thread scenario. 

**Task 3**

I added the timer to the program and to test my theory I ran it withe 2 and 3 threads. I didn't include the \n first which made the output near impossible to read, but once it was added the print proved my point.

***./mandelbrot -t 2***                                                                                  

Thread 0: time = 116.592 ms
Thread 1: time = 117.116 ms

Thread 0: time = 115.638 ms
Thread 1: time = 115.977 ms

Thread 0: time = 115.302 ms
Thread 1: time = 116.068 ms

Thread 0: time = 116.094 ms
Thread 1: time = 116.856 ms

Thread 0: time = 116.171 ms
Thread 1: time = 116.167 ms

***./mandelbrot -t 3***

Thread 2: time = 45.643 ms
Thread 0: time = 46.040 ms
Thread 1: time = 142.608 ms

Thread 2: time = 45.296 ms
Thread 0: time = 45.387 ms
Thread 1: time = 141.417 ms

Thread 0: time = 45.288 ms
Thread 2: time = 45.428 ms
Thread 1: time = 141.171 ms

Thread 0: time = 45.908 ms
Thread 2: time = 45.977 ms
Thread 1: time = 140.801 ms

Thread 2: time = 46.110 ms
Thread 0: time = 46.525 ms
Thread 1: time = 144.131 ms

As seen in the output, thread 1 in the three thread version gets the majority of the workload, and because of that it is around three times slower than the other two threads. As also seen when compared to the version with two threads, it is around 25-30ms slower than each of the threads in the two thread version. That explains why the three thread process is slower than the two thread one. 

**Task 4**

To improve the speed I first tried to figure out the smartest way, but got stuck on an idea of either splitting up the hardest central part of the picture or to try and detect the whitest areas. The second idea came after I realized that the first would not work for the view 2 series. But since there was a hint about a possible solution that was fairly simple and straight forward I forgot both of those ideas. 

My following idea came from the first one, but instead, what if I could just make sure that each thread got parts from all over the picture instead of just a bunch of rows that are after one another. So my idea was to just make the threads process every other row, or actually every n:th row, where n is the number of threads. And this idea seemed to work, since with a number of 8 threads I got a 7.37x speedup on the view 2, and a 7.24x speedup on view 1. This compared to the 4.1x speedup with the previous method is very significant. The prints for the threads are also way more balanced now, which explains the speedup.

**Task 5**

I changed the MAX limit to 64 and tried running it with 32 and 64 on both views, but as I expected it did not affect the speedup in any significant way. View 1 got a 14.44x with 32 threads, and a 14.76x one with 64, while view 2 got 12.96x with 32 threads, and 12.99x with 64 threads. I expected this since the amount of software threads only adds to the scheduling queue, but does not actually process it any faster. 