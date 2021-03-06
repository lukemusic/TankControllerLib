#include "Devices/SD_TC.h"

//  class variables
SDClass_TC* SDClass_TC::_instance = nullptr;

//  class methods
/**
 * accessor for singleton
 */
SDClass_TC* SDClass_TC::instance() {
  if (!_instance) {
    _instance = new SDClass_TC();
  }
  return _instance;
}

//  instance methods
/**
 * Constructor sets pins, dimensions, and shows splash screen
 */
SDClass_TC::SDClass_TC() : SDClass() {
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  // TODO: Need to re-enable this for the physical device
  // begin(4);
}

void SDClass_TC::printRootDirectory() {
  File root = open("/");
  printDirectory(root, 0);
}

void SDClass_TC::printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println(F("/"));
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print(F("\t\t"));
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
