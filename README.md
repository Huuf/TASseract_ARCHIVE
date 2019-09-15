# TASseract
It got a better name!

# Releases
If you want to get the most reliable version, check the releases, any other links can be in development and non working (currently no design is verified working yet).

## Overview
This project aims to create an easy-to-use, multi-system TAS replay device to be used on actual consoles. The name of this project comes from the fact that it is powered by a [STM32H745ZIT6](https://www.st.com/en/microcontrollers-microprocessors/stm32h745zi.html) microcontroller.

# Thanks
[Ownasaurus](https://github.com/Ownasaurus) for having done the [TAStm32](https://github.com/Ownasaurus/TAStm32)

Ilari for insights in low level NES/SNES stuff

DwangoAC for introducing me to this community

The [TASBot](http://discord.tas.bot) community

# Setting up build environments + building

## Windows
### Setting Up
1. Install the GNU arm toolchain from [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) - latest version that ends with -sha2.exe (add path to environment variable, default unchecked, version at the time of writing is `gcc-arm-none-eabi-8-2019-q3-update-win32-sha2.exe`)
2. Install Make for Windows from [here](http://gnuwin32.sourceforge.net/packages/make.htm), download the setup file (Complete package, except sources)
3. Install the latest version of python3
4. Run `python -m pip install pyserial` and then `python -m pip install _______` install any missing modules
### Building
1. Go into the src directory
2. Run `setenv.bat`
3. Run `makeall.bat` to compile
### Flashing the firmware
1. Run `python dfu.py` to put the device in DFU mode (if it is not already)
2. Run `flashall.bat` to flash the compiled firmware

# PCB
The PCB is made in the free software [CircuitMaker](https://circuitmaker.com/) and can be found here: [Development PCB](https://circuitmaker.com/Projects/Details/Hans-Anders-3/TAStm32H745ZIT6).

# Case
The case is made in the free for certain parties software [Fusion 360](http://fusion360.autodesk.com) and can be found here: [Development case](https://a360.co/2Kgfb6K).

# Source Code
This project is written in C with some ASM.

The source code is available in the src directory. In here you will find code generated using [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) and then modified according to the needs of the project. Note that the .ioc file may not be consistent with the latest version of the source code.

# Duh
If I had a Duh moment (forgot credits, stuff like that), you can contact me on [Discord](http://discord.tas.bot) and @Skippy#5840
