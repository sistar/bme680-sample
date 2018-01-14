#include "mgos.h"
#include "mgos_bme680.h"

static void timer_cb(void *bme680) {
  struct mgos_bme680_data data;
  memset(&data, 0, sizeof (data));
  mgos_bme680_read(bme680, &data);
  LOG(LL_INFO, ("Temperature: %lf", data.temp));
}

enum mgos_app_init_result mgos_app_init(void) {
  struct mgos_bme680 *bme680 = mgos_bme680_i2c_create(0x76);
  LOG(LL_INFO, ("BME680 connected: %i", mgos_bme680_is_bme680(bme680)));
  mgos_set_timer(1000, true, timer_cb, bme680);
  return MGOS_APP_INIT_SUCCESS;
}
