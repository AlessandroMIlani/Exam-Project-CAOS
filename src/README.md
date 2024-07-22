# Source Files Overview

## Basic Demos

The source files in this directory include the following basic demos:

- `display_demo.c`: Demonstrates basic display functionality.
- `input_demo.c`: Showcases how input is handled.
- `chaos_demo.c`: Illustrates chaotic system behavior.
- `pong_demo.c`: Implements a classic Pong game.

These file ar linked with the `main.c` file that manage them

## EDF and Default Scheduler Tests

The EDF (Earliest Deadline First) scheduler and default scheduler tests are provided to evaluate different scheduling strategies:

- `test_edf_scheduler.c`: Basic example of EDF scheduler with 2 tasks
- `benchmark_default_scheduler.c`: Case utilized for benchmarking the default scheduler's performance.
- `benchmark_edf_scheduler.c`: Case utilized for benchmarking the EDF scheduler's performance.

## Configuring the EDF Scheduler

Before compiling files that utilize the EDF scheduler, you need to configure the `FreeRTOSConfig.h` file to enable EDF scheduling. Follow these steps:

1. Open the `FreeRTOSConfig.h` file
2. Locate the configuration option for the scheduler, named `configUSE_EDF_SCHEDULER`.
3. Set this option to `1` to enable the EDF scheduler:
   
   ```c
   #define configUSE_EDF_SCHEDULER 1
   ```

4. Save the changes to `FreeRTOSConfig.h`.

These steps ensure that the EDF scheduler is used when running the corresponding test files.

## Debug configuration
For debugging purposes, you can edit the `FreeRTOSConfig.h` file as follows:
1. Adjust the `configCPU_CLOCK_HZ` value to slow down execution. For example, you can increment it as shown in the comment at line `54`:

   ```c
   #define configCPU_CLOCK_HZ	( ( unsigned long ) 5000000000000000000 )
   ```

2. Enable tracing by declering the constant `ENABLE_TRACING`:
   
   ```c
   #define ENABLE_TRACING
   ```

## Additional Information

For more details on how to use the Makefile commands or for troubleshooting, refer to the main `README.md` file located in the `../build` directory of the project.
