COMPATIBLE_MACHINE = "damc-fmc2zup"

require recipes-core/images/techlab-common.inc

IMAGE_INSTALL_append = " packagegroup-zup-support"
IMAGE_INSTALL_append = " packagegroup-zup-demo"
