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

After setting all the values of the array to 3 - 1e-5 (almost 3) which is the furthest point from the initial guess we can provide, we can see a noticeable improvement in both SIMD and multicore paralelization being respectively:
SIMD x7.43 speedup
Multicore 69.14 / 7.43 = x9.3
We can justify this looking back at the second question. In this case, splitting and joining for both for SIMD and multicore was worth it as the compution was more expensive and being able to do it in parallel saved a lot of time compared to doing it sequentialy.

/*
Output received
[sqrt serial]:          [2726.011] ms
[sqrt ispc]:            [366.907] ms
[sqrt task ispc]:       [39.430] ms
                                (7.43x speedup from ISPC)
                                (69.14x speedup from task ISPC)
*/
