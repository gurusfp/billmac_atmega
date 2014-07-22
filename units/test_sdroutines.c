#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <assert.c>

#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/crc16.h>

#define TEST_KEY_ARR_SIZE 128

#include "lcd.h"
#include "kbd.h"
#include "ep_store.h"
#include "i2c.h"
#include "menu.h"

/* All Header overrides */
#undef  SD_ITEM_FILE
#define SD_ITEM_FILE "test_data/items_1.dat"

#include "lcd.c"
#include "kbd.c"
#include "ep_store.c"
#include "i2c.c"
#include "ff.c"
#include "menu.c"

int
main(void)
{
  uint16_t ui16_1, ui16_2;
  struct item *it = (void *)bufSS;
  
  menuSDLoadItem(MENU_MSUPER);

  for (ui16_1 = 0; (EEPROM_ADDR_INVALID-ui16_1)>ITEM_SIZEOF;
       ui16_1 += (ITEM_SIZEOF>>EEPROM_MAX_DEVICES_LOGN2)) {
    assert(ITEM_SIZEOF == ee24xx_read_bytes(ui16_1, bufSS, ITEM_SIZEOF));
    if (0 == it->name[0]) break;

    printf("addr:%x loop : ", ui16_1);
    for (ui16_2=0; ui16_2<ITEM_SIZEOF; ui16_2++) {
      printf("%x ", bufSS[ui16_2]);
    }
    printf("\n");
    it->name[ITEM_NAME_BYTEL-1] = 0;
    printf("item sizeof:%d -2:%d -1:%d\n", ITEM_SIZEOF, bufSS[ITEM_SIZEOF-2], bufSS[ITEM_SIZEOF-1]);
    printf("item name:%s\n", it->name);
    printf("item discount:%d\n", it->discount);
    printf("item cost:%d\n", it->cost);
    printf("item id:%d\n", it->id);
    //    printf("item prod_code:%s\n", it->prod_code);
    printf("item vat_sel:%d\n", it->vat_sel);
    printf("item has_cess2:%d\n", it->has_cess2);
    printf("item has_weighing_mc:%d\n", it->has_weighing_mc);
    printf("item name_in_unicode:%d\n", it->name_in_unicode);
    printf("item has_cess1:%d\n", it->has_cess1);
    printf("item is_biller_item:%d\n", it->is_biller_item);
    printf("item has_common_discount:%d\n", it->has_common_discount);
    printf("item has_serv_tax:%d\n", it->has_serv_tax);
    printf("item is_valid_item:%d\n", it->is_valid_item);
    printf("item unused_5:%d\n", it->unused_5);
    printf("item unused_4:%d\n", it->unused_4);
    printf("item unused_3:%d\n", it->unused_3);
    printf("item unused_2:%d\n", it->unused_2);
    printf("item unused_1:%d\n", it->unused_1);
  }

  return 0;
}