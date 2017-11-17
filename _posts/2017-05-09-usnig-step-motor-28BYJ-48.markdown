---
layout: post
title:  "Using Step Motor"
date:   2017-05-09 12:25:00 +0300
category: controls
---

Step motors allow controled rotation. They implement it using steps. To use it - you need controller.

My controller for step motor 28BYJ-48 has 4 input channels. To make one step - we must send 8 singals in sequence:

|------+-----+-----+-----+-----|
| Step | IN1 | IN2 | IN3 | IN4 |
|:----:|:---:|:---:|:---:|:---:|
| 1 | 1 | 0 | 0 | 0 |
| 2 | 1 | 1 | 0 | 0 |
| 3 | 0 | 1 | 0 | 0 |
| 4 | 0 | 1 | 1 | 0 |
| 5 | 0 | 0 | 1 | 0 |
| 6 | 0 | 0 | 1 | 1 |
| 7 | 0 | 0 | 0 | 1 |
| 8 | 1 | 0 | 0 | 1 |
|---+---+---+---+---+

Projects
--------

See [Step Motor][stepmotor-github]. It rotates step motor for some time, them makes delay for one second and repeat.

[stepmotor-github]: https://github.com/dmytrolev/IoT/tree/master/stepmotor