# OpenRGB GG Effects

A standalone, device-agnostic OpenRGB effects plugin project. **No RGB controller or keyboard-specific HID driver is bundled.**

## Architecture
- OpenRGB owns device discovery, controller communication and LED writes.
- This project owns animation rendering, effect presets, geometry adapters and reactive keyboard input.
- Physical keypress monitoring is **automatically enabled when a reactive effect is selected**, without an opt-in checkbox. Input access failures are reported, not bypassed.
- Linux key events are read passively without EVIOCGRAB. Do not store key sequences or typed text. Keyboard mapping must be scoped to the selected OpenRGB device wherever possible.
- Unsupported platforms and missing permissions must degrade gracefully; no claim of cross-platform keypress support yet.

## Status
This repository currently contains an **offline C++17 effect-core foundation**, not a loadable OpenRGB plugin. It has no controller code, hardware writes or device hooks. Plugin API integration, layout mapping, Qt UI and live reactive input remain pending.

The original Apex Pro Mini OpenRGB controller remains a separate project: https://github.com/newnetmp3/OpenRGB-ApexProMini

Historical SteelSeries GG-inspired presets are independently reconstructed and are not guaranteed identical to proprietary vendor shaders. This project is not affiliated with SteelSeries or OpenRGB.

## Offline test
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

See [docs/ROADMAP.md](docs/ROADMAP.md) and [docs/HANDOVER.md](docs/HANDOVER.md).
