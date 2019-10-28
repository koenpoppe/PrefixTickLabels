# PrefixTickLabels
## Problem statement
Most plot libraries are able to detect a common scale factor if the range of the data is too big. For example, if the data is ranging in tens of thousands, chances are that a common scaling factor of will be added to the axis to shorten the tick labels:
```none
--+------+------+------+------+------+---
125000 150000 175000 200000 225000 250000
```
could become
```none
--+------+------+------+------+------+---
 125    150    175    200    225    250    x 10^3
```
This not only reduces the visual load but might allow more ticks to be placed on the same range.

However, the same is not true for very small ranges that are positioned far from the origin. A simple scaling does not help here. So, what this library proposes is to extract a common prefix based on the data and display only the remainder of the numbers on the ticks. This way,
```none
--+------+------+------+------+------+---
3.1415 3.1416 3.1417 3.1418 3.1419 3.1420
```
could be presented as
```none
--+------+------+------+------+------+---
 500µ   600µ   700µ   800µ   900µ  1000µ   31.141XXX
```
In our opinion, this not only has the same benefits as the scaling does, but also gives a clearer indication of the range that is shown in the graph.
