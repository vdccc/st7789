#ifndef _ST7789_H_
#define _ST7789_H_

#include "types.h"

struct st7789_spi_transaction {
  u32 data_len;
  u8 *data;
  u8 cmd;
};

struct st7789_spi {
  void *spi_priv;

  i32 (*send)(void *spi_priv, struct st7789_spi_transaction *transaction);
  i32 (*wait)(void *spi_priv, u32 msec);
};

struct st7789_display {
  u32 width;
  u32 height;
  u32 ram_offset;
};

struct st7789 {
  struct st7789_display disp;
  struct st7789_spi spi;
};

i32 st7789_init(struct st7789 *drv);

void st7789_disp_on(struct st7789 *drv);
void st7789_disp_off(struct st7789 *drv);
void st7789_disp_idle_on(struct st7789 *drv);
void st7789_disp_idle_off(struct st7789 *drv);
void st7789_disp_sleep_on(struct st7789 *drv);
void st7789_disp_sleep_off(struct st7789 *drv);

struct st7789_blit_tgt {
  u32 col_start;
  u32 row_start;
  u32 width;
  u32 height;
  u8 *buf;
};

i32 st7789_blit(struct st7789 *drv, struct st7789_blit_tgt *tgt);

#endif
