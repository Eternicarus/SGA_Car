# Copilot Instructions for SGA_Car Firmware Project

## Project Architecture
This STM32F103VC firmware uses a layered structure organized by Keil project groups:
- **`Apply/Logic`**: Core logic (`main.c`, `usercode.c`, `config.c`). User code goes in `UserLogic_Code()` function in `usercode.c`.
- **`Apply/Task`**: System initialization and interrupt handlers (`task_irq.c`, `task_sysinit.c`).
- **`Bsp/Algo`**: Control algorithms (e.g., `algo_pid.c` for PID control, `algo_func.c` for utilities).
- **`Bsp/OCD`**: On-chip device drivers (OLED, MPU6050, SD card, etc., e.g., `ocd_oled.c`).
- **`Bsp/Dev`**: External device drivers (e.g., PS2 controller in `dev_ps2.c`).
- **`Bsp/FatFs`**: FAT filesystem support for SD card storage.
- **`Driver`**: Hardware abstraction layer wrapping STM32 HAL (e.g., `drv_hal_uart.c` with DMA support).
- **`Hardware`**: Vendor-provided STM32F1xx HAL library, CMSIS, and startup files.

## Critical Developer Workflows
**Building and Flashing** (use EIDE extension commands via VS Code tasks):
- Run tasks via Command Palette or Task menu: `build`, `flash`, `build and flash`, `rebuild`, `clean`.
- Tasks invoke EIDE commands defined in `.vscode/tasks.json` (e.g., `${command:eide.project.build}`).
- **Important**: This project uses EIDE, not direct Keil CLI. Do NOT run `armcc` or `fromelf` manually.

**Keil Project Structure**:
- `STM32.uvprojx` is the main project file. Source groups match directory structure.
- Build outputs: `Objects/` (`.o`, `.axf`, `.hex`), `Listings/` (`.map`, `.lst`).
- Debug configs: `DebugConfig/` (e.g., `Target_1_STM32F103VC_1.0.0.dbgconf`).

## Project-Specific Patterns
**DMA-Based UART Communication** (see `drv_hal_uart.c` for details):
- Use `Drv_Uart_Receive_DMA()` and `Drv_Uart_Transmit_DMA()` for non-blocking serial I/O.
- Example in `usercode.c`: Receives data into `ReceBuf`, then echoes it back via DMA.
- UART instances configured with DMA priority settings (`ucDMARxPriority`, `ucDMATxPriority`).

**Peripheral Driver Pattern**:
- Drivers expose structured APIs (e.g., `tagUART_T` struct holds handle, DMA config, priorities).
- Configuration headers (`drv_hal_conf.h`, `ocd_conf.h`, `dev_conf.h`, `algo_conf.h`) enable/disable modules.
- Include hierarchy: `usercode.h` ¡ú `drv_hal_conf.h`, `task_conf.h`, `ocd_conf.h`, `dev_conf.h`, `algo_conf.h`.

**Macros & Defines**:
- Key defines set in project: `USE_HAL_DRIVER`, `STM32F103xE`, `STM32F1_SGA_ENABLE`.
- Include paths span all layers (see `STM32.uvprojx` line 343 for full list).

## Integration Points
- **RTOS Support**: Prepared for RT-Thread/FreeRTOS in `Bsp/RTOS/` (includes exist but not active by default).
- **Sensor Integration**: MPU6050 gyro data accessed via `tMPU6050.stcAngle.ConPitch` (see `usercode.c`).
- **Display Output**: OLED via `OCD_OLED_ShowFloatNum()` for real-time data visualization.

## Code Conventions
- C99 standard. Use `tag` prefix for struct typedefs (e.g., `tagUART_T`).
- File naming: `drv_hal_*.c` for drivers, `ocd_*.c` for on-chip devices, `algo_*.c` for algorithms.
- When adding peripherals: Update corresponding `*_conf.h`, add to Keil group, follow existing NVIC config pattern.
- **Do NOT** manually edit `.crf`, `.d`, or build artifacts in `Objects/` ¡ª these are generated.

---
**Need Help?** Check `main.c` for system init flow, `drv_hal_uart.c` for DMA patterns, or `algo_pid.c` for control examples.
