# Roadmap
- [x] Independent C++17 color, blend, aperture and coordinate-driven effects foundation
- [x] Initial core animation and synthetic keypress-reactive render functions
- [ ] Wire offline CMake/CTest into CI and verify compile
- [ ] Port 31 historical Prism-style preset parameters and 36 regional variants from the Rust reference
- [ ] Port layered West Coast, Haze and Warp Drive scene recipes
- [ ] Implement a native OpenRGB effects plugin using compatible plugin APIs (no controller registration)
- [ ] Build OpenRGB device/LED geometry adapter with fallback for missing coordinates
- [ ] Automatic passive physical keypress discovery/monitoring when reactive effects are active; no opt-in checkbox
- [ ] Handle permission failures, device changes, unplug/reconnect and privacy-safe input routing
- [ ] Responsive Qt effects GUI, profiles and effect-specific controls
- [ ] Compare Rust/C++ snapshots and validate on real keyboards
- [ ] Package, test and release

No standalone keyboard driver or vendor HID transport is to be added.
