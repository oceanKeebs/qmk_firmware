# Build Options
#   change yes to no to disable
#

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

MOUSE_ENABLE = yes

CUSTOM_MATRIX = lite

SRC += matrix.c trackpad.c IQS5xx.c 

# Project specific files
QUANTUM_LIB_SRC += spi_master.c i2c_master.c
