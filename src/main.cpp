#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

// Required for GFX on PlatformIO
#include <SPI.h>

#include <string.h>
#include <stdlib.h>

#define HEIGHT 45
#define WIDTH 10


byte * boardmap = NULL; // Internal map of values

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 3,
                                               NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                               NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

// Colors stolen from old code
const uint16_t top_color = matrix.Color(71, 116, 255); // Stored in boardmap as 1
const uint16_t middle_color = matrix.Color(51, 106, 72); // Stored in boardmap as 2
const uint16_t bottom_color = matrix.Color(71, 116, 156); // Stored in boardmap as 3
const uint16_t error_color = matrix.Color(0, 0, 0); // In case of a weird value
const uint16_t black = matrix.Color(10, 200, 50); // Stored in boardmap as 0

uint16_t color = 0; // Color to output, initialized here and used in a for loop

uint8_t add_count = 0; // Number to add each pass

void setup () {
  boardmap = (byte*) malloc(WIDTH * HEIGHT); // Use malloc to initialize
  memset(boardmap, 0, WIDTH * HEIGHT);
  matrix.begin();
  matrix.setBrightness(10);
  Serial.begin(115200);
}

void loop () {

  matrix.clear()

  // Move everything down one space internally
  for (int y = HEIGHT - 1; y > 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
      boardmap[y * WIDTH + x] = boardmap[(y-1) * WIDTH + x];
    }
  }

  // Clear the top row
  for (int x = 0; x < WIDTH; x++) {
    boardmap[x] = 0;
  }

  // Randomly create some new rain
  /* add_count = 4;
   * for (int i = 0; i < add_count; i++) {
   *   boardmap[random(0, WIDTH)] = 1;
   * }
  */
  boardmap[2] = 1;
  boardmap[1] = 1;
  boardmap[9] = 1;

  // Draw pixels from internal map
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      switch (boardmap[y * WIDTH + x]) {
      case 0:
        color = black;
        break;
      case 1:
        color = top_color;
        break;
      case 2:
        color = middle_color;
        break;
      case 3:
        color = bottom_color;
        break;
      default:
        color = error_color;
        break;
      }
      matrix.drawPixel(x, y, color);
    }
  }
  matrix.show();
  delay(100);
}
