PKG_SUFFIX = "-example-design"

PL_VARIANTS_damc-fmc2zup = "zu11eg zu19eg"
ZUP_FPGA_VARIANT ?= "zu11eg"

PL_VARIANTS_damc-fmc1z7io = "7z030 7z035"
PL_VARIANTS_damc-fmc1z7io-rev-a = "7z030 7z045"
Z7IO_FPGA_VARIANT ?= "7z030"

# Default variant is selected if fpga-manager is not enabled
PL_VARIANTS_DEFAULT_damc-fmc2zup = "${ZUP_FPGA_VARIANT}"
PL_VARIANTS_DEFAULT_damc-fmc1z7io = "${Z7IO_FPGA_VARIANT}"
PL_VARIANTS_DEFAULT_damc-motctrl = "test"
