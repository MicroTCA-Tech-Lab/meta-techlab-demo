# Yocto demo layer for DAMC-FMC2ZUP and DAMC-FMC1Z7IO

This is the application layer to build the demo images for DAMC-FMC2ZUP/-FMC1Z7IO.

It contains demo FPGA bitstreams and demo software applications.

## FPGA variant

For different FPGA variants, different .xsa files are provided in [recipes-demo/hdf](recipes-demo/hdf).

* If the FPGA manager is enabled, all applicable FPGA bitstream are included in the image, and the appropriate one will be chosen at runtime, depending on the actual chip variant
  (see `recipes-bsp/fpgautil-init/fpgautil-init.bb` in `meta-techlab-bsp`)

* If the FPGA manager is not enabled, the bitstream is selected with `ZUP_FPGA_VARIANT` or `Z7IO_FPGA_VARIANT`, respectively, in the `local.conf`.
