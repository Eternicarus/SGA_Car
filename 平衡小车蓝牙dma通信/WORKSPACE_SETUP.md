# 工作区配置说明

## ? 如何使用新的工作区配置

已为您创建了 `SGA_Car.code-workspace` 文件，包含以下改进：

### ? 配置内容

1. **双根目录结构**：
   - `? Root (Source Code)`: 包含所有源码 (`Apply/`, `Bsp/`, `Driver/`, `Hardware/`)
   - `? Project (Keil)`: Keil 项目文件和构建输出

2. **C/C++ IntelliSense 配置**：
   - 自动包含所有头文件路径
   - 预定义宏：`USE_HAL_DRIVER`, `STM32F103xE`, `STM32F1_SGA_ENABLE`
   - C99 标准，ARM-GCC 模式

3. **文件过滤**：
   - 隐藏构建产物 (`Objects/`, `Listings/`)
   - 隐藏用户特定的 Keil 配置文件

### ? 启用步骤

**方法 1：直接打开工作区文件**
```
File → Open Workspace from File... 
→ 选择 "d:\MINE\My_SGA\平衡小车蓝牙dma通信\SGA_Car.code-workspace"
```

**方法 2：命令行打开**
```powershell
code "d:\MINE\My_SGA\平衡小车蓝牙dma通信\SGA_Car.code-workspace"
```

### ? 注意事项

- 打开工作区后，VS Code 会重新加载
- 任务配置 (`.vscode/tasks.json`) 将自动从 `Project` 文件夹继承
- EIDE 扩展将继续工作，因为 Keil 项目文件仍在 `Project/` 下

### ? 验证

打开工作区后，应该能在资源管理器中看到：
```
? Root (Source Code)
  ├── Apply/
  ├── Bsp/
  ├── Driver/
  ├── Hardware/
  └── Project/
? Project (Keil)
  ├── .github/
  ├── .vscode/
  ├── STM32.uvprojx
  └── ...
```

---
**创建时间**: 2025-10-14  
**工具**: GitHub Copilot
