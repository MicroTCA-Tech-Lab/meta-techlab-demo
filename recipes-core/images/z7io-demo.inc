COMPATIBLE_MACHINE = "damc-fmc1z7io"

require recipes-core/images/techlab-common.inc

IMAGE_INSTALL_append = " packagegroup-z7io-support"
IMAGE_INSTALL_append = " packagegroup-z7io-demo"
