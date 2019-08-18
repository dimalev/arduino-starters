---
layout: post
title:  "Shift Registers and Arduino"
date:   2019-08-18 11:24:00 +0100
category: controls
---

Shift registers allow storring and passing of 8-bit values. The name "shift-" it gets because of
the way it reads, and writes it's bits. When you write one bit - all the current bits are shifted,
and new one is put onto free place. This way, the last one (which was pushed first) can pop out -
and become an input for next shift register. This allows user to stack shift registers one by one,
and get bigger pieces of memory.

Reading is possible in the same way.

[See how to use](https://www.youtube.com/watch?v=6BLj9Ak2Djs).

[shiftOut() function](https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/).

[Arduino tutorial](https://www.arduino.cc/en/tutorial/ShiftOut).

[Datasheet](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf).