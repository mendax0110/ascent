# Ascent Architecture

## Overview

Ascent is a modular rocket avionics flight software targeting the STM32F7 Nucleo platform.
The architecture follows a strict layered design with dependency inversion at hardware boundaries.

## Layer Diagram

```
+------------------------------------------------------+
|                   Applications                       |
|  flight_controller  |  groundstation_ifc             |
+------------------------------------------------------+
|                     Modules                          |
|  navigation | propulsion | comms | telemetry | safety|
+------------------------------------------------------+
|                     Drivers                          |
|  sensors (IMU, baro, GPS, mag)                       |
|  actuators (servo, valve, pyro, igniter)             |
+------------------------------------------------------+
|              Hardware Abstraction Layer              |
|  GPIO | SPI | I2C | UART | PWM | ADC | Timer | WDG   |
+------------------------------------------------------+
|                      Core                            |
|  types | config | logger | error | events | scheduler|
+------------------------------------------------------+
```

## Dependency Rules

- Each layer may only depend on layers below it.
- The HAL exposes abstract interfaces (`ISensor`, `IActuator`, `ICommunication`, `IGpio`).
- Drivers implement these interfaces for concrete hardware.
- Modules consume driver abstractions, never raw HAL primitives.
- Applications compose modules through the scheduler.

## Key Design Decisions

| Decision | Rationale |
|---|---|
| No exceptions | Deterministic execution, reduced code size |
| `Result<T>` return type | Explicit error propagation without overhead |
| Static singletons for system services | No heap allocation, known lifetime |
| RAII for all hardware resources | Automatic cleanup on scope exit |
| Fixed-size containers | No dynamic allocation in flight-critical paths |
| Cooperative scheduler | Predictable timing, no RTOS dependency |

## Namespace Layout

| Namespace | Location |
|---|---|
| `ascent::core` | core/ |
| `ascent::hal` | hal/ |
| `ascent::drivers` | drivers/ |
| `ascent::navigation` | modules/navigation/ |
| `ascent::propulsion` | modules/propulsion/ |
| `ascent::communication` | modules/communication/ |
| `ascent::telemetry` | modules/telemetry/ |
| `ascent::safety` | modules/safety/ |
| `ascent::sim` | simulation/ |

## System States

```
Boot -> Init -> Idle -> Armed -> Launch -> Ascent -> Coast -> Apogee -> Descent -> Recovery
                  \                                                        /
                   +-----------------> Abort <----------------------------+
                                        |
                                       Fault
```

## Build Configurations

- **Native**: Desktop build for simulation and testing.
- **STM32F7**: Cross-compiled for the Nucleo-F767ZI board.
