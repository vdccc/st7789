#include "st7789.h"

#include "st7789_commands.h"

static void spi_send(struct st7789 *drv, u8 data) {
  drv->spi.send(drv->spi.spi_priv, data);
}

static void spi_wait(struct st7789 *drv, u8 delay) {
  drv->spi.wait(drv->spi.spi_priv, delay);
}

i8 swreset(struct st7789 *drv) {
  spi_send(drv, SWRESET);
  spi_wait(drv, SWRESET_DELAY_MSEC);
  return 0;
}

static void ca_set(struct st7789 *drv, u16 start, u16 end) {
  spi_send(drv, CASET);
  spi_send(drv, DATA(start));
  spi_send(drv, DATA(start >> 7));
  spi_send(drv, DATA(end));
  spi_send(drv, DATA(end >> 7));
}

static void ra_set(struct st7789 *drv, u16 start, u16 end) {
  spi_send(drv, RASET);
  spi_send(drv, DATA(start));
  spi_send(drv, DATA(start >> 7));
  spi_send(drv, DATA(end));
  spi_send(drv, DATA(end >> 7));
}

static void ram_wr(struct st7789 *drv, const u8 *buf, u16 len) {
  spi_send(drv, RAMWR);
  for (u16 i = 0; i < len; i++) {
    spi_send(drv, COLOR(buf[i]));
  }
}

i8 init(struct st7789 *drv) { return swreset(drv); }

void disp_on(struct st7789 *drv) { spi_send(drv, DISPON); }

void disp_off(struct st7789 *drv) { spi_send(drv, DISPOFF); }

void disp_idle_on(struct st7789 *drv) { spi_send(drv, IDMON); }

void disp_idle_off(struct st7789 *drv) { spi_send(drv, IDMOFF); }

void disp_sleep_on(struct st7789 *drv) { spi_send(drv, SLPIN); }

void disp_sleep_off(struct st7789 *drv) { spi_send(drv, SLPOUT); }

i8 blit(struct st7789 *drv, struct st7789_blit_tgt *tgt) {
  ca_set(drv, tgt->col_start, tgt->col_start + tgt->width);
  ra_set(drv, tgt->row_start, tgt->row_start + tgt->height);
  ram_wr(drv, tgt->buf, tgt->width * tgt->height);
  return 0;
}