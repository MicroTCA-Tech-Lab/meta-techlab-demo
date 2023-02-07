# Different PL bitstream variants to be included in the Yocto image:
# For the demo image it is the same logic built for different FPGA chip variants,
# but it could also be different versions / variants of a bitstream etc.

PL_VARIANTS_DIR := "${THISDIR}/${MACHINE}"

ZUP_FPGA_VARIANT ?= "zu11eg"
Z7IO_FPGA_VARIANT ?= "7z030"

# Default variant is selected if fpga-manager is not enabled
PL_VARIANTS_DEFAULT_damc-fmc2zup = "${ZUP_FPGA_VARIANT}"
PL_VARIANTS_DEFAULT_damc-fmc1z7io = "${Z7IO_FPGA_VARIANT}"
PL_VARIANTS_DEFAULT_damc-motctrl = "test"

HDF_BASE = "file://"
# this can only be a single file; take the default variant
HDF_PATH_damc-fmc2zup = "${PL_VARIANTS_DEFAULT_damc-fmc2zup}.xsa"
HDF_PATH_damc-fmc1z7io = "${PL_VARIANTS_DEFAULT_damc-fmc1z7io}.xsa"
HDF_PATH_damc-motctrl = "damc_motctrl_top.xsa"

S = "${WORKDIR}"

FILESEXTRAPATHS_prepend := "${THISDIR}/${MACHINE}:"
