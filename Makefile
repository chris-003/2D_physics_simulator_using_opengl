TOP_DIRECTORY := $(shell pwd)
export TOP_DIRECTORY
MAKEFILE_COMMON := $(TOP_DIRECTORY)/Makefile.common
export MAKEFILE_COMMON

.PHONY: default
default: build

include $(MAKEFILE_COMMON)
CFLAGS += -I $(TOP_DIRECTORY)/ -I /usr/include/freetype2/
export CFLAGS


.PHONY: build
build: $(SUBDIRECCTORY)
	
application/:engine/
application/:glad/

.PHONY: clean
clean: $(SUBDIRECCTORY_CLEAN)
