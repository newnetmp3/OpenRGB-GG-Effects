# Development handover — 2026-10-15

Repository: https://github.com/newnetmp3/OpenRGB-GG-Effects

The owner requested a standalone OpenRGB effects plugin, **not** an Apex controller with effects bundled. A new public repository was created by the owner.

Initial source: header-only C++17 RGB blend/mask primitives and 8 basic animation modes, including four synthetic keypress-reactive effects. Tests are provided but have not yet been run. No OpenRGB API bindings, plugin binary, real keypress monitor, or device writes exist yet. Do not describe this as installable or hardware-tested.

Default-on keypress requirement: Automatically activate passive input monitoring for reactive effects; no manual enable checkbox. Gracefully report missing input permissions. Do not grab devices, store typed content, or bypass security. Mapping physical key events to the selected OpenRGB device remains a separate implementation task.

Reference projects: newnetmp3/ApexProMini_gg_rgb (Rust scene/compositor and presets) and newnetmp3/OpenRGB-ApexProMini (controller). Reuse independently developed algorithms, not proprietary assets. Preserve the controller's independence.

Next: run CMake/CTest, wire CI, port preset catalog and layered scenes, implement OpenRGB plugin API integration without RGBController registration, and add automatic read-only evdev event handling with hotplug recovery.
