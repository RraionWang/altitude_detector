# XIAO ESP32-S3 BMP280 + SH1107 示例

本项目演示如何在 Seeed XIAO ESP32-S3 上同时使用 BMP280 气压/温度传感器和 SH1107 OLED 显示屏，实时读取并展示环境数据。

---


## 功能

- 通过 I²C 总线读取 BMP280 温度（°C）、气压（hPa）和海拔（m）  
- 使用 U8g2 库驱动 SH1107 OLED（128×128 分辨率）显示上述数据  
- 串口打印调试信息  

---

## 硬件清单

- Seeed XIAO ESP32-S3 ×1  
- BMP280 温度/气压传感器模块 ×1  
- SH1107 OLED 显示屏（128×128） ×1  
- 若干杜邦线  

---

## 接线说明

| 传感器 / 显示屏 | XIAO ESP32-S3 引脚           |
| -------------- | ---------------------------- |
| BMP280 SDA     | GPIO 3                       |
| BMP280 SCL     | GPIO 2                       |
| SH1107 SDA     | 默认 I²C SDA (GPIO 5)        |
| SH1107 SCL     | 默认 I²C SCL (GPIO 6)        |
| VCC            | 3.3V                         |
| GND            | GND                          |

> **注意：**  
> - BMP280 使用 `Wire.setPins(3,2)` 指定 SDA/SCL。  
> - SH1107 采用 U8g2 SW I2C 驱动，参数 `U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, SCL, SDA)`。

---

## 库依赖

请在 Arduino IDE 或 PlatformIO 中安装以下库：

- **U8g2** — OLED 驱动  
- **Adafruit BMP280** — BMP280 传感器驱动  
- **Adafruit Unified Sensor** — 传感器框架  

在 Arduino IDE 中可通过 **库管理器** 搜索并安装。

---

## 使用方法

### 1. 克隆仓库

```bash
git clone https://github.com/用户名/项目名.git
cd 项目名
```

### 2. 安装依赖
```bash 
打开 Arduino IDE/PlatformIO → 工具 → 管理库

搜索并安装

U8g2 by olikraus

Adafruit BMP280 Library

Adafruit Unified Sensor
```

3. 设置开发板
```bash 
工具 → 开发板 → 选择 Seeed XIAO ESP32S3

工具 → 端口 → 选择对应的串口
```
4. 编译并烧录
```bash
将 XIAO ESP32-S3 通过 USB 连接电脑

点击 上传，等待编译与烧录完成
```

## 代码结构
```bash 

project-root/
├── src/
│   └── main.ino        # 核心代码，包含 setup() 与 loop()
├── README.md           # 本文档
└── library/            # （可选）本地库文件或示例
main.ino
```

setup()：初始化串口、I²C、BMP280、OLED，并显示启动画面

loop()：

  1. 读取 BMP280 环境数据

  2. 串口打印调试

  3. 使用 U8g2 在 OLED 上分行显示温度、气压、海拔

  4. 延时 2 秒，循环执行

## 常见问题
### 1. OLED 不亮？

  检查 SDA/SCL 接线是否正确。

  确认地址（0x3C）与硬件一致。

### 2. BMP280 无数据？

  确保 Wire.setPins 设置了正确的引脚。

  检查供电与地线。

  编译报错找不到库？

  确保通过库管理器正确安装所有依赖。
