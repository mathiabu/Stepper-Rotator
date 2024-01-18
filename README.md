# Stepper-Rotator
Rotation machine for recirculating Organ-on-Chip systems. There are currently 2 versions of the machine: (A) with manual tilt adjustment and (B) with servo-motor controlled tilt adjust.

Mounting instructions:

1. Laser-cut DXF files into acrylic. Use following thickness for the different parts:
  Back, Front, Bottom and Side: 5 mm, Top: 1.5 mm, Adapter: 6 mm.
  For version (A) use 2x Adapter-left and 2xSide-A. Delete the text and angle scale in Side-A and engrave this in the second step.
  For version (B) use Adapter-left + Adapter-right and Side-B-left + Side-B-right
2. Some of the files contains engravemt (Side-B right, Side-A, Back). You have to align the engravement with the cutted parts and create and overlay to only remove the difference in the software of your lasercutter. For both versions this is a Hex-nut for the power connector. In version A engrave only the scale for the tilt. If you want it on both sides, mirrow it. For version B, engrave rectengular structure on side-B-right to fix the servomotor. All engravements should be 1-2 mm deep.
3. 3D-print the stl files in a hard material using a FDM- or DLP-based printer. Use enough infill to be able to tap a thread later on. Print the mounting cubes 4x each (normal and mirrowed). The other parts only 1x.
4. Use a hand tapping tool with M3 thread to tap threads in all mounting cubes, the front bar and the adapter parts. Use a M2 tapping tool for the rotator fixing thread.
5. Mount the Arduino board at the bottom so that the USB port faces the backside using 5mm long distance rolls with M3 thread and M3 screws. Mount the power socket and the power switch on the backside. Mount the motor on the top plate using short M3 screws. Screw a long M3 screw to both adapter parts so that the screw head faces inside and the screw sticks out on both sides. Mount the LCD display using 5mm M3 distance rolls.
6. Mount the adapters to the side parts and loosely fix it with wing nuts. Bot adapters should be symmetrically. 
