#  Computer architectures and operating systems 

## Version Information

We are using version 202212.01, which is the latestest tag on the [master branch](https://github.com/FreeRTOS/FreeRTOS/tree/202212.01) available at the time of writing this.

For cross-compiling, we are using the Arm GNU Toolchain version 13.2.rel1, released on October 30, 2023. This toolchain can be downloaded from the [Arm Developer website](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).

## Structure of this repository

The repository is structured as follows:

- `./FreeRTOS`: This is the submodule that contains the FreeRTOS source code. As stated above, we are using the latest tag on the master branch. This has been pruned of any demo and test code.
- `./src`: This is the directory that contains the source code for the project.
- `./build`: This is the directory that contains the build files for the project. This includes the Makefile and subdir.mk.
- `./doc`: This is the directory that contains the documentation for the project, namely the report and the presentation.

## Compilation and Source Code Information

For more information on how to compile the project, refer to the README file in the `./build` directory.

For details on the source code structure, refer to the README file in the `./src` directory.


