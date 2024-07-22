# Compilation and Execution Guide

## Compilation

The project can be compiled in two different ways based on the demo you want to execute:

### 1. Basic Demos

To execute one of the four basic demos, use the following command:

```bash
make all DEMO=X
```

Replace `X` with one of the following values:
- `1`: Display Demo
- `2`: Input Demo
- `3`: Chaos Demo
- `4`: Pong Demo

### 2. EDF and Default Scheduler Tests

**Note**: Before compiling a file that uses an EDF scheduler, check the `README` in the `../src` folder to apply the necessary changes to the `FreeRTOSConfig.h` file.

To execute one of the test files related to the EDF scheduler, use:

```bash
make edf DEMO=Y
```

Replace `Y` with the name of the file you want to execute. Possible values are:
- `test_edf_scheduler.c`
- `benchmark_default_scheduler.c`
- `benchmark_edf_scheduler.c`

## Execution

To execute the compiled files, use:

```bash
make run
```

## Cleaning Compiled Files

To clean up compiled files, use:

```bash
make clean
```
