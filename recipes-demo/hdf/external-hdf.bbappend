FPGA_VARIANT_damc-fmc2zup ?= "zu11eg"
FPGA_VARIANT_damc-fmc1z7io ?= "7z035"

FPGA_VARIANTS_damc-fmc2zup = "zu11eg zu19eg"
FPGA_VARIANTS_damc-fmc1z7io = "7z030 7z035"

HDF_BASE = "file://${FPGA_VARIANT}/"
HDF_PATH_damc-fmc2zup = "damc_fmc2zup_top.xsa"
HDF_PATH_damc-fmc1z7io = "damc_fmc1z7io_top.xsa"
HDF_NAME = "only-used-for-git"
HDF_EXT = "xsa"

S = "${WORKDIR}"
SRC_URI += " file://*"

FILESEXTRAPATHS_prepend := "${THISDIR}/${MACHINE}:"

do_install_append() {
    # Support multiple FPGA variants in one single Yocto image.
    for VARIANT in ${FPGA_VARIANTS}; do
        echo installing $VARIANT
        install -m 0644 ${WORKDIR}/${VARIANT}/${HDF_PATH} ${D}/opt/xilinx/hw-design/design_${VARIANT}.xsa
    done
}

do_deploy_append() {
    # Support multiple FPGA variants in one single Yocto image.
    for VARIANT in ${FPGA_VARIANTS}; do
        echo deploying $VARIANT
        install -m 0644 ${WORKDIR}/${VARIANT}/${HDF_PATH} ${DEPLOYDIR}/Xilinx-${MACHINE}_${VARIANT}.xsa
    done
}

FILES_${PN} += "/opt/xilinx/hw-design/design_*.xsa"
