# ����������˵��

## ? ���ʹ���µĹ���������

��Ϊ�������� `SGA_Car.code-workspace` �ļ����������¸Ľ���

### ? ��������

1. **˫��Ŀ¼�ṹ**��
   - `? Root (Source Code)`: ��������Դ�� (`Apply/`, `Bsp/`, `Driver/`, `Hardware/`)
   - `? Project (Keil)`: Keil ��Ŀ�ļ��͹������

2. **C/C++ IntelliSense ����**��
   - �Զ���������ͷ�ļ�·��
   - Ԥ����꣺`USE_HAL_DRIVER`, `STM32F103xE`, `STM32F1_SGA_ENABLE`
   - C99 ��׼��ARM-GCC ģʽ

3. **�ļ�����**��
   - ���ع������� (`Objects/`, `Listings/`)
   - �����û��ض��� Keil �����ļ�

### ? ���ò���

**���� 1��ֱ�Ӵ򿪹������ļ�**
```
File �� Open Workspace from File... 
�� ѡ�� "d:\MINE\My_SGA\ƽ��С������dmaͨ��\SGA_Car.code-workspace"
```

**���� 2�������д�**
```powershell
code "d:\MINE\My_SGA\ƽ��С������dmaͨ��\SGA_Car.code-workspace"
```

### ? ע������

- �򿪹�������VS Code �����¼���
- �������� (`.vscode/tasks.json`) ���Զ��� `Project` �ļ��м̳�
- EIDE ��չ��������������Ϊ Keil ��Ŀ�ļ����� `Project/` ��

### ? ��֤

�򿪹�������Ӧ��������Դ�������п�����
```
? Root (Source Code)
  ������ Apply/
  ������ Bsp/
  ������ Driver/
  ������ Hardware/
  ������ Project/
? Project (Keil)
  ������ .github/
  ������ .vscode/
  ������ STM32.uvprojx
  ������ ...
```

---
**����ʱ��**: 2025-10-14  
**����**: GitHub Copilot
