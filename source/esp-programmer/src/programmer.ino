/* From https://github.com/AprilBrother/cactus-micro-r2/tree/master/libraries/CactusMicro/examples/esp8266Programmer */

/**************************************************
 * Simple pass-through serial flash programmer 
 * programming the ESP8266 by an Arduino
 * 
 * This resembles the comfortable DTS controlled 
 * programming mode one have with an FTDI or similiar
 * serial connection cable, where no manual reset of
 * the ESP is needed to upload code and run it.
 * Unfortunately there is no RTS/DTS control on the
 * Arduino Serial library, so we solely rely on timing.
 *
 * If the esptool does not wait or retry long enough, 
 * you have to press the reset button
 *
 * Transmissions from the ESP are passed without any
 * modification.
 *
 *
 ***************************************************/


/*
 * connection table:
 * ESP8266  Cactus Micro Rev2
 * GPIO0    12
 * ENABLE   13
 * RX       TX
 * TX       RX
 * GND      GND
 * 
 */

const int led_pin               = 11;
const int program_pin           = 12;
const int enable_pin            = 13;

const int upload_timeout        = 5000;

unsigned long last_serial_time  = 0;

void serial1Flush(){
  while(Serial1.available() > 0) {
    (void)Serial1.read();
  }
}

void reset_esp() {
    digitalWrite(enable_pin, LOW);
    delay(1000);
    digitalWrite(enable_pin,HIGH);
    delay(1000);
    serial1Flush();
}

void setup() {
    Serial1.begin(115000);
    Serial.begin(115000);
    pinMode(enable_pin,     OUTPUT);
    pinMode(program_pin,    OUTPUT);
    pinMode(led_pin,        OUTPUT);
    digitalWrite(program_pin, LOW);

    // Reset ESP
    reset_esp();

    //while(!Serial);
    Serial.println("ESP8266 programmer ready.");
}

void loop() {
    if ((last_serial_time > 0) and (millis() - last_serial_time > upload_timeout)) {
        last_serial_time = 0;
        digitalWrite(led_pin, 0);
        reset_esp();
    }

    // pass data from ESP to host, if any
    while(Serial1.available()) {
        Serial.write(Serial1.read());
    }

    // pass data from host to ESP, if any
    if(Serial.available()) {
        while(Serial.available()) {
            char c = Serial.read();
            digitalWrite(led_pin, 1);
            last_serial_time = millis();
            Serial1.write((uint8_t)c);
        }
    }
}

