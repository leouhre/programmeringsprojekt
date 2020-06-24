#include "LED_hp.h"

void led_hp_update(spaceship_t sh) { //set LED hp acording to hp left one each heart
	if (sh.hp < 1) { //turn LED of if dead
        led_color(0);
	} else {
        led_color((sh.hp % 3) + 1);
	}
}
