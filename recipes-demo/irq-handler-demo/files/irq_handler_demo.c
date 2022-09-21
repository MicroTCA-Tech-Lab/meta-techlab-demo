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

#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "custom_irq_gen.h"

void print_usage(const char *prog_name) {
  printf("Usage: %s --mmap_dev MMAP_DEV [--event_dev EVENT_DEV] --count COUNT\n"
         "        --period PERIOD [--addr ADDR]\n",
         prog_name);

  printf("\n\n");
  printf("Arguments:\n");
  printf("  mmap_dev  : register access device\n");
  printf("  event_dev : event device, if not specified mmap_dev is used\n");
  printf("  count     : number of request to be handeled\n");
  printf(
      "  period    : number of FPGA clock cycles between interrupt requests\n");
  printf("  addr      : hardware address of the IP, only needed for xdma\n");
  printf("\n\n");
  printf("Example usage (over PCIe with xdma driver):\n");
  printf("\n");
  printf("  ./irq_handler_demo \\\n"
         "    --mmap_dev /dev/xdma/slot11/user \\\n"
         "    --event_dev /dev/xdma/slot11/events1 \\\n"
         "    --count 1000 \\\n"
         "    --period 100000 \\\n"
         "    --addr 0x310000\n");
  printf("\n\n");
  printf("Example usage (on ARM with UIO driver):\n");
  printf("\n");
  printf("  ./irq_handler_demo \\\n"
         "    --mmap_dev /dev/uio14 \\\n"
         "    --count 1000 \\\n"
         "    --period 100000\n");
}

int main(int argc, char *argv[]) {

  // clang-format off
  struct option long_options[] = {
      { "help",      no_argument,       0, 'h' },
      { "mmap_dev",  required_argument, 0, 'd' },
      { "event_dev", required_argument, 0, 'e' },
      { "count",     required_argument, 0, 'c' },
      { "period",    required_argument, 0, 'p' },
      { "addr",      required_argument, 0, 'a' },
      { 0, 0, 0, 0 },
  };
  // clang-format on

  char *mmap_dev = NULL, *event_dev = NULL;
  uint32_t count = 0, period = 0;
  uint64_t addr = 0;

  while (1) {
    int c = getopt_long(argc, argv, "hd:e:c:p:a:", long_options, NULL);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 'a':
      addr = strtoul(optarg, NULL, 0);
      break;
    case 'c':
      count = strtoul(optarg, NULL, 0);
      break;
    case 'p':
      period = strtoul(optarg, NULL, 0);
      break;
    case 'd':
      mmap_dev = optarg;
      break;
    case 'e':
      event_dev = optarg;
      break;
    case 'h':
      print_usage(argv[0]);
      return EXIT_SUCCESS;
    case '?':
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
  }

  if (!mmap_dev || (period == 0) || (count == 0)) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  if (!event_dev) {
    event_dev = mmap_dev;
  }

  printf("Arguments summary:\n");
  printf("  mmap_dev  = %s\n", mmap_dev);
  printf("  event_dev = %s\n", event_dev);
  printf("  address   = 0x%08lx\n", addr);
  printf("  count     = %d\n", count);
  printf("  period    = %d\n", period);

  int fd_mmap = open(mmap_dev, O_RDWR | O_SYNC);
  if (fd_mmap < 0) {
    perror("open(mmap_dev)");
    return EXIT_FAILURE;
  }

  int fd_event = open(event_dev, O_RDWR | O_SYNC);
  if (fd_event < 0) {
    perror("open(event_dev)");
    return EXIT_FAILURE;
  }

  void *map =
      mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mmap, addr);
  if (!map) {
    perror("mmap()");
  }

  if (check_id(map)) {
    return EXIT_FAILURE;
  }

  uint32_t *latencies = calloc(count, sizeof(uint32_t));
  uint32_t lat_idx = 0;

  period_set(map, period);
  printf("period readback = 0x%x\n", period_get(map));

  irq_enable(map, 0);
  irq_handle(map);
  printf("cleared irq state\n");
  irq_enable(map, 1);

  uint32_t data;
  uint32_t reenable_irq = 1;
  uint32_t seq_nr_exp = 0;
  write(fd_event, &reenable_irq, 4);

  while (1) {
    read(fd_event, &data, 4);
    uint32_t seq_nr = irq_handle(map);
    if (seq_nr_exp != seq_nr) {
      printf("seq nr mismatch (exp = %x, recv = %x)\n", seq_nr_exp, seq_nr);
    }

    latencies[lat_idx++] = latency_get(map);
    if (seq_nr_exp == count - 1) {
      break;
    }
    seq_nr_exp = seq_nr + 1;

    write(fd_event, &reenable_irq, 4);
  }

  for (uint32_t i = 0; i < count - 1; i++) {
    printf("latency[%d] = %d\n", i, latencies[i]);
  }

  return EXIT_SUCCESS;
}
