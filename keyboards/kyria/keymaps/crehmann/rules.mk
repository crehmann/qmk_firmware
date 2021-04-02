OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes
RGBLIGHT_ENABLE = yes
LEADER_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
DYNAMIC_MACRO_NO_NESTING = yes
MOUSEKEY_ENABLE = yes

TRACKPOINT = 0
ifeq ($(TRACKPOINT), 1)
	PS2_MOUSE_ENABLE = yes
	PS2_USE_INT = yes 
	OLED_DRIVER_ENABLE = no
endif

SPLIT_TRANSPORT = custom

ifeq ($(strip $(SPLIT_TRANSPORT)), custom)
	OPT_DEFS += -DCUSTOM_TRANSPORT
	QUANTUM_SRC += transport_custom.c
	# Functions added via QUANTUM_LIB_SRC are only included in the final binary if they're called.
	# Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
	ifeq ($(PLATFORM),AVR)
		QUANTUM_LIB_SRC += i2c_master.c \
							i2c_slave.c
	endif

	SERIAL_DRIVER ?= bitbang
	ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
		QUANTUM_LIB_SRC += serial.c
	else
		QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
	endif
endif