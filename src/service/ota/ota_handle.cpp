#include "ota_handle.h"

// Global variables
AsyncWebServer ota_server(OTA_SERVER_PORT);
unsigned long ota_start_time = 0;

void ota_init(void) 
{
    Serial.println("Starting OTA mode...");
    
    
}

void ota_start(void) 
{
    // Root page with integrated upload form
    ota_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<!DOCTYPE html><html><head>";
        html += "<title>Smart Weight Scale OTA</title>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<style>";
        html += "body{font-family:Arial;text-align:center;margin:20px;background:#f0f0f0;}";
        html += ".container{max-width:400px;margin:0 auto;background:white;padding:20px;border-radius:8px;box-shadow:0 2px 8px rgba(0,0,0,0.1);}";
        html += "h1{color:#333;margin-bottom:15px;}";
        html += "input[type=file]{margin:10px 0;width:100%;}";
        html += "button{background:#007bff;color:white;border:none;padding:10px 20px;border-radius:4px;cursor:pointer;width:100%;margin:5px 0;}";
        html += "button:hover{background:#0056b3;}";
        html += "progress{width:100%;height:15px;margin:10px 0;}";
        html += "</style></head><body>";
        html += "<div class='container'>";
        html += "<h1>Smart Weight Scale</h1>";
        html += "<h3>OTA Update</h3>";
        
        // Firmware upload form
        html += "<form id='fw-form' enctype='multipart/form-data'>";
        html += "<p>Select Firmware (.bin):</p>";
        html += "<input type='file' name='firmware' accept='.bin'>";
        html += "<button type='submit'>Update Firmware</button>";
        html += "</form>";
        
        // Progress display
        html += "<div id='progress' style='display:none'>";
        html += "<p id='status'>Starting upload...</p>";
        html += "<progress id='progressbar' value='0' max='100'></progress>";
        html += "</div>";
        
        html += "<p><small>Timeout: " + String(OTA_TIMEOUT_MS/60000) + " min</small></p>";
        html += "</div>";
        
        // Simplified JavaScript
        html += "<script>";
        html += "document.getElementById('fw-form').onsubmit = function(e) {";
        html += "  e.preventDefault();";
        html += "  const file = this.firmware.files[0];";
        html += "  if (!file) { alert('Select a file!'); return; }";
        html += "  const xhr = new XMLHttpRequest();";
        html += "  const formData = new FormData();";
        html += "  formData.append('update', file);";
        html += "  document.getElementById('progress').style.display = 'block';";
        html += "  xhr.upload.onprogress = function(e) {";
        html += "    if (e.lengthComputable) {";
        html += "      const percent = Math.round((e.loaded / e.total) * 100);";
        html += "      document.getElementById('progressbar').value = percent;";
        html += "      document.getElementById('status').innerText = 'Upload: ' + percent + '%';";
        html += "    }";
        html += "  };";
        html += "  xhr.onload = function() {";
        html += "    if (xhr.status === 200) {";
        html += "      document.getElementById('status').innerText = 'Success! Rebooting...';";
        html += "    } else {";
        html += "      document.getElementById('status').innerText = 'Failed: ' + xhr.responseText;";
        html += "    }";
        html += "  };";
        html += "  xhr.open('POST', '/update');";
        html += "  xhr.send(formData);";
        html += "};";
        html += "</script>";
        
        html += "</body></html>";
        
        request->send(200, "text/html", html);
    });
    
    // Update handling endpoint
    ota_server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
        bool shouldReboot = !Update.hasError();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot ? "OK" : "FAIL");
        response->addHeader("Connection", "close");
        request->send(response);
        if (shouldReboot) {
            delay(1000);
            ota_end();
        }
    }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        if (index == 0) {
            Serial.printf("Update: %s\n", filename.c_str());
            #if defined(ESP8266)
                Update.runAsync(true);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin(maxSketchSpace, U_FLASH)) {
            #elif defined(ESP32)
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) {
            #endif
                    Update.printError(Serial);
                }
        }
        
        if (Update.write(data, len) != len) {
            Update.printError(Serial);
        }
        
        if (final) {
            if (Update.end(true)) {
                Serial.printf("Update Success: %u bytes\n", index + len);
            } else {
                Update.printError(Serial);
            }
        }
    });
    
    // Start server
    ota_server.begin();
    Serial.println("OTA Web Server started");
    
    ota_start_time = millis();
    
    Serial.println("=== OTA MODE ACTIVE ===");
    Serial.printf("Timeout: %d minutes\n", OTA_TIMEOUT_MS / 60000);
}

void ota_loop(void)
{
    while (true)
    {
        delay(1);
        // Check timeout
        if ((millis() - ota_start_time) > OTA_TIMEOUT_MS) 
        {
            Serial.println("OTA timeout reached, exiting OTA mode");
            ota_end();
        }
    }
}

void ota_end(void)
{
    ota_server.end();
    Serial.println("OTA Web Server stopped");
    Serial.println("Restarting device...");
    ESP.restart();
}