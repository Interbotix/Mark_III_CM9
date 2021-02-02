# Phoenix Code for OpenCM9.04 and Playstation 4 remote

## Project Contributors
Jeroen Janssen [aka Xan] - The original Phoenix code was written by to run on the Lynxmotion Phoenix (http://www.lynxmotion.com/c-117-phoenix.aspx). It was originally written in Basic for the Basic Atom Pro 28 processor by Basic Micro.

Kare Halvorsen (aka Zenta) - The Lynxmotion Phoenix was based on the original Phoenix that was developed by him. In addition a lot of the software was based off of his earlier Excel spreadsheet (PEP). More details up on his Project page (http://www.lynxmotion.com/images/html/proj098.htm).

Kurt Eckhardt (aka Kurt) - Kurt later ported the code to C/C++ and the Arduino environment. His work in this regard can be found [here](https://github.com/KurtE/Arduino_Phoenix_Parts). He further extended his [fantastic work](https://github.com/KurtE/Open_CM_CR_Arduino_Sketches) to use the ROBOTIS DynamixelSDK in order to allow for the Phoenix code to work on the ROBOTIS OpenCM9.04 board.

Me - My efforts on this project were to allow for the use of a Playstation4 remote to control the hexapod and adjust the Phoenix code accordingly.

## Directory Layout

### Phoenix Code
You will find the code to be run by the OpenCM9.04 board in the [Phantom_Phoenix](../Phantom_Phoenix) folder. This is the phoenix code used to control the PhantomX Mark III Hexapod.

### Esp32 Code
You will find the code to be run by Esp32 board in the [PS4_esp32](./PS4_esp32) folder. This code is used to connect to a PS4 remote via bluetooth and then send the relevant control input data to the OpenCM9.04 via UART.
