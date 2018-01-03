/** BMSCommsSender
 * This class creates status packets to send over serial to an external charger
 **/

#pragma once

#include"Arduino.h"
#include"CellComms.h"

// Data Structure Defines
#define BMSCOMMS_PACKET_LENGTH        3

#define BMSCOMMS_MILLIVOLT_OFFSET     1652
#define BMSCOMMS_MILLIVOLTS_MAX       3700

// exit statuses
#define BMSCOMMS_SUCCESS              0
#define BMSCOMMS_FAILURE              1

// Statuses
#define BMSCOMMS_STATUS_OK            0
#define BMSCOMMS_STATUS_FAULT         1
#define BMSCOMMS_STATUS_OVER_VOLTAGE  2
#define BMSCOMMS_STATUS_OVER_TEMP     3
#define BMSCOMMS_STATUS_UNDER_VOLTAGE 4

// Balancing
#define BMSCOMMS_BALANCE_NONE         0
#define BMSCOMMS_BALANCE_SOME         1
#define BMSCOMMS_BALANCE_ALL          2

class BMSCommsSender
{
 public:
   BMSCommsSender(
     Stream & Serial,
     CellComms & CellComms
   );
   BMSCommsSender(
     Stream & Serial,
     CellComms & CellComms,
     uint8_t packetLength,
     uint16_t millivoltOffset,
     uint16_t millivoltMax
   );

   void send_packet(void);

 private:
   Stream & _Serial;
   CellComms & _CellComms;
   uint8_t* bmscommsDataArr;
   const uint8_t
    _packetLength, _millivoltOffset, _millivoltMax;
   uint8_t
    calculate_status_byte(void),
    calculate_balancing_byte(void);
  uint8_t * encode_packet(
    uint16_t milliVolts,
    uint8_t status,
    uint8_t balancing
  );
};
