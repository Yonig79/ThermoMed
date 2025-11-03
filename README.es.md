Sistema de Control de Temperatura

Un sistema de control de temperatura basado en lógica de decisión y una celda Peltier, diseñado para mantener una refrigeración estable en materiales sensibles como la insulina. Incluye un sensor MCP9808 de alta precisión, control de potencia con MOSFET y una PCB personalizada diseñada en EasyEDA.

Capacidad del Modelo

* El gabinete está diseñado para un volumen de aproximadamente 0.7 litros
* Ideal para almacenar frascos pequeños, lapiceras de insulina o muestras sensibles a la temperatura

Componentes

* Sensor de temperatura MCP9808
* Celda Peltier TEC1-12704
* MOSFET IRLB8721
* Microcontrolador ESP32
* Pantalla OLED SH1106 (128×64, interfaz SPI)
* PCB personalizada (diseñada en EasyEDA)

Interfaz de Usuario

Este sistema incluye una pantalla OLED SH1106 (128×64) para proporcionar información en tiempo real al usuario. La pantalla muestra:

* Lecturas actuales de temperatura del sensor MCP9808
* Indicador "Ready" cuando la temperatura está por debajo de 8 °C
* No se muestran mensajes de depuración ni estados de control al usuario

La pantalla está conectada vía SPI al microcontrolador y utiliza la biblioteca U8g2 para renderizar texto. Esta interfaz permite al usuario monitorear el sistema sin necesidad de una computadora, lo que la hace ideal para aplicaciones portátiles o autónomas como el almacenamiento de insulina.

Lógica de Control

* El arranque suave incrementa gradualmente el PWM hasta que comienza el control
* Cada 60 segundos, el sistema evalúa la desviación térmica
* La lógica de decisión ajusta el PWM según la desviación:

  * "Positive" → enfriamiento más fuerte
  * "Negative" → enfriamiento más suave
  * "Normal" → respuesta equilibrada

* Los valores PWM se asignan a rangos de temperatura para un control preciso
* Se activa una alerta sonora cuando la temperatura alcanza los 6 °C

Nota: El sistema realiza una evaluación térmica completa cada 60 segundos, pero el PWM se actualiza cada segundo según la temperatura actual y la última decisión.

Rendimiento Térmico

* El sistema mantiene la temperatura alrededor de 6 °C con una desviación térmica aceptable
* La lógica de control garantiza que las fluctuaciones se mantengan dentro de un rango estrecho y seguro
* Adecuado para aplicaciones que requieren refrigeración estable sin necesidad de ajuste PID complejo

Estado del Proyecto

* Prototipo en desarrollo
* Firmware estable y probado
* Mejoras continuas en marcha para optimizar el rendimiento y la confiabilidad





Informe de Evaluación:



45 thermal cycles analyzed / 45 ciclos térmicos analizados.

Average deviation: 0.15–0.24 °C / Desviación promedio: 0.15–0.24 °C.

Average error: ±0.24–±0.36 °C / Error promedio: ±0.24–±0.36 °C.

Power consumption: ~40 W over 30 minutes / Consumo de energía: ~40 W en 30 minutos.

Test volume: 20 mL (≈6.67 NovoLog insulin cartridges).

Volumen de prueba: 20 mL (≈6.67 cartuchos de insulina NovoLog).



Archivos de Diseño de Hardware:



Gerber Files / Archivos Gerber.

Bill of Materials (BOM) / Lista de materiales (BOM).

PCB Layout / Diseño de PCB.

Schematic Diagrams / Diagramas esquemáticos.



Mejoras futuras:



&nbsp;Respaldo con batería de litio.

&nbsp;Integración de material de cambio de fase (PCM).

&nbsp;Lógica de control híbrida.



📄 Read full report / 📄 Leer informe completo.





Tecnologías Utilizadas

* ESP32 (C++)
* EasyEDA
* Sistemas embebidos
* Electrónica de potencia

Autor

Yoniel Gutierrez Gomez (Yoni) — Técnico electrónico y desarrollador freelance

