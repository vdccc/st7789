#include "st7789.h"

#include <stdlib.h>

#include "include/st7789_commands.h"

static struct st7789_spi_transaction *trans_new(u8 cmd, u32 len, u8 *data) {
  struct st7789_spi_transaction *res =
      malloc(sizeof(struct st7789_spi_transaction));
  res->cmd = cmd;
  res->data_len = len;
  res->data = data;
  return res;
}

static void spi_send(struct st7789 *drv, struct st7789_spi_transaction *trans) {
  drv->spi.send(drv->spi.spi_priv, trans);
}

static void spi_wait(struct st7789 *drv, u32 delay) {
  drv->spi.wait(drv->spi.spi_priv, delay);
}

static void sw_reset(struct st7789 *drv) {
  spi_send(drv, trans_new(SWRESET, 0, 0));
  spi_wait(drv, SWRESET_DELAY_MSEC);
}

static void ca_set(struct st7789 *drv, u16 start, u16 end) {
  u16 *data = malloc(sizeof(u16) * 2);
  data[0] = start;
  data[1] = end;
  spi_send(drv, trans_new(CASET, 4, (u8 *)data));
}

static void ra_set(struct st7789 *drv, u16 start, u16 end) {
  u16 *data = malloc(sizeof(u16) * 2);
  data[0] = start;
  data[1] = end;
  spi_send(drv, trans_new(RASET, 4, (u8 *)data));
}

static void ram_wr(struct st7789 *drv, u32 len, u8 *buf) {
  spi_send(drv, trans_new(RAMWR, len, buf));
}

i32 st7789_init(struct st7789 *drv) {
  sw_reset(drv);
  return 0;
}

void st7789_disp_on(struct st7789 *drv) {
  spi_send(drv, trans_new(DISPON, 0, 0));
}

void st7789_disp_off(struct st7789 *drv) {
  spi_send(drv, trans_new(DISPOFF, 0, 0));
}

void st7789_disp_idle_on(struct st7789 *drv) {
  spi_send(drv, trans_new(IDMON, 0, 0));
}

void st7789_disp_idle_off(struct st7789 *drv) {
  spi_send(drv, trans_new(IDMOFF, 0, 0));
}

void st7789_disp_sleep_on(struct st7789 *drv) {
  spi_send(drv, trans_new(SLPIN, 0, 0));
}

void st7789_disp_sleep_off(struct st7789 *drv) {
  spi_send(drv, trans_new(SLPOUT, 0, 0));
}

i32 st7789_blit(struct st7789 *drv, struct st7789_blit_tgt *tgt) {
  ca_set(drv, tgt->col_start, tgt->col_start + tgt->width);
  ra_set(drv, tgt->row_start, tgt->row_start + tgt->height);
  ram_wr(drv, tgt->width * tgt->height, tgt->buf);
  return 0;
}
