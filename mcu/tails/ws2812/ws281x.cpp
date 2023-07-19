#include "ws281x.hpp"
#include "ws2812.pio.h"

#include <vector>

// #define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

WS281X_PIO::WS281X_PIO(uint pin, uint length, PIO pio, uint sm)  {
	initialize(pin, length, pio, sm, NONE, GREEN, RED, BLUE);
}

WS281X_PIO::WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataFormat format) {
	switch (format) {
		case FORMAT_RGB:
			initialize(pin, length, pio, sm, NONE, RED, GREEN, BLUE);
			break;
		case FORMAT_GRB:
			initialize(pin, length, pio, sm, NONE, GREEN, RED, BLUE);
			break;
		case FORMAT_WRGB:
			initialize(pin, length, pio, sm, WHITE, RED, GREEN, BLUE);
			break;
		case FORMAT_RGBW:
			initialize(pin, length, pio, sm, RED, GREEN, BLUE, WHITE);
			break;
	}
}

WS281X_PIO::WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3) {
	initialize(pin, length, pio, sm, b1, b1, b2, b3);
}

WS281X_PIO::WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3, DataByte b4) {
	initialize(pin, length, pio, sm, b1, b2, b3, b4);
}

WS281X_PIO::~WS281X_PIO() {}

void WS281X_PIO::initialize(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3, DataByte b4) {
	this->pin = pin;
	this->length = length;
	this->pio = pio;
	this->sm = sm;
	this->data = new uint32_t[length];
	this->bytes[0] = b1;
	this->bytes[1] = b2;
	this->bytes[2] = b3;
	this->bytes[3] = b4;
	uint offset = pio_add_program(pio, &ws2812_program);
	uint bits = (b1 == NONE ? 24 : 32);
	#ifdef DEBUG
	printf("WS281X_PIO / Initializing SM %u with offset %X at pin %u and %u data bits...\n", sm, offset, pin, bits);
	#endif
	ws2812_program_init(pio, sm, offset, pin, 800000, bits == 32);
}

uint32_t WS281X_PIO::convertData(uint32_t rgbw) {
	uint32_t result = 0;
	for (uint b = 0; b < 4; b++) {
		switch (bytes[b]) {
			case RED:
				result |= (rgbw & 0xFF) / m_brightness;
				break;
			case GREEN:
				result |= ((rgbw & 0xFF00) >> 8) / m_brightness;
				break;
			case BLUE:
				result |= ((rgbw & 0xFF0000) >> 16) / m_brightness;
				break;
			case WHITE:
				result |= ((rgbw & 0xFF000000) >> 24) / m_brightness;
				break;
			default: break;
		}
		result <<= 8;
	}
	return result;
}

void WS281X_PIO::setBrightness(uint8_t brightness) {
	m_brightness = 255 / brightness;
}

void WS281X_PIO::setPixelColor(uint index, uint32_t color) {
	if (index < length) {
		data[index] = convertData(color);
	}
}

void WS281X_PIO::setPixelColor(uint index, uint8_t red, uint8_t green, uint8_t blue) {
	setPixelColor(index, RGB(red, green, blue));
}

void WS281X_PIO::setPixelColor(uint index, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
	setPixelColor(index, RGBW(red, green, blue, white));
}

void WS281X_PIO::fill(uint32_t color) {
	fill(color, 0, length);
}

void WS281X_PIO::fill(uint32_t color, uint first) {
	fill(color, first, length-first);
}

void WS281X_PIO::fill(uint32_t color, uint first, uint count) {
	uint last = (first + count);
	if (last > length) {
		last = length;
	}
	color = convertData(color);
	for (uint i = first; i < last; i++) {
		data[i] = color;
	}
}

void WS281X_PIO::fill(std::vector<uint32_t> flat2d) {
	std::copy(flat2d.begin(), flat2d.end(), data);
}

void WS281X_PIO::show() {
	#ifdef DEBUG
	for (uint i = 0; i < length; i++) {
		printf("WS281X_PIO / Put data: %08X\n", data[i]);
	}
	#endif
	for (uint i = 0; i < length; i++) {
		pio_sm_put_blocking(pio, sm, data[i]);
	}
	sleep_us(525); // guarantee we don't hit show again within 525us (max rate)
}