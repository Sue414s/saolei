# 扫雷游戏 (saolei)

一个基于 Qt 6 的经典扫雷游戏，使用 C++ 和 CMake 构建。支持自定义网格大小、左键翻开、右键标记旗子等功能。

## ✨ 特性

- 经典的扫雷玩法（左键翻开格子，右键标记地雷）
- 剩余雷数,生命,积分显示
- 完全使用 Qt Widgets 实现，无额外依赖

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
### 2. 编译

```bash
mkdir build
cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_PREFIX_PATH="你的Qt安装路径/lib/cmake"
cmake --build build
```
