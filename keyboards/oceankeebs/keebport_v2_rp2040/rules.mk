# Build Options
#   change yes to no to disable
#
WPM_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

CUSTOM_MATRIX = lite

SRC += matrix.c trackpad.c IQS5xx.c 

# Project specific files
QUANTUM_LIB_SRC += i2c_master.c