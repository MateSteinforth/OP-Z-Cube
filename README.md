# OP-Z-Cube
A beautiful Light Object for the Teenage Engineering OP-Z

[![](http://img.youtube.com/vi/yUOjW_sgsTw/0.jpg)](http://www.youtube.com/watch?v=yUOjW_sgsTw "OP-Z Light Object")

Cleaned source for not so you can easily connect and configure your LEDs to your OP-Z with an Ardunio

The list of numbers in the beginning of the source code are the LED IDs that you want to be played per one of the 16 OP-Z channels. So if you connect your LEDs via WS2818 or similar controller, each LED will have a number. Just put any combination of numbers in here you want. So for example, if you have 160 LED and you want 10 to light up for each channel, just put 0,1,…10 in the first row, 11,12…20 in the second and so on.

The upside of using this is that you’re completely flexible, so that way I was able to do this cool mapping to the diagonals of the cube you see in the video.

The only other parameters you need to set are MAXLED which is the channel with the most LEDs you have, and DATA_PIN which is the Pin on your Arduino you use to connect to your LEDs.

And yes, you will need a powered and compatible USB Hub or you can just provide your LEDs with external power, whichever you like.

I will probably also upload the hardware design files so you can make your own cube!

I’m also thinking of making pre-built ones with beautiful black PCBs like the Teenage Engineering Pocket Operators have. If you’d be interested in this, LMK.
