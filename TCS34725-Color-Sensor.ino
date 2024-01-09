#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found TCS34725");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop(void) {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);

  // Menebak warna berdasarkan nilai-nilai RGB
  String predictedColor = guessColor(r, g, b);
  Serial.print("Predicted Color: "); Serial.println(predictedColor);

  delay(1000);
}

// Fungsi untuk menebak warna berdasarkan nilai-nilai RGB
String guessColor(uint16_t red, uint16_t green, uint16_t blue) {
  // Mendominasi warna yang memiliki nilai tertinggi
  if (red > green && red > blue) {
    return "Merah";
  } else if (green > red && green > blue) {
    return "Hijau";
  } else if (blue > red && blue > green) {
    return "Biru";
  } else {
    return "Tidak Dikenal";
  }
}
