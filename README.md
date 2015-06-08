# water
a simple timer device for watering flowers. msp430f2001 is used

I use WDT with SMCLK to generate 10sec intervals. The algorithm of watering is as follows:
1. Water for 10 secs
2. Wait for 1 minute
3. Water for 10 secs
4. Wait for 12 hrs

The watering pump is like this http://www.banggood.com/Mini-Submersible-DC-Motor-Pump-3V-120LH-Low-Noise-Max-Lift-p-87235.html
connected to msp through a mosfet. Powered on 2xAA (approx 100mA in active regime, less than 0.1 mA in inactive)
