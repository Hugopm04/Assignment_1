**First Question**

/*
Default output
[sqrt serial]:          [691.818] ms
[sqrt ispc]:            [138.840] ms
[sqrt task ispc]:       [12.267] ms
                                (4.98x speedup from ISPC)
                                (56.40x speedup from task ISPC)
*/
The speedup due to SIMD is of x4.98 while the one for SIMD with multicore is 56.4, concluding that the multicore paralelization.
Therefore, the multicore paralelization provides 56.4 / 4.98 = x11.32.

**Second Question**

After setting all the array values to 1 (which is the initial guess so the calculation of the sqrt goes down to O(1)).
We can see that the speedup both for SIMD and multicore parallelization it's almost none, which can be explained by using the same concepts when building divide and conquer algorithms.
This is a case where we have to split the problem, solve it, and then join the results. Both splitting and joining have a cost, but as long as the computation is faster there is margin for improvement. Since here the computation of every instance is almost the same, and is really low, adding more cores or ALU units can not overcome the cost of splitting and joining.
/*
Output received
[sqrt serial]:          [13.955] ms
[sqrt ispc]:            [9.143] ms
[sqrt task ispc]:       [7.882] ms
                                (1.53x speedup from ISPC)
                                (1.77x speedup from task ISPC)
*/


**Third Question**

For this question we want to reduce the speedup given by the ISPC. As seen before, the value 1 makes the computation trivial, leading to the overhead of the parallel version set up and join being significant in comparison with the computing time, and so, providing almost x1~x2 speedup.

/*
[sqrt serial]:          [13.775] ms
[sqrt ispc]:            [9.481] ms
[sqrt task ispc]:       [7.791] ms
                                (1.45x speedup from ISPC)
                                (1.77x speedup from task ISPC)
*/
