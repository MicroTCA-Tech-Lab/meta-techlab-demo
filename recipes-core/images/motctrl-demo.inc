COMPATIBLE_MACHINE = "damc-motctrl"

require recipes-core/images/techlab-common.inc

IMAGE_INSTALL_append = " packagegroup-motctrl-support"
