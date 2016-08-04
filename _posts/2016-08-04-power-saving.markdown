---
layout:   post
title:    "Power saving"
date:     2016-08-04 23:10:00 +0300
category: construction
---

To operate long time using some energy source there has to be used some powersaving. Simple `delay` does not make Arduino consume less power. [Sleep mode][sleep-mode-site] should be used. To return from sleep, interrupt is used.

See [sleep][sleep-root] for example usage.

[sleep-mode-site]: http://playground.arduino.cc/Learning/ArduinoSleepCode
[sleep-root]: https://github.com/dimalev/arduino-starters/tree/master/sleep
