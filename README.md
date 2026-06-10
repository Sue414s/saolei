# 扫雷游戏 (saolei)

一个基于 Qt 6 的经典扫雷游戏，使用 C++ 和 CMake 构建。支持自定义网格大小、左键翻开、右键标记旗子等功能。

## ✨ 特性

- 经典的扫雷玩法（左键翻开格子，右键标记地雷）
- 剩余雷数,生命,积分显示
- 完全使用 Qt 实现，无额外依赖

## 📦 依赖

- **CMake** 3.16 或更高版本
- **Qt 6** (推荐 6.4 以上) – 需要以下组件：
  - Core
  - Widgets
  - 可选：Gui（用于图标）

如果你使用的是 Qt 5，可以修改 `CMakeLists.txt` 中的 `find_package(Qt6...)` 为 `Qt5`，但建议使用 Qt 6。

## 🔧 构建与运行

### 1. 克隆仓库

```bash
git clone https://github.com/Sue414s/saolei.git
cd saolei

```
### 2. 配置与编译

```bash
cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_PREFIX_PATH="你的Qt安装路径/lib/cmake"
# Windows (MinGW) 示例: -DCMAKE_PREFIX_PATH="D:/Qt/6.5.0/mingw64/lib/cmake"
cmake --build build
```
### 3. 运行
```bash
cd build
#如果运行提示缺乏动态库请执行windeployqt saolei.exe
saolei.exe
```

## 🎵 自定义音效与背景音乐

游戏支持用户自行替换背景音乐（BGM）和游戏音效。请按照以下步骤操作。

### 📁 文件夹结构

在你编译生成的 `build/` 目录下（即 `saolei.exe` 所在位置），手动创建两个文件夹:  
build/  
├── bgm/ # 存放背景音乐(MP3 格式) 
│ └── (你的音乐文件)  
├── sounds/ # 存放游戏音效(WAV 格式)  
│ └── (你的音效文件)  
└── saolei.exe  
注意音乐文件名称,例如`spread.wav`表示扩散音效。
