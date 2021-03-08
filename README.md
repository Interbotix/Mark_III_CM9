# Phoenix Code for OpenCM9.04 and Playstation 4 remote

## Project Contributors
Jeroen Janssen [aka Xan] - The original Phoenix code was written by to run on the Lynxmotion Phoenix (http://www.lynxmotion.com/c-117-phoenix.aspx). It was originally written in Basic for the Basic Atom Pro 28 processor by Basic Micro.

Kare Halvorsen (aka Zenta) - The Lynxmotion Phoenix was based on the original Phoenix that was developed by him. In addition a lot of the software was based off of his earlier Excel spreadsheet (PEP). More details up on his Project page (http://www.lynxmotion.com/images/html/proj098.htm).

Kurt Eckhardt (aka Kurt) - Kurt later ported the code to C/C++ and the Arduino environment. His work in this regard can be found [here](https://github.com/KurtE/Arduino_Phoenix_Parts). He further extended his [fantastic work](https://github.com/KurtE/Open_CM_CR_Arduino_Sketches) to use the ROBOTIS DynamixelSDK in order to allow for the Phoenix code to work on the ROBOTIS OpenCM9.04 board.

Me - My efforts on this project were to allow for the use of a Playstation4 remote to control the hexapod and adjust the Phoenix code accordingly.

## Directory Layout

### Phoenix Code
You will find the code to be run by the OpenCM9.04 board in the [Phantom_Phoenix](./Phantom_Phoenix) folder. This is the phoenix code used to control the PhantomX Mark III Hexapod.

### Esp32 Code
You will find the code to be run by Esp32 board in the [PS4_esp32](./PS4_esp32) folder. This code is used to connect to a PS4 remote via bluetooth and then send the relevant control input data to the OpenCM9.04 via UART.

There is also a folder called [FIND_ESP_MAC](./FIND_ESP_MAC), in which there is a small arduino script to find the MAC address of the Esp32, this is used in the setup described below.

## Setup
This serves as a guide to describe how to set up your Playstation4 remote and your Esp32 to work together to get input to the hexapod! This should already be done if you purchased your hexapod from Interbotix, but this guide is available for using a new remote or if something else goes wrong with connecting your PS4 remote!

### Playstation4 Library
The first step is to download this [PS4-Esp32 Library](https://github.com/aed3/PS4-esp32) (Credit to [aed3](https://github.com/aed3) for their fantastic library!). With this downloaded to your computer, place the file "PS4-esp32-master" amongst the rest of your Arduino libraries - likely in `/Arduino/libraries`.

### Pairing Your Esp32 to your PS4 remote
Upload the code `FIND_ESP_MAC.ino` onto your Esp32 and open up the Serial port. You should then see the MAC address of your Esp32 printed out. For example, it would be a number that looks like this: `01:02:03:04:05:06`. Remember this number!

Next you will need to download [Sixaxispairtool](https://sixaxispairtool.software.informer.com/download/) - which is what I used or you can also use [sixaxispairer](https://github.com/user-none/sixaxispairer). This software is used to change the MAC address that the PS4 remote will look to make a Bluetooth connection with. Plug your PS4 remote into the computer USB port and run the Sixaxispairtool software, the software should give you the chance to input a new MAC address, this is where you put in the MAC address that the `FIND_ESP_MAC.ino` script gave you!

From this point on, when you turn on your PS4 remote (with the PS4 button), it will automatically look for and connect to your Esp32!

### Run the PS4_esp32 code
Next, remember to upload the `PS4_esp32.ino` code onto your Esp32. This will give you PS4 remote control of your hexapod!

### Upload the Phoenix code
With all of the relevant phoenix code files ([Phantom_Phoenix](./Phantom_Phoenix)) in the correct place - in the same directory as the `Phantom_Phoenix.ino` sketch - don't forget to upload the `Phantom_Phoenix.ino` sketch to the OpenCM9.04 board in order to get the Hexapod going!