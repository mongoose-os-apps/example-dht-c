/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mgos.h"
#include "mgos_dht.h"

static struct mgos_dht *s_dht = NULL;

static void dht_timer_cb(void *arg) {
  float t = mgos_dht_get_temp(s_dht);
  float h = mgos_dht_get_humidity(s_dht);

  if (isnan(h) || isnan(t)) {
    LOG(LL_INFO, ("Failed to read data from sensor\n"));
    return;
  }
  LOG(LL_INFO, ("Temperature: %f *C Humidity: %f %%\n", t, h));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  if ((s_dht = mgos_dht_create(16, DHT22)) == NULL) return MGOS_APP_INIT_ERROR;
  mgos_set_timer(2000 /* ms */, true /* repeat */, dht_timer_cb, NULL);
  return MGOS_APP_INIT_SUCCESS;
}
