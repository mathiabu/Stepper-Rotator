# Stepper-Rotator
Rotation machine for recirculating Organ-on-Chip systems. There are currently 2 versions of the machine: (A) with manual tilt adjustment and (B) with servo-motor controlled tilt adjust. As seen in the image of the fully mounted device, it consists of a main body and a changeable rotor that holds the chips. 

Usage instructions (Version A):
1. Mount the rotor and place the plates/chips.
2. Set the desired tilt by loosening, moving, and tightening the wing nuts on the side.
3. Connect the machine to the power supply (9-12 V) and turn it on (at the backside).
4. While the motor is off (after startup) you can adjust the speed between 0 and 2.5 rpm and also change the rotation direction (clockwise (CW) or counterclockwise (CCW)) by turning the knob.
5. To run the motor, press the on/off button. The user input is blocked while the motor is running. If you want to change the speed, turn the motor off, adjust the speed, and run it again.

Mounting instructions of the body (Version A):
1. Laser-cut DXF files into acrylic. Use the following thickness for the different parts: Back, Front, Bottom, and Side: 5 mm, Top: 1.5 mm, Adapter: 6 mm. Use 2x Adapter-left and 2x Side-A. Delete the text and angle scale in Side-A and engrave this in the second step.
2. Some of the files contain engravement (Side-A, Back). You have to align the engravement with the cut parts and create an overlay to only remove the difference in the software of your lasercutter. For both versions, this is a Hex-nut for the power connector. In version A engrave only the scale for the tilt. If you want it on both sides, mirrow it. All engravements should be 1-2 mm deep.
3. 3D-print the STL files in a hard material using a FDM- or DLP-based printer. Use enough infill to be able to tap a thread later on. Print the mounting cubes 4x each (normal and mirrowed) and the front bar only 1x.
4. Use a drilling machine with a countersink bit to drill countersinks on the outer parts of the sides, the front, and the back.
5. Use a hand-tapping tool with M3 thread to tap threads in all mounting cubes, the front bar, the front, and the adapter parts.
6. Mount the Arduino board at the bottom so that the USB port faces the backside using 5mm long distance rolls (motherboard standoffs, or spacers) with M3 thread stack 10 mm distance rolls on top of them to mount the custom-made Arduino shield later on. Mount the power socket and the power switch on the backside. Mount the motor on the top plate using short M3 screws. Screw a long M3 screw to both adapter parts so that the screw head faces inside and the screw sticks out on both sides. Mount the LCD display using 5mm M3 distance rolls, the potentiometer, and the On/off button to the front panel.
7. Mount the adapters to the side parts and loosely fix them with wing nuts. Both adapters should be symmetrically mounted. Mount the motor to the top plate.
8. Solder a red wire from the (+) pole of the connector to the power switch. Solder a red wire (min 15 cm long) to the other pole of the power switch with an open end. Solder a black wire with an open end to the (-) pole of the the power connector (min 15 cm). Solder a 3-pin female connector (pitch 2.54 mm) to the potentiometer and a 2-pin female connector (pitch 2.54 mm) to the on/off button with 15 cm long wires.
9. Mount & solder additional components to the Arduino motorshield and wire as explained in the attached PDF (Wiring-diagramm-A). The 
10. Mount the sides, the front, and the back using the mounting cubes and the front bar. Use the mirrowed and normal versions and rotate them so that the holes fit each other. Set the tilt to 0 degrees and align the top plate (with the mounted motor) with the adapter. Mark the positions for the mounting holes on the adapter and drill 4 holes into the adapter with a diameter of 2.5 mm and a depth of 10mm. Tap a M3 thread into the holes and mount the top plate (with the motor) with 4 screws.
11. Stack the customized shield to the Arduino and connect the on/off button, the potentiometer, the display, and the motor driver using cables. Use the respective screw terminals on the motor driver and the Arduino shield to connect the main power (red/black wire), the motor, and the motor power supply. Consult the wiring diagram.
12. Finally, close the bottom part and fix it with 4 countersink screws. Connect a USB cable to your computer and flash the firmware (version A) to the Arduino. Disconnect and power with an external power supply. Check if the device is functioning accordingly and mount the rotor using an M2 screw.

Mounting instructions (Rotor):
1.  Laser cut the lower part in 1.5 mm and the upper part in 5 mm acrylic (Select the desired version from the folders attached).
2.  3d print the rotor part with an FDM or SLA printer.
3.  Tap an M3 thread in the 4 bigger holes and an M2 thread in the smaller hole that is mounted to the motor shaft.
4.  Drill countersinks in the thinner acrylic part and tap M3 threads in the 5 mm acrylic sheet.
5.  Mount the thinner and the thicker acrylic sheet together with the 3d-printed part using countersink M3 screws.
