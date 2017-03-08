# physical_computing

A repo for the work done in Physical Computing.

#Pulse Cheater

Pulse Cheater was inspired by the idea of cheating a polygraph. In this simplification, a breadboard is taped within a
light-tight box. Three inputs exist outside the box: two switches and a pulse reader. One input is inside the box, a photocell.
There is is also one ouput inside the box, an LED. When the LED is lit, the photocell reads the light. This is printed to the
serial monitor. This LED-photocell interaction is the stand in for the polygraph.

When an active pulse is not read by the pulse sensor and no switches are active, the LED is off. When switch one is active, the
LED lights up. When switch two is active, the LED is off even if a pulse is read. If both switches are active at once, the 
LED is off.
