# Discussion of the results

It is hard to provide a quantitative measurement of the communication rate,
because there is an high variability in the rate of the loop.

I believe it is much more interesting to observe qualitatively what happens 
and try to understand why.

In a non realtime OS, the linux kernel can take up to tenths or hundreds of 
microseconds to switch to a different context or unlock a mutex. Furthermore, 
the latency is negatively affected by the other processes running in the system.

A realtime OS, for instance linux patched with RT_PREEMPT, can easily achieve 
maximum latencies below 30 __microseconds__, while a "normal" Linux kernel might 
occasionally have latencies in the order of the __millisecond__.

__NOTE__: usually the periodic loop will sleep slightly more than expected.
For this reason it is not surprising that the number of message sent per second is
always smaller than the expected one.

## C++ publisher

Increasing the rate of the publishing loop, its jitter increase accordingly.

Up to 15 KHz, the number of messages sent is in the order of 14.500 +/- 500.

At 20 KHz, the number of messages sent per second considerably oscillates
between 14.000 and 18.000 

The amount of CPU used is roughly 75% +/- 10%. This means that is not a problem
of throughput of the CPU, but rather a latency problem.

## Python publisher

On the other hand, the Python publisher seems to be CPU-bound.
The maximum rate is 4000 +/- 1000, with 100% CPU utilization when a single subscriber is running.
When multiple subscribers are connected, the rate decrease even further.

## Subscribers

Both Python and C++ subscribers seems to confortably tolerate 
publishing rates of 15 KHz, with the former consuming about 70% of the CPU and the
latter about 60%.

Both subscribers start loosing some messages after 5 KHz, about 3% of them at 15 KHz.
For some reason the Python implementation seems to be able to miss less messages (<1% only).






