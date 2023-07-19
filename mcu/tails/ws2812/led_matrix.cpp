#include "led_matrix.hpp"

#include <algorithm>
#include <cstdint>
#include <execution>

LedMatrix::LedMatrix(
		WS281X_PIO * pioLeds,
		const uint16_t xWidth,
		const uint16_t yHeight,
		const uint16_t * layoutMap,
		const uint16_t layoutCount
)
	: pioLedsPtr(pioLeds),
		m_xWidth(xWidth),
		m_yHeight(yHeight),
		m_layoutMap(layoutMap),
		m_ledCount(layoutMap ? layoutCount : xWidth*yHeight)
{
	m_ledVec.resize(m_ledCount + 1); // 1 extra for OOB mapping
}

void LedMatrix::fill(uint32_t color) {
	color = pioLedsPtr->convertData(color); // TODO: make unnecessary, hardcode BGR
	std::fill_n(m_ledVec.begin(), m_ledVec.size(), color);
}

void LedMatrix::clear() {
	std::fill_n(m_ledVec.begin(), m_ledVec.size(), 0);
}

void LedMatrix::setPixel(int16_t x, int16_t y, uint32_t color) {
	if (x > m_xWidth-1 || x < 0 || y > m_yHeight-1 || y < 0) return;
	color = pioLedsPtr->convertData(color); // TODO: make unnecessary, hardcode BGR
	m_ledVec[mapPixel(x, y)] = color;
}

void LedMatrix::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, uint32_t color) {
	// Calculate the change in x and y for the line
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);
  
  // Determine the direction of the line in x and y
  int x_dir = x2 > x1 ? 1 : -1;
  int y_dir = y2 > y1 ? 1 : -1;
  
  // Calculate the error factor
  int error = dx - dy;
  
  // Loop through each pixel along the line and draw a rectangle of pixels with a width equal to the line thickness
  while (x1 != x2 || y1 != y2) {
    // Draw the current pixel and adjacent pixels to create a rectangle of pixels with the given thickness
    for (int i = -thickness/2; i <= thickness/2; i++) {
      setPixel(x1, y1+i, color);
    }
    
    // Calculate the next pixel
    int error2 = error * 2;
    if (error2 > -dy) {
      error -= dy;
      x1 += x_dir;
    }
    if (error2 < dx) {
      error += dx;
      y1 += y_dir;
    }
  }
  
  // Draw a rectangle of pixels at the final position to complete the line
  for (int i = -thickness/2; i <= thickness/2; i++) {
    setPixel(x2, y2+i, color);
  }
}

void LedMatrix::drawArrow1(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t thickness, uint32_t color) {
	drawLine(x, y, x + width, y + height, thickness, color);
	drawLine(x, y, x + width, y - height, thickness, color);
}


void LedMatrix::render() {
	pioLedsPtr->fill(m_ledVec);
}

void LedMatrix::show() {
	render();
	pioLedsPtr->show();
}

uint16_t LedMatrix::mapPixel(int16_t x, int16_t y) {
	if ( (x >= m_xWidth) || (y >= m_yHeight) || (x < 0) || ( y < 0) ) {
    return (m_ledCount + 1);
  }

	uint16_t i = (y * m_xWidth) + x;
	return m_layoutMap[i];
}