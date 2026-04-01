# nRF_blanktest

Simple Zephyr/NCS app that toggles GPIO P0.28 at ~1 Hz (0.5 s low, 0.5 s high).

## Requirements

- nRF Connect SDK (tested with v3.2.4)
- `west` initialized for the NCS workspace
- A supported board. This repo includes a custom board variant under `boards/others/nrf52840dk`.

## Build

From the repository root:

```bash
west boards --board-root .
west build -b <board> -p auto
```

Use the board identifier shown by `west boards`. If you are targeting the custom variant, look for an entry that includes the `nrf52840dk` board with the `nrf52840` qualifier and the `ca03` variant.

## Flash

```bash
west flash
```

## Notes

- `CMakeLists.txt` adds the repo root to `BOARD_ROOT`, so custom boards in this repo are picked up automatically.
- The app uses `CONFIG_GPIO=y` from `prj.conf`.
