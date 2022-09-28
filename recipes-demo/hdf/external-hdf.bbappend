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
HDF_NAME = "only-used-for-git"
HDF_EXT = "xsa"

S = "${WORKDIR}"
SRC_URI += " file://*"

FILESEXTRAPATHS_prepend := "${THISDIR}/${MACHINE}:"

do_install() {
    if [ ${FPGA_MNGR_RECONFIG_ENABLE} = "1" ]; then
        # Put design.xsa into subfolders for each variant
        HW_DESIGNS=${D}/opt/xilinx/hw-design
        for VARIANT in ${PL_VARIANTS}; do
            VARIANT_DIR=${HW_DESIGNS}/${VARIANT}
            echo installing ${VARIANT} to ${VARIANT_DIR}
            install -d ${VARIANT_DIR}
            install -m 0644 ${WORKDIR}/${VARIANT}/${HDF_PATH} ${VARIANT_DIR}/design.xsa
        done
        # Save list of variants for dependents (device-tree, bitstream-extraction)
        echo -n "${PL_VARIANTS}" > ${HW_DESIGNS}/pl-variants
    else
        install -d ${D}/opt/xilinx/hw-design
        install -m 0644 ${WORKDIR}/${PL_DEFAULT_VARIANT}/${HDF_PATH} ${D}/opt/xilinx/hw-design/design.xsa
    fi
}

do_deploy() {
    install -d ${DEPLOYDIR}
    install -m 0644 ${WORKDIR}/${PL_DEFAULT_VARIANT}/${HDF_PATH} ${DEPLOYDIR}/Xilinx-${MACHINE}.${HDF_EXT}
}

python () {
    if d.getVar('FPGA_MNGR_RECONFIG_ENABLE', True) == '1':
        d.setVar('PL_VARIANT_FILES',
            '/opt/xilinx/hw-design/pl-variants ' +
            ' '.join(
                '/opt/xilinx/hw-design/' + v + '/design.xsa'
                for v in d.getVar('PL_VARIANTS', True).split(' ')
            )
        )
    else:
        d.setVar('PL_VARIANT_FILES', '')
}

FILES_${PN} += "${PL_VARIANT_FILES}"
