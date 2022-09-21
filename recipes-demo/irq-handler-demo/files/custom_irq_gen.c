//---------------------------------------------------------------------------//
//        ____  _____________  __    __  __ _           _____ ___   _        //
//       / __ \/ ____/ ___/\ \/ /   |  \/  (_)__ _ _ __|_   _/ __| /_\       //
//      / / / / __/  \__ \  \  /    | |\/| | / _| '_/ _ \| || (__ / _ \      //
//     / /_/ / /___ ___/ /  / /     |_|  |_|_\__|_| \___/|_| \___/_/ \_\     //
//    /_____/_____//____/  /_/      T  E  C  H  N  O  L  O  G  Y   L A B     //
//                                                                           //
//---------------------------------------------------------------------------//

// Copyright (c) 2020-2021 Deutsches Elektronen-Synchrotron DESY.
//                         All rights reserved

#include <stdio.h>

#include "custom_irq_gen.h"
#include "custom_irq_gen_regs.h"

uint32_t _rd32(void *map, uintptr_t reg_byte_addr) {
  return *(uint32_t *)((uintptr_t)map + reg_byte_addr);
}

void _wr32(void *map, uintptr_t reg_byte_addr, uint32_t data) {
  *(uint32_t *)((uintptr_t)map + reg_byte_addr) = data;
}

int check_id(void *map) {
  uint32_t id_reg = _rd32(map, CUSTOM_IRQ_GEN_ADDR_REG_ID);

  if (id_reg == CUSTOM_IRQ_GEN_REG_ID_ID_RST_VAL) {
    printf("check_id: ID register matches\n");
  } else {
    printf("check_id: ID register does not match\n");
    return -1;
  }

  return 0;
}

uint32_t period_get(void *map) {
  return _rd32(map, CUSTOM_IRQ_GEN_ADDR_REG_GEN_PERIOD);
}

uint32_t latency_get(void *map) {
  return _rd32(map, CUSTOM_IRQ_GEN_ADDR_REG_HANDLER_LATENCY);
}

void period_set(void *map, uint32_t period) {
  _wr32(map, CUSTOM_IRQ_GEN_ADDR_REG_GEN_PERIOD, period);
}

void irq_enable(void *map, int enable) {
  if (enable) {
    _wr32(map, CUSTOM_IRQ_GEN_ADDR_REG_GEN_EN,
          CUSTOM_IRQ_GEN_REG_GEN_EN_GEN_EN_MASK
              << CUSTOM_IRQ_GEN_REG_GEN_EN_GEN_EN_SHIFT);
  } else {
    _wr32(map, CUSTOM_IRQ_GEN_ADDR_REG_GEN_EN, 0);
  }
}

uint32_t irq_handle(void *map) {
  uint32_t seq_nr = _rd32(map, CUSTOM_IRQ_GEN_ADDR_REG_IRQ_SEQ);

  _wr32(map, CUSTOM_IRQ_GEN_ADDR_REG_CLR_IRQ,
        CUSTOM_IRQ_GEN_REG_CLR_IRQ_CLR_IRQ_MASK
            << CUSTOM_IRQ_GEN_REG_CLR_IRQ_CLR_IRQ_SHIFT);

  return seq_nr;
}
