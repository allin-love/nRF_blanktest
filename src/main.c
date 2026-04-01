#include <zephyr/kernel.h>
#include <hal/nrf_gpio.h>

int main(void)
{
    nrf_gpio_cfg_output(28);

    while (1) {
        nrf_gpio_pin_clear(28);
        k_busy_wait(500000);

        nrf_gpio_pin_set(28);
        k_busy_wait(500000);
    }
}