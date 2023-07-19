#include "hardware/timer.h"
#include "led_matrix.hpp"
#include "pico/stdlib.h"
#include <cmath>

#include "util.h"

#include "ws281x.hpp"

const uint kLedPin = 0;
const uint kLedLength = 263;

const uint16_t kLedMap[] = {
	263, 264, 265, 266, 267, 268, 269, 270, 271,   0,   1,   2,   3,   4,   5,   6,   7,   8, 272, 273, 274, 275,
	276, 277, 278, 279, 280, 281, 282, 283,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18, 284, 285, 286, 287,
	288, 289, 290, 291, 292, 293, 294,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29, 295, 296, 297, 298,
	299, 300, 301, 302, 303, 304,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41, 305, 306, 307, 308,
	309, 310, 311, 312, 313,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55, 314, 315, 316,
	317, 318, 319, 320,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70, 321, 322, 323,
	324, 325, 326,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86, 327, 328, 329,
	330, 331, 332,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 333, 334,
	335, 336, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 337, 338,
	339, 340, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 341, 342,
	343, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 344, 345,
	346, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 347,
	348, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 349,
	199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 350,
	220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 351,
	241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262
}; 

int main() {
	stdio_init_all();
	// sleep_ms(1000);

	WS281X_PIO ledStrip{
		kLedPin, kLedLength,
		pio0, 0,
		WS281X_PIO::FORMAT_GRB
	};

	LedMatrix matrix{
		&ledStrip,
		22, 16,
		kLedMap, 262
	};

	ledStrip.fill(0);
	ledStrip.show();
	sleep_ms(250);

	ledStrip.setBrightness(50);

	matrix.fill(WS281X_PIO::RGB(50, 0, 0));
	matrix.show();
	sleep_ms(250);
	matrix.fill(WS281X_PIO::RGB(0, 50, 0));
	matrix.show();
	sleep_ms(250);
	matrix.fill(WS281X_PIO::RGB(0, 0, 50));
	matrix.show();
	sleep_ms(250);

	matrix.clear();
	matrix.show();
	sleep_ms(250);

	

	matrix.drawLine(9,0, 17, 0, 		1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(17,0, 18, 8, 		1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(18,8, 20, 15, 	1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(20,15, 11, 15, 	1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(11, 15, 0, 15, 	1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(0, 15, 3, 7, 		1, WS281X_PIO::RGB(35, 20, 20));
	matrix.drawLine(3, 7, 9, 0, 		1, WS281X_PIO::RGB(35, 20, 20));

	matrix.setPixel(9, 0, WS281X_PIO::RGB(0, 100, 0));
	matrix.setPixel(17, 0, WS281X_PIO::RGB(100, 0, 0));
	matrix.setPixel(3, 7, WS281X_PIO::RGB(0, 0, 100));
	matrix.setPixel(18, 8, WS281X_PIO::RGB(0, 100, 100));
	matrix.setPixel(0, 15, WS281X_PIO::RGB(100, 0, 100));
	matrix.setPixel(11, 15, WS281X_PIO::RGB(100, 50, 0));
	matrix.setPixel(20, 15, WS281X_PIO::RGB(100, 100, 0));

	matrix.show();



	// // arm_watchdog();
	// printf("Wifi init start\n");
	// if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA)) {
	// 	printf("Wifi init failed\n");
	// 	return -1;
	// } else {
	// 	printf("Wifi init ok!\n");
	// }
	// sleep_ms(250);

	// printf("Wifi connect start\n");
	// WifiGpio::set(CYW43_WL_GPIO_LED_PIN, 0);
	// cyw43_arch_enable_sta_mode();

	// if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
	// 	printf("Wifi connect failed\n");
	// 	return -2;
	// } else {
	// 	printf("Wifi connect OK\n");
	// }

	// WifiGpio::set(CYW43_WL_GPIO_LED_PIN, 1);


	// sleep_ms(500);


	ledStrip.setBrightness(20);

	int16_t xOffset = 21;

	uint64_t lastXMoveUs = 0;

	uint32_t arrowColor = WS281X_PIO::RGB(240, 100, 0);

	while(true) {
		matrix.clear();
		int16_t arrow1x = 0 + xOffset;
		int16_t arrow2x = arrow1x + 4;
		matrix.drawArrow1(arrow1x, 8, 4, 7, 2, arrowColor);
		matrix.drawArrow1(arrow2x, 8, 4, 7, 2, arrowColor);

		bool lastArrowOffscreen = arrow2x + 4 < 0;

		if (time_us_64() - lastXMoveUs > 25000) {
			xOffset -= 1;
			if (lastArrowOffscreen) xOffset = 21;
			lastXMoveUs = time_us_64();
		}

		matrix.show();
		sleep_ms(1);
		// // Pick a random color
		// uint32_t color = (uint32_t)rand();
		// // Pick a random direction
		// int8_t dir = (rand() & 1 ? 1 : -1);
		// // Setup start and end offsets for the loop
		// uint16_t start = (dir > 0 ? 0 : kLedLength);
		// uint16_t end = (dir > 0 ? kLedLength : 0);
		// for (uint16_t ledIndex = start; ledIndex != end; ledIndex += dir) {
		// 	ledStrip.setPixelColor(ledIndex, color);
		// 	ledStrip.show();
		// 	// sleep_us(525); // 520us is the fastest the PIO can handle WS281x reliably
		// }
	}
}