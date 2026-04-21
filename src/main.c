#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <hal/nrf_gpio.h>

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

int main(void)
{
    int err;

    /* 保留一个 LED 状态指示，P0.28 低亮高灭按你之前接法调整 */
    nrf_gpio_cfg_output(28);
    nrf_gpio_pin_set(28);   // 默认灭

    err = bt_enable(NULL);
    if (err) {
        /* BLE 初始化失败：快速闪烁 */
        while (1) {
            nrf_gpio_pin_clear(28);
            k_msleep(100);
            nrf_gpio_pin_set(28);
            k_msleep(100);
        }
    }

    err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        /* 广播启动失败：慢闪 */
        while (1) {
            nrf_gpio_pin_clear(28);
            k_msleep(500);
            nrf_gpio_pin_set(28);
            k_msleep(500);
        }
    }

    /* 广播成功：常亮 */
    nrf_gpio_pin_clear(28);

    while (1) {
        k_sleep(K_SECONDS(1));
    }
}