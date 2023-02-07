COMPATIBLE_MACHINE = "damc-fmc1z7io|damc-fmc2zup"

DESCRIPTION = "AXI DMA demo"
LICENSE = "BSD"
PV = "1.0.2"
PR = "r0"

DEPENDS = "boost libudmaio"
RDEPENDS_${PN} = "boost-log boost-program-options libudmaio"

inherit pkgconfig cmake

SRCREV = "64b447901b0d37bf546b283ebe68fa104e137685"
SRC_URI = "git://github.com/MicroTCA-Tech-Lab/libudmaio.git;protocol=https"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=e218aa5496fc02972b9c9425e527094c"

EXTRA_OECMAKE_damc-fmc2zup = "-DCMAKE_SKIP_RPATH=TRUE -DTARGET_HW=ZUP"
EXTRA_OECMAKE_damc-fmc1z7io = "-DCMAKE_SKIP_RPATH=TRUE -DTARGET_HW=Z7IO"

S="${WORKDIR}/git"

do_install() {
    # example
    install -d ${D}${bindir}
    install -m 0755 axi_dma_demo_cpp ${D}${bindir}
}
