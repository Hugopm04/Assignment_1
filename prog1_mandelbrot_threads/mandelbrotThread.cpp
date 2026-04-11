#include "CycleTimer.h"
#include <cstdlib>
#include <stdio.h>
#include <thread>

typedef struct {
  float x0, x1;
  float y0, y1;
  unsigned int width;
  unsigned int height;
  int maxIterations;
  int *output;
  int threadId;
  int numThreads;
} WorkerArgs;

extern void mandelbrotSerial(float x0, float y0, float x1, float y1, int width,
                             int height, int startRow, int numRows,
                             int maxIterations, int output[]);

//
// workerThreadStart --
//
// Thread entrypoint.
void workerThreadStart(WorkerArgs *const args) {

  // TODO FOR STUDENTS: Implement the body of the worker
  // thread here. Each thread should make a call to mandelbrotSerial()
  // to compute a part of the output image.  For example, in a
  // program that uses two threads, thread 0 could compute the top
  // half of the image and thread 1 could compute the bottom half.

  // Task 3, added the included CycleTimer to time each thread separately
  // This is the start for the timer
  double threadTimerStart = CycleTimer::currentSeconds();
  // Task 1, added the rows per thread and start row so that it could calculate the amount of rows and decide the amount
  // of rows per thread. Rows per thread calculates the amount of rows that each thread has, and startrow decides where
  // the thread will start.
  // int rowsPerThread = args->height / args->numThreads;
  // int startRow = args->threadId * rowsPerThread;


  // This dedicates the amount of rows for each thread, but incase the number is not evenly divisible, the last thread
  // gets the leftover rows.
  /*int numberOfRows;
  if (args->threadId == args->numThreads - 1)
  {
    numberOfRows = args->height - startRow;
  } else
  {
    numberOfRows = rowsPerThread;
  }
  mandelbrotSerial(
    args->x0, args->y0, args->x1, args->y1,
    args->width, args->height,
    startRow, numberOfRows,
    args->maxIterations,
    args->output);
  */

  // The replacement for assigning the rows to the threads. This for loop gives each thread the nth row, where n is the amount of threads.
  // So when you run the program with 4 threads thread one would get rows 0, 4, 8...
  // This means that no thread will get purely black (easy) rows, but that each thread gets around the same amount of difficult rows.
  for (int row = args->threadId; row < args->height; row += args->numThreads)
  {
    mandelbrotSerial(args->x0, args->y0, args->x1, args->y1,
    args->width, args->height,
    row, 1,
    args->maxIterations,
    args->output);
  }

  // The stop for the timer to compare to the start
  double threadTimerStop = CycleTimer::currentSeconds();

  //Print for the thread, had to add a \n for easier reading
  printf("Thread %d: time = %.3f ms\n",
    args->threadId,
    (threadTimerStop - threadTimerStart) * 1000);
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning std::threads.
void mandelbrotThread(int numThreads, float x0, float y0, float x1, float y1,
                      int width, int height, int maxIterations, int output[]) {
  static constexpr int MAX_THREADS = 64;

  if (numThreads > MAX_THREADS) {
    fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
    exit(1);
  }

  // Creates thread objects that do not yet represent a thread.
  std::thread workers[MAX_THREADS];
  WorkerArgs args[MAX_THREADS];

  for (int i = 0; i < numThreads; i++) {

    // TODO FOR STUDENTS: You may or may not wish to modify
    // the per-thread arguments here.  The code below copies the
    // same arguments for each thread
    args[i].x0 = x0;
    args[i].y0 = y0;
    args[i].x1 = x1;
    args[i].y1 = y1;
    args[i].width = width;
    args[i].height = height;
    args[i].maxIterations = maxIterations;
    args[i].numThreads = numThreads;
    args[i].output = output;

    args[i].threadId = i;
  }

  // Spawn the worker threads.  Note that only numThreads-1 std::threads
  // are created and the main application thread is used as a worker
  // as well.
  for (int i = 1; i < numThreads; i++) {
    workers[i] = std::thread(workerThreadStart, &args[i]);
  }

  workerThreadStart(&args[0]);

  // join worker threads
  for (int i = 1; i < numThreads; i++) {
    workers[i].join();
  }
}
