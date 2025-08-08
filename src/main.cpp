#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// ==================== BMP280 设置 ====================
#define BMP280_ADDR 0x77

// BMP280 使用 GPIO3(SDA), GPIO2(SCL)
#define BMP_SDA 3
#define BMP_SCL 2

Adafruit_BMP280 bmp;

// ==================== OLED 设置（完全遵循你的参考代码）====================
// 使用 SCL/SDA 宏（在 XIAO ESP32S3 上对应 GPIO6/GPIO5）
U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  // 初始化串口（用于调试）
  Serial.begin(115200);
  while (!Serial);

  // ------------------ 初始化 BMP280 ------------------
  if (!Wire.setPins(BMP_SDA, BMP_SCL)) {
    Serial.println("❌ BMP280: 设置 I2C 引脚失败！");
    while (1) delay(10);
  }

  Wire.begin();
  Wire.setClock(100000);  // 100kHz

  if (!bmp.begin(BMP280_ADDR)) {
    Serial.println("❌ 未找到 BMP280 传感器，请检查接线！");
    while (1) delay(10);
  }
  Serial.println("✅ BMP280 初始化成功！");

  // ------------------ 初始化 OLED（完全按照你的参考）------------------
  u8g2.begin();  // 使用你验证过的初始化方式

  // 显示启动信息（使用你验证过的算法和字体）
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB08_tf);
    u8g2.drawStr(0, 24, "Hello Seeed!");
    u8g2.drawStr(0, 40, "BMP280 + SH1107");
  } while (u8g2.nextPage());

  delay(1000);
}

void loop(void) {
  // 读取传感器数据
  float temperature = bmp.readTemperature();     // °C
  float pressure = bmp.readPressure() / 100.0F;  // hPa
  float altitude = bmp.readAltitude(1013.25);    // m

  // 串口输出（可选，用于调试）
  Serial.print(": "); Serial.print(temperature, 2); Serial.println(" °C");
  Serial.print("Pres: "); Serial.print(pressure, 2); Serial.println(" hPa");
  Serial.print("Alt: "); Serial.print(altitude, 2); Serial.println(" m");
  Serial.println("------------------------------------");

  // ------------------ OLED 显示（完全遵循你的参考结构）------------------
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB08_tf);

    // 第一行：温度
    u8g2.setCursor(0, 16);
    u8g2.print("temperature: ");
    u8g2.print(temperature, 2);
    u8g2.print(" C");

    // 第二行：气压
    u8g2.setCursor(0, 36);
    u8g2.print("Pressure: ");
    u8g2.print(pressure, 2);
    u8g2.print(" hPa");

    // 第三行：海拔
    u8g2.setCursor(0, 56);
    u8g2.print("Aaltitude: ");
    u8g2.print(altitude, 2);
    u8g2.print(" m");

    // 可选：底部信息
    u8g2.setCursor(0, 100);
    u8g2.print("Made with XIAOESP32S3");
    u8g2.setCursor(0, 120);
    u8g2.print("ChaiHuo Makerapace");

  } while (u8g2.nextPage());

  delay(2000);  // 每2秒刷新一次
}