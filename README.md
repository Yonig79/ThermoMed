Temperature-Control-System



A temperature control system using decision-based logic and a Peltier cell, designed to maintain stable cooling for sensitive materials like insulin. Includes a high-precision MCP9808 sensor, MOSFET power control, and a custom PCB designed in EasyEDA.

This project is a temperature control system using adaptive decision logic and a Peltier cell. It is designed to maintain stable cooling around 6 °C for sensitive materials such as insulin.



Model Capacity
⦁ The enclosure is designed for a volume of approximately 0.7 liters  
⦁ Ideal for storing small vials, insulin pens, or temperature-sensitive samples



Components


⦁ MCP9808 temperature sensor  
⦁ TEC1-12704 Peltier cell  
⦁ IRLB8721 MOSFET  
⦁ ESP32 microcontroller  
⦁ SH1106 OLED display (128x64, SPI interface)  
⦁ Custom PCB (designed in EasyEDA)



User Interface


This system includes a SH1106 OLED display (128x64) to provide real-time feedback to the user. The screen shows:
⦁ Current temperature readings from the MCP9808 sensor  
⦁ "Ready" indicator when temperature is below 8 °C  
⦁ No debug messages or control status shown to the user



The display is connected via SPI to the microcontroller and uses the U8g2 library for rendering text. This interface allows users to monitor the system without needing a computer, making it ideal for portable or standalone applications such as insulin storage.

Control Logic


⦁ Soft-start ramp gradually increases PWM until control begins  
⦁ Every 60 seconds, the system evaluates temperature deviation  
⦁ Decision logic adjusts PWM based on deviation:

* "Positive" → stronger cooling
* "Negative" → softer cooling
* "Normal" → balanced response  
  ⦁ PWM values are mapped to temperature ranges for precise control  
  ⦁ Buzzer alert activates when temperature reaches 6 °C



Note: The system performs a full thermal evaluation every 60 seconds, but PWM is updated every second based on the current temperature and the latest decision



Thermal Performance
⦁ The system maintains temperature around 6 °C with acceptable thermal deviation  
⦁ Control logic ensures fluctuations remain within a narrow and safe range  
⦁ Suitable for applications requiring stable cooling without complex PID tuning

Status


Prototype in progress. Firmware stable and tested.  
The system is also in continuous improvement to enhance performance and reliability.
Hardware Design
The schematic and PCB layout are currently in progress and will be added to this repository soon.



Technologies Used
⦁ ESP32 (C++)  
⦁ EasyEDA  
⦁ Embedded systems  
⦁ Power electronics

Author
Yoniel Gutierrez Gomez (Yoni)— Electronics technician and freelance developer

