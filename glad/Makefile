.PHONY: default
default: build

include $(MAKEFILE_COMMON)

.PHONY: build
build: $(OBJ)
	@echo Link libglad.a
	@$(AR) r libglad.a $(OBJ)

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@rm -f libglad.a