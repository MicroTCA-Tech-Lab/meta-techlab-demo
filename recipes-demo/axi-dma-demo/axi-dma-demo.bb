COMPATIBLE_MACHINE = "damc-fmc1z7io|damc-fmc2zup"

DESCRIPTION = "AXI DMA demo"
LICENSE = "BSD"
PV = "1.1.1"
PR = "r0"

DEPENDS = "boost libudmaio"
RDEPENDS_${PN} = "boost-log boost-program-options libudmaio"

inherit pkgconfig cmake update-rc.d

SRCREV = "43addd408a7cf70a2ff4c0aa8a2f434f242be818"
SRC_URI = "git://github.com/MicroTCA-Tech-Lab/libudmaio.git;protocol=https"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=e218aa5496fc02972b9c9425e527094c"

EXTRA_OECMAKE_damc-fmc2zup = "-DCMAKE_SKIP_RPATH=TRUE -DTARGET_HW=ZUP"
EXTRA_OECMAKE_damc-fmc1z7io = "-DCMAKE_SKIP_RPATH=TRUE -DTARGET_HW=Z7IO"

S="${WORKDIR}/git"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = "            \
    file://init.d/udmabuf     \
"

FILES_${PN}_append = "               \
    /etc/init.d/udmabuf              \
"

INITSCRIPT_NAME = "udmabuf"
INITSCRIPT_PARAMS = "defaults 90"

do_install() {
    # Example application
    install -d ${D}${bindir}
    install -m 0755 axi_dma_demo_cpp ${D}${bindir}

    # UDmaBuf allocation
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/init.d/udmabuf ${D}${sysconfdir}/init.d/
}
