#include <Arduino.h">
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#define HEIGHT 30
#define WIDTH 10


int ** map = NULL; // Internal map of values

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 3,
        NEO_MATRIX_LEFT + NEO_MATRIX_TOP +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
        NEO_GRB + NEO_KHZ800);

void setup () {
  map = calloc(HEIGHT * WIDTH, sizeof(**map)); // Use calloc to initialize
  matrix.begin();
  matrix.show();
  matrix.setBrightness(10);
  Serial.begin(115200);
}

void loop () {
}
