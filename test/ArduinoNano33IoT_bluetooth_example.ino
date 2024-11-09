#include <ArduinoBLE.h>

BLEService controlService("12345678-1234-5678-1234-56789abcdef0");  
BLEByteCharacteristic controlChar("abcdef01-1234-5678-1234-56789abcdef0", BLERead | BLEWrite | BLENotify);

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Nano33IoT");  
  BLE.setAdvertisedService(controlService);  
  controlService.addCharacteristic(controlChar);  
  BLE.addService(controlService);  
  controlChar.writeValue((byte)0);  // Set initial value as a byte

  BLE.advertise();  
  Serial.println("Waiting for a connection...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Connected to central device!");

    while (central.connected()) {
      if (controlChar.written()) {
        byte value = controlChar.value();  // Read the byte directly
        Serial.print("Received byte: ");
        Serial.println(value);

        switch (value) {
          case 0:
            Serial.println("Command 0 received");
            break;
          case 1:
            Serial.println("Command 1 received");
            break;
          case 2:
            Serial.println("Command 2 received");
            break;
          case 3:
            Serial.println("Command 3 received");
            break;
          default:
            Serial.println("Unknown command received");
            break;
        }
      }
    }
    Serial.println("Disconnected from central device!");
  }
}
