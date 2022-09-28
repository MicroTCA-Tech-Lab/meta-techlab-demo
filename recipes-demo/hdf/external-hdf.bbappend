# Different PL bitstream variants to be included in the Yocto image:
# For the demo image it is the same logic built for different FPGA chip variants,
# but it could also be different versions / variants of a bitstream etc.

PL_VARIANTS_damc-fmc2zup = "zu11eg zu19eg"
PL_VARIANTS_damc-fmc1z7io-rev-b = "7z030 7z035"
PL_VARIANTS_damc-fmc1z7io-rev-a = "7z030 7z045"

# Default variant is selected if fpga-manager is not enabled
PL_DEFAULT_VARIANT_damc-fmc2zup = "${ZUP_FPGA_VARIANT}"
PL_DEFAULT_VARIANT_damc-fmc1z7io = "${Z7IO_FPGA_VARIANT}"

HDF_BASE = "file://${PL_DEFAULT_VARIANT}/"
HDF_PATH_damc-fmc2zup = "damc_fmc2zup_top.xsa"
HDF_PATH_damc-fmc1z7io = "damc_fmc1z7io_top.xsa"

S = "${WORKDIR}"
SRC_URI += " file://*"

FILESEXTRAPATHS_prepend := "${THISDIR}/${MACHINE}:"
