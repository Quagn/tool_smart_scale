void ota() {
  while (){
    if (micros() - loop_timer > 15e6) {       // wait 10s to OTA "if no receive"
      WiFi.mode(WIFI_STA);                    // start wifi connect
      WiFi.begin("MinPhone", "11223344");     // wifi ssid and pass

      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->send(200, "text/plain", "ESP8266 OTA.");
      });

      AsyncElegantOTA.begin(&server);
      server.begin();
      while (true) delay(1);                          // stay in OTA "delay(1) to bypass watchdog"
    }
    delay(1);
  }
}
