////////////////// Web
//#include <ESPAsyncTCP.h>
#include <ESPAsyncWebSrv.h>

////////////////// Ota
#include <AsyncElegantOTA.h>
AsyncWebServer server(80);        // OTA Web

////////////////// Scale
#include <HX711.h>
HX711 scale0, scale1, scale2;     // 3 Scale
scale0_clk =  2; scale0_data =  0;  // Scale 1 pin
scale1_clk = 14; scale1_data = 12;  // Scale 2 pin
scale2_clk = 13; scale2_data = 15;  // Scale 3 pin   
float raw[6], tear[6];


////////////////// Batt
const int battPin = A0;       // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;          // Value read from the pot
int previousSensorValue = 0;  // Declare previousSensorValue here

////////////////// Button
const int button1 = 16;      // The number of the pushbutton pin
const int button2 = 3;      // The number of the pushbutton pin
int previousButtonState = 0;  // Declare previousButtonState here

uint32_t loop_timer;                // Timer
uint32_t window_timer = 4000;

void setup() {
  Serial.begin(115200);
  
  scale_setup();
  button_setup();
  
  loop_timer = micros();
  //ota(); 
}

void loop() {
  sensorValue = analogRead(battPin);

  if (sensorValue != previousSensorValue || digitalread(button1) != previousButtonState) {
    Serial.print(map(sensorValue, 0, 864, 0, 100));
    Serial.print("Button:");
    Serial.print(digitalread(button1) ? "ON" : "OFF");
  }

  previousSensorValue = sensorValue;
  //previousButtonState = digitalread(button1);
  readSensors();

  while (micros() - loop_timer < window_timer);           // 250hz windows
  loop_timer = micros();
}

void readSensors() {
  for (int i = 0; i < 10; i++) {
    scale0.set_gain(64);
    r[1] = scale0.read();  // read raw r1
    Serial.print(r[1]);
    Serial.print(" ");
    scale1.set_gain(64);
    r[2] = scale1.read();  // read raw r3
    Serial.print(r[2]);
    Serial.print(" ");
    scale2.set_gain(64);
    r[3] = scale2.read();  // Read r r2
    Serial.print(r[3]);
    Serial.print(" ");
    scale0.set_gain(32);
    r[4] = scale0.read();  // Read r r4
    Serial.print(r[4]);
    Serial.print(" ");
    scale1.set_gain(32);
    r[3] = scale1.read();  // Read r r5
    Serial.print(r[5]);
    Serial.print(" ");
    scale2.set_gain(32);
    r[4] = scale2.read();  // Read r r6
    Serial.print(r[6]);
    Serial.println(" ");
    delay(50);
  }
}

void resetSensors() {
  /*
  t1 = r1;
  t2 = r2;
  t3 = r3;
  t4 = r4;      
  Serial.println("Tear Done..");
  */
}
