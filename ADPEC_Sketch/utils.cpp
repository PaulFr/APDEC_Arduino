#include "utils.h"

String dump_byte_array(byte *buffer, byte bufferSize) {

  String id = ""; 
  for (byte i = 0; i < bufferSize; i++) {
    id += String(buffer[i], HEX);
  }
  return id;
}
