# pid-temperature-control
A temperature control system using PID logic and a Peltier cell, designed to maintain stable cooling for sensitive materials like insulin. Includes a high-precision MCP9808 sensor, MOSFET power control, and a custom PCB designed in EasyEDA.
# PID Temperature Control System

# PID Temperature Control System

This project is a temperature control system using PID logic and a Peltier cell. It is designed to maintain stable cooling around 6 °C for sensitive materials such as insulin.

## Components
- MCP9808 temperature sensor  
- TEC1-12704 Peltier cell  
- IRLB8721 MOSFET  
- Arduino microcontroller  
- SH1106 OLED display (128x64)  
- Custom PCB (designed in EasyEDA)

## User Interface

This system includes a SH1106 OLED display (128x64) to provide real-time feedback to the user. The screen shows:

- Current temperature readings from the MCP9808 sensor  
- PID status indicators (e.g., Cooling, Stable, Overheat)  
- Optional debug messages for system tuning

The display is connected via I2C to the microcontroller and uses the U8g2 library for rendering text and graphics. This interface allows users to monitor the system without needing a computer, making it ideal for portable or standalone applications such as insulin storage.

## Status
Prototype in progress. PCB design completed. Code under testing.

## Technologies Used
- Arduino (C/C++)  
- EasyEDA  
- Embedded systems  
- Power electronics

## Author
Yoni — Electronics technician and freelance developer
