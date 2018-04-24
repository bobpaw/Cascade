#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

// Required for GFX on PlatformIO
#include <SPI.h>

#define HEIGHT 45
#define WIDTH 10


uint16_t * boardmap = NULL; // Internal map of values

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 3,
                                               NEO_MATRIX_LEFT + NEO_MATRIX_TOP +
                                               NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

uint16_t top_color = 0;
uint16_t middle_color = 0;
uint16_t bottom_color = 0;
uint16_t black = 0;

uint8_t add_count = 0;

void setup () {
  boardmap = (uint16_t*) calloc(HEIGHT * WIDTH, sizeof(*boardmap)); // Use calloc to initialize
  matrix.begin();
  matrix.show();
  matrix.setBrightness(10);
  Serial.begin(115200);

  // Colors for rain, stolen from old code
  // uint16_t Color(uint8_t r, uint8_t g, uint8_t b);
  top_color = matrix.Color(71, 116, 255);
  middle_color = matrix.Color(51, 106, 72);
  bottom_color = matrix.Color(71, 116, 156);
  black = matrix.Color(0, 0, 0);
}

void loop () {

  // Wipe the screen
  matrix.fillScreen(black);

  // Move everything down one space internally
  for (int y = HEIGHT - 1; y > 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
      boardmap[y * WIDTH + x] = boardmap[(y-1) * WIDTH + x];
    }
  }

  // Clear the top row
  for (int x = 0; x < WIDTH; x++) {
    boardmap[x] = black;
  }

  // Randomly create some new rain
  add_count = random(WIDTH);
  for (int i = 0; i < add_count; i++) {
    boardmap[random(WIDTH)] = top_color;
  }

  // Draw pixels from internal map
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (boardmap[y * WIDTH + x] != black) {
        matrix.drawPixel(int16_t(x), int16_t(y), boardmap[y * WIDTH + x]);
      }
    }
  }
  matrix.show();
  delay(100);
}
