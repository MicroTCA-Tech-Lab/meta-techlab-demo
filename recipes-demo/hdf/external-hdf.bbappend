ZUP_FPGA_VARIANT ?= "zu11eg"
Z7IO_FPGA_VARIANT ?= "7z030"

# Default variant is selected if fpga-manager is not enabled
PL_VARIANTS_DEFAULT_damc-fmc2zup = "${ZUP_FPGA_VARIANT}"
PL_VARIANTS_DEFAULT_damc-fmc1z7io = "${Z7IO_FPGA_VARIANT}"

HDF_BASE = "file://"
# For the motion controller & UNIZUP, do not use PL_VARIANTS, but HDF_PATH
HDF_PATH_damc-motctrl = "test.xsa"
HDF_PATH_damc-unizup = "test.xsa"

S = "${WORKDIR}"

FILESEXTRAPATHS_prepend := "${THISDIR}/${MACHINE}:"
PL_VARIANTS_DIR := "${THISDIR}/${MACHINE}"
