/** BMSCommsSender
 * This class creates status packets to send over serial to an external charger
 **/
#include "BMSCommsSender.h"

BMSCommsSender::BMSCommsSender(
     Stream & Serial,
     CellComms & CellComms,
     uint8_t packetLength = BMSCOMMS_PACKET_LENGTH,
     uint16_t millivoltOffset = BMSCOMMS_MILLIVOLT_OFFSET,
     uint16_t millivoltMax = BMSCOMMS_MILLIVOLTS_MAX
   ) :  _Serial (Serial),
        _CellComms (CellComms),
        _packetLength (packetLength),
        _millivoltOffset (millivoltOffset),
        _millivoltMax (millivoltMax),
        bmscommsDataArr(new uint8_t[packetLength])
  {}
BMSCommsSender::BMSCommsSender(
     Stream & Serial,
     CellComms & CellComms
   ) : BMSCommsSender(
     Serial, CellComms,
     BMSCOMMS_PACKET_LENGTH,
     BMSCOMMS_MILLIVOLT_OFFSET,
     BMSCOMMS_MILLIVOLTS_MAX
   )
   {}

void BMSCommsSender::send_packet(void) {
  _Serial.write(
    encode_packet(
      _CellComms.millivoltsMax(),
      calculate_status_byte(),
      calculate_balancing_byte()
    ),
    _packetLength
  );
}

uint8_t * BMSCommsSender::encode_packet(
    uint16_t milliVolts,
    uint8_t status,
    uint8_t balancing
  ){
  bmscommsDataArr[0] = ((milliVolts - BMSCOMMS_MILLIVOLT_OFFSET) >> 5) | 0xC0;
  bmscommsDataArr[1] = (milliVolts - BMSCOMMS_MILLIVOLT_OFFSET) & 0x1F | (0x5 << 5);
  bmscommsDataArr[2] = (0x2 << 5) | ((status & 0x7) << 2) | (balancing & 0x3);
  return bmscommsDataArr;
}

uint8_t BMSCommsSender::calculate_status_byte(void){
  if (_CellComms.overVoltageNum() > 0) {
    return BMSCOMMS_STATUS_OVER_VOLTAGE;
  } else if (_CellComms.overTemperatureNum() > 0){
    return BMSCOMMS_STATUS_OVER_TEMP;
  } else if (_CellComms.underVoltageNum() > 0){
    return BMSCOMMS_STATUS_UNDER_VOLTAGE;
  } else {
    return BMSCOMMS_STATUS_OK;
  }
}

uint8_t BMSCommsSender::calculate_balancing_byte(void){
  uint8_t balancing_num = _CellComms.balancingNum();
  if (balancing_num == _CellComms.cellNum){
    return BMS_BALANCING_ALL;
  } else if (balancing_num > 0){
    return BMS_BALANCING_SOME;
  } else {
    return BMS_BALANCING_NONE;
  }
}
