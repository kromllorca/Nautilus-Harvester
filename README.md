# 🌊 Nautilus Harvester

**A self-powered hybrid energy harvesting smart buoy for environmental monitoring in the Venice Lagoon.**

Bachelor's Thesis in Industrial Engineering — Università degli Studi di Padova, Department of Industrial Engineering (DII)
Author: **Krom Llorca Lloret** · Supervisor: Prof. Damiano Varagnolo · A.Y. 2025–2026 · Grade: **30 e lode / 30**

📄 [Read the full thesis (PDF)](docs/Nautilus_Harvester_Thesis.pdf)

---

## The problem

The Venice Lagoon needs continuous, real-time monitoring (Acqua Alta, salinity, boat-induced wake wash or *moto ondoso*), but battery-powered sensor nodes require frequent maintenance trips that are costly and harmful to a protected ecosystem. The lagoon is also extremely shallow (1–2 m) with weak currents (0.04–0.06 m/s), which rules out conventional turbines and oceanic wave energy converters.

## The solution

Nautilus Harvester is a buoy that powers a low-consumption ESP32 IoT sensor node from two complementary sources:

- ☀️ **Solar:** a 10 W flexible, ETFE-coated monocrystalline panel on the buoy dome.
- ⚡ **Waves:** an internal omnidirectional **electromagnetic pendulum generator** (Cardan joint + NdFeB magnets over flat copper coils) that converts wave and boat-wake motion into electricity — strongest in winter, when solar input is lowest.

<p align="center">
  <img src="images/buoy_architecture.png" width="45%" alt="Three-level buoy architecture">
  <img src="images/working_principle.png" width="50%" alt="Pendulum working principle">
</p>

## Power management — the *Nautilus Energy Hub*

Bridge rectifier + smoothing capacitor for the pendulum's AC output, Schottky diodes for source isolation, a TP4056 CC/CV Li-Ion charger, and an **Arduino-controlled MOSFET dump load** as a secondary overvoltage protection layer.

<p align="center">
  <img src="images/power_flow_schematic.png" width="70%" alt="Energy Hub power flow schematic">
</p>

## Energy budget

| Scenario | Solar yield | EMG est. yield | Net balance vs. 1 Wh/day load |
|---|---|---|---|
| Summer (sunny) | 37.5 Wh | 1–2 Wh | +38 Wh |
| Winter (cloudy) | 11.25 Wh | 3–5 Wh | +15 Wh |
| Worst case (fog) | 2.25 Wh | 4–6 Wh | +6.5 Wh |

Positive balance in every scenario; the battery alone provides 10–25 days of backup.
*EMG yield is a literature-based estimate pending experimental validation.*

## Prototyping

- **Virtual prototype** in Tinkercad to validate the safety logic of the Energy Hub.
- **Bench implementation** of the power-management subsystem: solar charging branch + Arduino monitoring and protection layer.

<p align="center">
  <img src="images/tinkercad_prototype.png" width="40%" alt="Tinkercad virtual prototype">
  <img src="images/bench_prototype.png" width="50%" alt="Bench prototype">
</p>

## Firmware

[`firmware/nautilus_energy_hub/nautilus_energy_hub.ino`](firmware/nautilus_energy_hub/nautilus_energy_hub.ino) — reads the battery voltage through a 10 kΩ/10 kΩ divider at 2 Hz and switches the dump load (IRFZ44N + 10 Ω/25 W resistor) when V_batt ≥ 4.20 V, with LED status indicators.

## Status and future work

The integration of the second harvesting source was not completed within the thesis. Next steps:

- Combine both sources on a common bus with the 1N5822 source-isolation stage and a matching charger/battery topology.
- Build the full 3D-printed hull and pendulum mechanism.
- Flume tank testing to measure the real pendulum output.
- Numerical simulation in the MBARI WEC Gazebo framework.

Approximate prototype cost: **~55–60 €**.

## Related

Related repository: [andreazerbato04/Nautilus_Marine_Energy_Harvester](https://github.com/andreazerbato04/Nautilus_Marine_Energy_Harvester)

---

*Keywords: energy harvesting · electromagnetic generator · pendulum harvester · photovoltaic · IoT · smart buoy · Arduino · Venice Lagoon*
