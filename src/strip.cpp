#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>
#include <stdlib.h>

#define HEIGHT 45
#define WIDTH 10


byte * boardmap = NULL; // Internal map of values

Adafruit_NeoPixel strip = Adafruit_NeoPixel(WIDTH, HEIGHT, 3, NEO_GRB + NEO_KHZ800);

uint16_t location (int x, int y) {
  uint16_t result = HEIGHT * WIDTH;
  if (y % 2 == 0) {
    return uint16_t(HEIGHT * WIDTH - (HEIGHT * x + y));
    result -= HEIGHT * x + y;
  } else {
    return uint16_t(HEIGHT * WIDTH - (HEIGHT * x + (HEIGHT - y)));
  }
}

uint16_t top_color = 0; // Stored in boardmap as 1
uint16_t middle_color = 0; // Stored in boardmap as 2
uint16_t bottom_color = 0; // Stored in boardmap as 3
uint16_t error_color = 0; // In case of a weird value
uint16_t black = 0; // Stored in boardmap as 0

uint16_t color = 0; // Color to output, initialized here and used in a for loop

uint8_t add_count = 0; // Number to add each pass

void setup () {
  boardmap = (byte*) malloc(WIDTH * HEIGHT); // Use malloc to initialize
  memset(boardmap, 0, WIDTH * HEIGHT);
  strip.begin();
  strip.setBrightness(10);
  Serial.begin(115200);

  // Colors for rain, stolen from old code
  // uint16_t Color(uint8_t r, uint8_t g, uint8_t b);
  top_color = strip.Color(71, 116, 255);
  middle_color = strip.Color(51, 106, 72);
  bottom_color = strip.Color(71, 116, 156);
  black = strip.Color(0, 0, 0);
  error_color = strip.Color(10, 200, 50);
}

void loop () {
  strip.clear();
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
      strip.setPixelColor(location(x, y), color);
    }
  }
  strip.show();
  delay(100);
}
