# BMSCommsSender
BMS Communications from Cell Top Master via serial

## Minimal example
Instantiate the `BMSCommsSender` class as:
```
#include <Arduino.h>
#include <CellComms.h>
#include <BMSCommsSender.h>

#define NUMBER_OF_CELLS  12

// Setup serial device to talk to CTM ring:
HardwareSerial Serial1(1)
HardwareSerial Serial2(2)

CellComms cells(NUMBER_OF_CELLS, Serial1);
BMSCommsSender bmsCommsSender(
  Serial2,
  cells
);
```

Use as:
```
...
  cells.readCells();
  bmsCommsSender.send_packet();
```
