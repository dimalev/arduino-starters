---
layout:   post
title:    "Uploading sketch to Arduino Mini"
date:     2016-08-02 23:13:00 +0300
category: construction
---

Arduino Mini comes without USB connection. To be able to connect it to computer, use USB - UART TTL converter.

To check your USB adapter:

 1. Wire USB adapter's `TX` to it's `RX` (this will make it recieve same data, which it transmitted).
 2. Plug USB into computer.
 3. In Arduino IDE, check *Tools* -> *Port*, and select propper (hopefuly) COM port.
 4. Open *Serial Monitor*, and type any string into input - you should recieve it back.
 5. If you don't recieve data back - you might select wrong COM port, or you have mulfunction USB converter.

Wiring USB to Arduino
---------------------

To communicate, Arduino and USB will use `RX` and `TX` pins. Both have them, and they must be connected as `USB-TX` to `Arduino-RX` and `USB-RX` to `Arduino-TX`. One of these pins is transmitter, another is reciever. That is why they are wired like this.

Power for Arduino can be connected to `5V` and `Gnd` pins to corresponing pins of USB converter. These same pins can used to power other connected devices. This will work, because all these devices will be connected in parallel, and hence - will have same voltage (which is important).

You can use external power source (9V battery). In this case - you should plug battery's `+` to Arduino Mini's `9V` marked pin. `Gnd` should be connected to same pin. Other devices should be powered from pin marked `5V`, or `3.3V` depending on there requirements.

Uploading Sketch
----------------

After connecting Arduino to computer, select propper port (see top of the chapter), and *Tools* -> *Board*. Changing board will force complete recompelation of your sketch. This might take some time.

To upload sketch - click *Upload* button in Arduino IDE, and *SIMULTANEOUSLY* press and hold *Reset* button on Arduino Mini board. As soon as upload process complete (green bar of compile/upload disappears) - release *Reset* button. You will see blue LEDs start flashing on your USB converter.

Upload complete! Sketch is already working.

External Powering
-----------------

See wiring Arduino section for these details. Last passage explains powering from 9V battery. 5V can be used from external USB powering.

Read More
---------

[Uploading sketches on Aruino Mini][arduino-mini-tutorial].

[arduino-mini-tutorial]: https://www.arduino.cc/en/Guide/ArduinoMini
