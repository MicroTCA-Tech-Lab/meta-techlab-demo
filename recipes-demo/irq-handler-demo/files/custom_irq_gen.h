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

#include <stdint.h>

/** check the ID register */
int check_id(void *map);

/** get the period between the interrup request, in clk cycles */
uint32_t period_get(void *map);

/** get the latency of the interrupt handler */
uint32_t latency_get(void *map);

/** set the period (number of clk cycles) between interrupt request */
void period_set(void *map, uint32_t period);

/** enable generation of the interrupts in the IP core */
void irq_enable(void *map, int enable);

/** handle the request - read the sequence number and clear the flags */
uint32_t irq_handle(void *map);
