---
layout: post
title:  "Adding bluetooth to Arduino"
date:   2016-07-14 01:29:55 +0300
category: connected
---

This is done in two steps: first - configure your bluetooth adapter to be ready to get connections, e.g. set visible name and PIN; and second - plug it to your Arduino!

Tell where to buy [UART to TTL USB adapter][where-to-buy-uart-to-ttl].

Configure bluetooth adapter {#configure}
---------------------------

Tell about `AT` commands and baud configuration.

Use Bluetooth {#use}
-------------

![Arduino Wiring]({{site.baseurl}}/img/arduino-wired-bluetooth-new.png)

Tell that `Serial` is ready to go through attached Arduino.


[where-to-buy-uart-to-ttl]: http://arduino-ua.com/prod232-USB_20_-_UART_TTL_perehodnik_na_CP2102
