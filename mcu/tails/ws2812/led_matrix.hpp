#ifndef LED_MATRIX_HPP
#define LED_MATRIX_HPP

#ifndef LED_MATRIX_MAX_BUF
	#define LED_MATRIX_MAX_BUF 512
#endif

#include <stdint.h>
#include "ws281x.hpp"
#include <vector>

class LedMatrix {
public:
	LedMatrix(
		WS281X_PIO * pioLeds,
		const uint16_t xWidth,
		const uint16_t yWidth,
		const uint16_t * layoutMap = nullptr,
		const uint16_t layoutCount = 0);

	void setPixel(int16_t x, int16_t y, uint32_t color);
	void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, uint32_t color);
	void drawArrow1(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t thickness, uint32_t color);
	void fill(uint32_t color);
	void clear();

	void render();
	void show();

private:
	WS281X_PIO * pioLedsPtr;
	const uint16_t m_xWidth;
	const uint16_t m_yHeight;
	const uint16_t * m_layoutMap;
	const uint16_t m_ledCount;

	uint16_t mapPixel(int16_t x, int16_t y);

	std::vector<uint32_t> m_ledVec;
	// uint32_t m_ledStripBuf[LED_MATRIX_MAX_BUF];
	// std::vector<std::vector<uint32_t>> m_ledMatrix;
};

#endif /* LED_MATRIX_HPP */