---
layout: post
title:  "Shift Registers and Arduino"
date:   2016-07-14 01:29:55 +0300
category: controls
---

Shift registers allow storring and passing of 8-bit values. The name "shift-" it gets because of
the way it reads, and writes it's bits. When you write one bit - all the current bits are shifted,
and new one is put onto free place. This way, the last one (which was pushed first) can pop out -
and become an input for next shift register. This allows user to stack shift registers one by one,
and get bigger pieces of memory.

Reading is possible in the same way.

[See how to use](https://www.youtube.com/watch?v=6BLj9Ak2Djs).