#ifndef LUDELED_UTIL_H
#define LUDELED_UTIL_H

#include "pico/cyw43_arch.h"

class WifiGpio {
public:
	static void set(uint pin, bool state) {
		cyw43_arch_gpio_put(pin, state);
	}

	static bool get(uint pin) {
		return cyw43_arch_gpio_get(pin);
	}
};

#endif // LUDELED_UTIL_H