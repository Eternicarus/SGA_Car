# Copilot Instructions for SGA_Car Firmware Project

## 项目架构
- 本项目为 STM32F103VC 微控制器的固件，采用分层结构，主要分为：
  - `Apply/Logic`：主控逻辑与配置（如 `main.c`, `usercode.c`, `config.c`）。
  - `Apply/Task`：系统任务与初始化（如 `task_irq.c`, `task_sysinit.c`）。
  - `Bsp/Algo`：算法实现（如 PID 控制，`algo_pid.c`、`algo_func.c`）。
  - `Bsp/OCD`、`Bsp/Dev`、`Bsp/FatFs`：外设驱动与设备支持。
  - `Driver`：HAL 驱动层，封装底层硬件操作。
  - `Hardware`：芯片厂商提供的底层库与启动文件。

## 关键开发流程
- **构建/烧录/清理**：
  - 推荐使用 VS Code 的任务（已在 `.vscode/tasks.json` 配置）：
    - 构建：`build`
    - 烧录：`flash`
    - 构建并烧录：`build and flash`
    - 重新构建：`rebuild`
    - 清理：`clean`
- **Keil 项目文件**：
  - `STM32.uvprojx` 为主工程文件，包含所有源码分组与编译配置。
  - 输出文件在 `Objects/`，汇编/映射文件在 `Listings/`。
- **调试配置**：
  - 调试相关配置在 `DebugConfig/`，如目标芯片和调试器参数。

## 项目约定与模式
- 所有源码按功能分组，路径与 Keil 工程分组一致。
- 头文件与源文件分离，接口定义在 `Inc/`，实现在 `Src/`。
- 主要宏定义（如 `USE_HAL_DRIVER`, `STM32F103xE`, `STM32F1_SGA_ENABLE`）在工程配置中统一声明。
- 外设驱动优先使用 STM32 HAL 库，部分自定义驱动在 `Driver/` 和 `Bsp/`。
- 任务/中断相关代码集中在 `Apply/Task/`。
- 算法（如 PID）实现与参数配置分离，便于复用和调优。

## 依赖与集成
- 依赖 STM32F1xx HAL 库（见 `Hardware/STM32F1XX/STM32F1xx_HAL_Driver`）。
- 支持 RT-Thread、FreeRTOS，可在 `Bsp/RTOS/` 目录下扩展。
- FAT 文件系统支持（`Bsp/FatFs`），常用于 SD 卡存储。
- 典型外设如 OLED、传感器、存储器等均有独立驱动模块。

## 代码风格与建议
- 遵循 C99 标准，结构体、枚举、宏命名统一。
- 重要接口和数据流请参考 `main.c`、`algo_pid.c`、`drv_hal_xxx.c`。
- 新增模块请按现有分组和命名规范放置。
- 变更硬件相关配置时，务必同步更新 Keil 工程和相关头文件。

---
如有不清楚或遗漏的部分，请反馈以便进一步完善说明。
