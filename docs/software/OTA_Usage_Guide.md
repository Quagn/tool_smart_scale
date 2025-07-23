# OTA (Over-The-Air) Update Guide

## Overview

The Smart Weight Scale supports wireless firmware updates through OTA (Over-The-Air) functionality. This guide explains how to use this feature.

## How OTA Works

The OTA system in the Smart Weight Scale works as follows:

1. When triggered, the device will first attempt to connect to a known WiFi network (STA mode) for 20 seconds
2. If connection fails, it will create its own WiFi access point (AP mode)
3. The user connects to the device's web interface to upload new firmware
4. After successful update, the device will automatically restart with the new firmware

## Activating OTA Mode

OTA mode can be activated by:

1. Holding the designated button for 5 seconds (BUTTON_OTA_HOLD_TIME)
2. Calling the `ota_start()` function from your code

## Connecting to OTA

### If device connects to your WiFi (STA mode):

1. The device will connect to the configured WiFi network (WIFI_STA_SSID)
2. Look for the device's IP address in your router's connected devices list or in the serial monitor
3. Open a web browser and navigate to: `http://<device-ip>/update`

### If device creates its own WiFi (AP mode):

1. Connect your computer or mobile device to the WiFi network named `SmartScale_OTA`
2. Password: `ota123456`
3. Open a web browser and navigate to: `http://192.168.4.1/update`

## Uploading Firmware

1. In the web interface, click "Choose File" to select your compiled firmware (.bin file)
2. Click "Update" to begin the upload process
3. Wait for the upload to complete (do not disconnect during this process)
4. The device will automatically restart with the new firmware

## Timeout

The OTA mode will automatically exit after 5 minutes (OTA_TIMEOUT_MS) if no update is performed.

## Code Example

```cpp
// Example of triggering OTA mode from your code
void enterOtaMode() {
    // Save any important data before entering OTA mode
    saveSettings();
  
    // Start OTA mode
    ota_start();
  
    // Main loop during OTA mode
    while (true) {
        ota_handle();  // Must be called regularly to handle OTA operations
        delay(10);
    }
}
```

## Customizing OTA Settings

You can customize OTA settings in the following files:

1. `src/config/peripheral_config.h` - WiFi credentials, timeout settings
2. `src/config/web_config.h` - Web server configuration
3. `src/service/ota/ota_handle.h` - OTA function declarations

## Troubleshooting

1. **Cannot connect to device in AP mode**

   - Make sure you're connecting to the correct WiFi network (SmartScale_OTA)
   - Try restarting the device and activating OTA mode again
2. **Upload fails**

   - Ensure you're uploading a valid firmware file (.bin)
   - Check that the file size is not too large for the device
   - Try reconnecting to the WiFi network and uploading again
3. **Device not responding after update**

   - If the device doesn't restart properly after an update, try manually resetting it
   - If issues persist, you may need to use serial programming to restore firmware
