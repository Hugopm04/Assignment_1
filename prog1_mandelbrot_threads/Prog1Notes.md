**Program 1 Notes**

***Task 1***

For the first task I started by coming up with how I could separate the work for the threads, and did that by splitting the task up by dividing the amount of rows by the amount of threads. I then assigned the rows and the starting rows to the threads but initially forgot to actually use it in the mandelbrot serial function so it did nothing. But after getting it to work I tested it with two threads and got a 1.99x speedup, which was expected, but then when I tried with 3 threads I only got a 1.64x speedup, which was less than with two threads. 
I wondered if I had done something wrong but when testing with 4 threads it was a 2.45x speedup, so it seemed to be working. 

After thinking for a while I figured that it was due to the division giving a way harder to process part to one of the threads and thus slowing down the process.

***Task 2***


