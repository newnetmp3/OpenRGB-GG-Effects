# Development handover — 2026-10-15

Repository: https://github.com/newnetmp3/OpenRGB-GG-Effects

The owner requested a standalone OpenRGB effects plugin, **not** an Apex controller with effects bundled. A new public repository was created by the owner.

Initial source: header-only C++17 RGB blend/mask primitives and 8 basic animation modes, including four synthetic keypress-reactive effects. Tests are provided but have not yet been run. No OpenRGB API bindings, plugin binary, real keypress monitor, or device writes exist yet. Do not describe this as installable or hardware-tested.

Default-on keypress requirement: Automatically activate passive input monitoring for reactive effects; no manual enable checkbox. Gracefully report missing input permissions. Do not grab devices, store typed content, or bypass security. Mapping physical key events to the selected OpenRGB device remains a separate implementation task.

Reference projects: newnetmp3/ApexProMini_gg_rgb (Rust scene/compositor and presets) and newnetmp3/OpenRGB-ApexProMini (controller). Reuse independently developed algorithms, not proprietary assets. Preserve the controller's independence.

Next: run CMake/CTest, wire CI, port preset catalog and layered scenes, implement OpenRGB plugin API integration without RGBController registration, and add automatic read-only evdev event handling with hotplug recovery.

## Qt5/OpenRGB compatibility requirement — 2026-10-15
- **Qt5 is the required initial GUI target**, matching the owner's locally built Qt5 OpenRGB executable on Arch Linux.
- Build any plugin UI with Qt5 Core/Widgets; do not silently link Qt6 or assume a Qt6 plugin can load into a Qt5 host.
- Target OpenRGB Plugin API v5 only after confirming the owner's host headers and exported ABI; compile the plugin against the same OpenRGB source/runtime as the host.
- Keep the effects renderer independent of Qt for offline tests. No bundled RGB controller.
- CI should eventually compile the Qt5 plugin against a pinned compatible OpenRGB checkout; Qt6 is not an acceptance requirement.

## Vendor installer reference and fidelity mandate
The owner explicitly requires literal observable GG effect parity and requests that the previously supplied installer contents be the primary reference. Earlier installer analysis identified:
- macOS SteelSeriesGG108.3.0.pkg: SteelSeriesPrismSyncV2.pkg contains a native SteelSeriesPrism binary (~18.7 MB); SteelSeriesEngineCore.pkg includes device specifications.
- Windows SteelSeriesGG121.0.0Setup.exe: NSIS installer; inner payload was not extracted in the earlier analysis.
- Existing analysis artifact: steelseries_apex_pro_mini_installer_analysis.md in the owner's ChatGPT file library.
- Device .edevice descriptors are encrypted; they do not directly expose readable animation shader parameters. The Prism executable has not yet been statically analyzed for exact shader behavior.
These are reference inputs, NOT permission to redistribute vendor binaries, encrypted descriptors, trademarks as branding, or proprietary source code. Implement independently from observable behavior, resource metadata and lawful analysis. Do not label effects exact until evidence supports the claim. Prioritize Prism binary resources/effect parameter metadata over Apex HID/device specification files for this effects-only repository.
Next: recover accessible installer payloads, inventory Prism animation/preset resources and effect parameters, build per-effect parity matrix (timing, spatial mapping, color, input, defaults), then replace placeholder algorithms and add snapshot comparisons.
