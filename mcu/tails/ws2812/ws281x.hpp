#ifndef WS281X_HPP
#define WS281X_HPP

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#include <vector>

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
	pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
	return
		((uint32_t) (r) << 8) |
		((uint32_t) (g) << 16) |
		(uint32_t) (b);
}

class WS281X_PIO {
public:
	enum DataByte {
		NONE=0,
		RED=1,
		GREEN=2,
		BLUE=3,
		WHITE=4
	};

	enum DataFormat {
		FORMAT_RGB = 0,
		FORMAT_GRB = 1,
		FORMAT_WRGB = 2,
		FORMAT_RGBW = 3
	};

	WS281X_PIO(uint pin, uint length, PIO pio, uint sm);
	WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataFormat format);
	WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3);
	WS281X_PIO(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3, DataByte b4);
	~WS281X_PIO();

	static uint32_t RGB(uint8_t red, uint8_t green, uint8_t blue) {
		return (uint32_t)(blue) << 16 | (uint32_t)(green) << 8 | (uint32_t)(red);
	};

	static uint32_t RGBW(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
		return (uint32_t)(white) << 24 | (uint32_t)(blue) << 16 | (uint32_t)(green) << 8 | (uint32_t)(red);
	}

	void setBrightness(uint8_t brightness);

	void setPixelColor(uint index, uint32_t color);
	void setPixelColor(uint index, uint8_t red, uint8_t green, uint8_t blue);
	void setPixelColor(uint index, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
	void fill(uint32_t color);
	void fill(uint32_t color, uint first);
	void fill(uint32_t color, uint first, uint count);
	void fill(std::vector<uint32_t> flat2d);
	uint32_t convertData(uint32_t rgbw);
	void show();

private:
	uint pin;
	uint length;
	PIO pio;
	uint sm;
	DataByte bytes[4];
	uint32_t *data;

	uint8_t m_brightness = 1;

	void initialize(uint pin, uint length, PIO pio, uint sm, DataByte b1, DataByte b2, DataByte b3, DataByte b4);
};

#endif /* WS281X_HPP */