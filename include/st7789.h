#ifndef _ST7789_H_
#define _ST7789_H_

#include "types.h"

struct st7789_spi {
  void *spi_priv;

  i8 (*send)(void *spi_priv, u8 data);
  i8 (*wait)(void *spi_priv, u8 msec);
};

struct st7789_display {
  u8 width;
  u8 height;
  u8 ram_offset;
};

struct st7789 {
  struct st7789_display disp;
  struct st7789_spi spi;
};

i8 st7789_init(struct st7789 *drv);

void st7789_disp_on(struct st7789 *drv);
void st7789_disp_off(struct st7789 *drv);
void st7789_disp_idle_on(struct st7789 *drv);
void st7789_disp_idle_off(struct st7789 *drv);
void st7789_disp_sleep_on(struct st7789 *drv);
void st7789_disp_sleep_off(struct st7789 *drv);

struct st7789_blit_tgt {
  u16 col_start;
  u16 row_start;
  u16 width;
  u16 height;
  u8 *buf;
};

i8 st7789_blit(struct st7789 *drv, struct st7789_blit_tgt *tgt);

#endif
