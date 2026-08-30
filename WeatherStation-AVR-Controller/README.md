# 🌦️ Weather Monitoring & Data Logging Station

### AVR Embedded Systems Graduation Project — Team 3

---

<p align="center">

**ATmega32 | Embedded C | Layered Architecture | ADC | EEPROM Logging | UART Data Dump**

</p>

---

# 🚀 Message from the Team Leader

**Hello Team,**

Welcome to the **Weather Monitoring & Data Logging Station** project! Our objective is to develop an environmental monitoring system that continuously reads sensor data (temperature and light), displays real-time status locally, logs historical data into EEPROM, raises threshold alarms, and dumps the logged data to a PC over UART.

We implement a professional **Layered Architecture (MCAL, HAL, APP)** with clean, reusable drivers, exactly like professional embedded teams do.

**Important Note:** Before we move to the final build, we design and simulate the entire circuit using **Proteus Professional**. This will help us test our firmware safely and ensure everything is connected properly.

*— Abdelrahman Mohamed Ibrahim, Team Leader*

---

# 📋 Project Overview

Develop an environmental monitoring system that continuously reads sensor data (temperature and light), displays real-time updates, logs historical data, and triggers alarms if thresholds are exceeded.

# ✨ Key Features

| # | Feature | Description | Module(s) Used |
|---|---------|-------------|----------------|
| 1 | Real-Time Sensor Reading | Continuously read temperature (LM35) and light (LDR) via ADC | Adc, LM35, Ldr |
| 2 | Local Status Display | Show live readings and system state on 16x2 LCD | Lcd |
| 3 | Data Logging & Retrieval | Store periodic readings in EEPROM and retrieve them on demand | Eeprom |
| 4 | Threshold Alarms | Trigger buzzer when readings exceed configured limits | Buzzer, Exti |
| 5 | PC Communication for Data Dump | Send the logged data to a PC terminal over serial | Uart |

# 🧩 Embedded Concepts Applied

ADC — LCD — EEPROM — UART — Timers — Interrupts

---

# 🏗️ System Architecture (Layered)

```
┌──────────────────────────────────────────────┐
│                  APP Layer                   │
│  Weather_App: sampling schedule, alarm logic │
│  logging, UART commands (D = dump, C = clear)│
├──────────────────────────────────────────────┤
│                  HAL Layer                   │
│        Lcd │ LM35 │ Ldr │ Buzzer             │
├──────────────────────────────────────────────┤
│                 MCAL Layer                   │
│  Dio │ Adc │ Uart │ Timer │ Eeprom │ Exti    │
├──────────────────────────────────────────────┤
│                Common                        │
│              Definition.h                    │
└──────────────────────────────────────────────┘
                    ATmega32
```

# 📁 Repository Structure

```
WeatherStation-AVR-Controller/
│
├── Demo video/          → Final project demo video
├── HardwareDesign/      → Proteus simulation & wiring diagrams
├── Presention/          → Project presentation slides
│
└── Src/
    ├── main.c           → Entry point (superloop)
    ├── Common/          → Definition.h (shared types & constants)
    ├── APP/             → Application logic
    │   └── Weather_App.c/.h
    ├── HAL/             → Hardware Abstraction Layer
    │   ├── Lcd/         → 16x2 display driver (4-bit mode)
    │   ├── LM35/        → Temperature sensor driver
    │   ├── Ldr/         → Light sensor driver
    │   └── Buzzer/      → Alarm actuator driver
    └── MCAL/            → Microcontroller Abstraction Layer
        ├── Dio/         → Digital input/output
        ├── Adc/         → Analog-to-digital converter
        ├── Uart/        → Serial communication (PC dump)
        ├── Timer/       → Timer0 CTC 1ms system tick
        ├── Eeprom/      → Data logging storage
        └── Exti/        → External interrupts (INT0/INT1/INT2)
```

> Every driver module follows the standard 4-file convention:
> `Module_Config.h` • `Module_Interface.h` • `Module_Private.h` • `Module_Program.c`

---

# 🔌 System Pin Mapping

| Port / Pin | Connected To |
|------------|--------------|
| PA0 | LM35 temperature sensor (ADC channel 0) |
| PA1 | LDR light sensor (ADC channel 1) |
| PB0 / PB1 | LCD RS / EN |
| PB4 – PB7 | LCD data (4-bit mode) |
| PC0 | Buzzer |
| PD2 | Dump button (INT0, rising edge) |
| PD3 | Mute button (INT1, falling edge) |

---

# 👥 Team Members & Task Division

| Member | Role | Suggested Responsibility |
|--------|------|--------------------------|
| Abdelrahman Mohamed Ibrahim | Team Leader | APP layer, integration, pin mapping review |
| Abdelrahman Ibrahim adelbary | Member | MCAL: Dio, Adc, Eeprom |
| Youssef mohamed ghaith | Member | MCAL: Uart, Timer, Exti |
| Mohamed Raafat Hassan | Member | HAL: Lcd, LM35, Ldr, Buzzer + Proteus design |

---

# 🗓️ Milestone Plan

| Phase | Deliverable | Target Date |
|-------|-------------|-------------|
| 0 | Repo created, work divided, README read | Aug 29, 2026 |
| 1 | Layered architecture + Common files + pin mapping pushed | Aug 30, 2026 |
| 2 | MCAL drivers implemented | Sep 1, 2026 |
| 3 | HAL drivers implemented | Sep 3, 2026 |
| 4 | APP: real-time reading + local display | Sep 4, 2026 |
| 5 | Data logging & retrieval + threshold alarms | Sep 5, 2026 |
| 6 | PC communication data dump + integration | Sep 6, 2026 |
| 7 | Demo video, presentation, final review | Sep 8, 2026 |

---

# ⚙️ Build & Simulation

```
avr-gcc -mmcu=atmega32 -Os -I Src -o main.elf Src/main.c Src/APP/*.c Src/HAL/*/*.c Src/MCAL/*/*.c
avr-objcopy -O ihex main.elf main.hex
```

- **MCU:** ATmega32 (F_CPU = 8 MHz)
- **Toolchain:** avr-gcc + Proteus Professional / SimulIDE
- **Terminal (data dump):** any serial monitor at 9600 baud
  - `D` → dump the log as CSV, `C` → clear the log

---

# 📜 License

Distributed under the MIT License. See `LICENSE` for more information.
