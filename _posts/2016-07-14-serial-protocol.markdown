---
layout: post
title:  "Serial Protocol"
date:   2016-07-14 01:29:55 +0300
category: connected
---

Serial Protocol is based on transmitting bytes, and receiving them. For this,
they have two wires - `RX` and `TX`. When connecting two devices (like arduino and
USB - UART TTL converter), they must be twisted. See 
[how to program arduino mini]({{ site.baseurl }}{% post_url 2016-08-02-upload-on-arduino-mini %})
for an example.

Main problems of this protocol, is that you can connect only two devices together, not more.
Other protocols like `SPI` or `I2C` handle this problem.