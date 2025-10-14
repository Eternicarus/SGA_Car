@echo off
echo ============================================
echo   SGA_Car 工作区快速启动脚本
echo ============================================
echo.
echo 正在打开多根工作区...
echo.

cd /d "%~dp0"
code "SGA_Car.code-workspace"

echo.
echo 工作区已在 VS Code 中打开！
echo 如果没有自动切换，请：
echo   1. 查看任务栏是否有新的 VS Code 窗口
echo   2. 或在当前窗口：File ^> Open Workspace from File...
echo.
pause
