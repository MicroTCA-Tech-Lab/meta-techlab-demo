FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_damc-fmc1z7io += " \
    file://cma_pool_64mib.dtsi \
"

do_configure_append_damc-fmc1z7io() {
    # Increase CMA pool to 64MiB to make space for demo application
    echo '#include "cma_pool_64mib.dtsi"' >> ${DT_FILES_PATH}/system-top.dts
}
