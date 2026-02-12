# Ascent API Reference

Full API documentation is generated from Doxygen comments in the source headers.

## Generating

```bash
./scripts/generate_docs.sh
```

The HTML output is placed in `build/docs/html/index.html`.

## Key Types

### `ascent::core::Result<T>`

Error-handling wrapper returned by all fallible operations.

```cpp
auto result = sensor.read();
if (result.ok())
{
    auto value = result.value();
}
else
{
    auto code = result.status();
}
```

### `ascent::core::StatusCode`

Enumeration of all error codes used throughout the system.

| Value | Meaning |
|---|---|
| `Ok` | Operation succeeded |
| `Error` | Generic failure |
| `Timeout` | Operation timed out |
| `Busy` | Resource busy |
| `InvalidParam` | Invalid argument |
| `HardwareFault` | Hardware-level error |
| `NotReady` | Device not initialized |
| `OutOfMemory` | Allocation failure |
| `NotSupported` | Feature unavailable |

### `ascent::core::Vec3f`

3D vector (x, y, z) used for accelerometer, gyroscope, and magnetometer data.

### `ascent::core::Quaternion`

Orientation quaternion (w, x, y, z) used for attitude estimation.

## Module APIs

See the respective header files under `modules/*/include/` for the full API surface:

- **Navigation**: `NavigationSystem`, `KalmanFilter1D`, `AttitudeEstimator`, `AltitudeEstimator`
- **Propulsion**: `PropulsionController`, `IgnitionSequence`, `ValveController`, `ThrustMonitor`
- **Communication**: `RadioLink`, `CommandParser`, `ProtocolHandler`
- **Telemetry**: `TelemetryManager`, `PacketFormatter`, `DataLogger`
- **Safety**: `SafetyMonitor`, `HealthMonitor`, `AbortController`, `RangeSafety`
