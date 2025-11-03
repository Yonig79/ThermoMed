Thermal Stability Report – Peltier-Controlled System

Prepared by: Yoniel Gutierrez Gomez (yoni) Date: October 2025

System Type: Peltier-based thermal regulation with PWM control Evaluation Count: 45 cycles

1. Objective:
   This report documents the thermal performance of a temperature-controlled system using Peltier cells(TEC1-12704K12). The system was evaluated over 45 cycles to assess its stability, error margins, and control logic effectiveness. Each cycle includes a decision outcome, average deviation, and average error. One cycle also includes power consumption data.
2. Control Strategy:
   The system uses conditional logic to determine PWM output based on temperature and thermal state (Positive, Negative, Normal). This approach was selected over PID control due to:

1-Nonlinear thermal response of Peltier cells.

2-Thermal lag and saturation zones.

3-Environmental noise sensitivity.

4-Easier calibration and predictable behavior.



Evaluation Methodology:



Each cycle records:

1-Decision: System’s thermal state (all were "Normal").

2-Average Deviation: Mean temperature fluctuation from target.

3-Average Error: Estimated error margin based on sample comparison.

4-Power Consumption: Recorded once over a 30-minute interval.

(Test Medium: 20 mL of water, selected to simulate a compact thermal load. This volume is approximately equivalent to 6.67 NovoLog insulin cartridges (each containing 3 mL), making it relevant for medical-grade cooling applications).



4. Data Summary
   Evaluation	Decision	Avg. Deviation (°C)  Avg. Error (°C)	Avg. Power (30 min)
   1–45	         Normal	           0.15–0.24	     ±0.24–±0.36	 41.94 W (once)



1. Performance Analysis:
   Stability: All 45 evaluations resulted in "Normal" decisions, indicating consistent thermal control.

Deviation Range: 0.15 °C to 0.24 °C — tight and predictable.



Error Range: ±0.24 °C to ±0.36 °C — well within acceptable limits.



Power Efficiency: One reading showed 41.94 W over 30 minutes, suggesting moderate energy use under stable conditions.



6. Justification for Conditional Logic
   The system avoids PID control due to:

&nbsp;  Nonlinear behavior of Peltier cells (as shown in the equation):

&nbsp;   𝑄=𝛼⋅𝑇𝑐⋅𝐼−1/2\*𝐼^2−𝐾⋅(𝑇ℎ−𝑇𝑐);

1 -Thermal inertia and delayed response.
2 -Risk of oscillation or overcorrection with PID.
3 -Simplified tuning and robust performance with logic tables.

Where:
𝑄: Heat absorbed (watts)
𝛼: Seebeck coefficient
𝑇𝑐: Cold side temperature
𝐼: Electrical current
𝑅: Internal resistance
𝐾: Thermal conductance
𝑇ℎ:Hot side temperature



7. Recommendations:

Expand power monitoring across more cycles to assess energy efficiency trends.

Consider PCM (Phase Change Material) integration to improve passive thermal stability. PCMs absorb or release latent heat during phase transitions (e.g., solid ↔ liquid), helping maintain temperature without active cooling. Materials such as paraffin wax or fatty acids are commonly used in compact systems.

Automate deviation/error logging for real-time diagnostics.

Explore hybrid control (logic + adaptive PID) for future iterations.

Evaluate the integration of lithium battery backup systems. Given the average power consumption of ~40 W over 30 minutes, a compact Li-ion pack could provide short-term autonomy in case of power interruptions, enhancing reliability for portable or medical applications.



8. Conclusion

The system demonstrated excellent thermal stability across all 45 evaluations. The use of conditional logic proved effective and reliable, avoiding the complexities of PID control. The data supports continued use of this strategy in similar thermal applications, especially where compact and consistent cooling is required.





