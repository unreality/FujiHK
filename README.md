Fujitsu AirConditioner Controller for HomeKit
----------
Flash to an [M5Atom](https://shop.m5stack.com/collections/atom-series/products/atom-lite-esp32-development-kit), and add your Fujitsu AirConditioner (Heatpump) to your HomeKit home. Should work with most other ESP32 kits as well.

Quick start
-----------

* Clone the repository
* Open repository in PlatformIO
* Build and Upload
* Open Serial Monitor
* Enter 'S <HOMEKIT PIN>' to define the HomeKit pairing pin (eg 'S 11122333')
* Enter 'W' to enter WiFi connection details
* Connect the M5Atom to the AirConditioner via the 3-wire interface (see example circuit) or via the com connector on the indoor unit (will need a logic level converter)
* Power-Cycle your air conditioner

Status LED
----------
- Yellow: 
  - Pulsing: WiFi Details Required
  - Flashing: WiFi Connecting
  - Solid: Wifi Connected
- Magenta:
  - Pulsing: Waiting to pair with HomeKit
- Blue:
  - Solid: Update pending send
- Red:
  - Pulsing: Not bound to the indoor unit
- Green: 
  - Solid: Bound to an indoor unit and processing frames

Secondary Mode
--------------

By default the controller binds to the indoor unit as a secondary controller. If you do not have an existing wall remote controller, you will need to edit FujiHeatPump initialisation to bind as a primary controller.

QR Code
-------

You can generate a QR code to scan with Home.app by using the [QR code generator tool](https://github.com/maximkulkin/esp-homekit/tree/master/tools)

```#  python3 gen_qrcode 21 111-22-333 FUJI output.png```

Example Circuit
---------------
<img src="https://github.com/unreality/FujiHK/blob/master/example-circuit.png"/>

Other ESP Boards
----------------

This controller should work fine on other ESP boards, with the following setup:
- GPIO 19 - LIN RX
- GPIO 22 - LIN TX 
- GPIO 27 - NeoPixel Compatible LED (SK6812/WS2812C/etc)

Parts Required
--------------
- LIN Tranceiver
  - MCP-2025-330 (or similar)
  - http://ww1.microchip.com/downloads/en/DeviceDoc/20002306B.pdf
- 10uF Capacitor
- 10k Resistor
- 12v -> 3.3v (500mA+) voltage regulator
  - https://www.pololu.com/product/2842

