.PHONY: default
default: build

include $(MAKEFILE_COMMON)

.PHONY: build
build: $(SUBDIRECCTORY) $(OBJ)
	@echo Link libengine.a
	@$(AR) r libengine.a $(OBJ)

.PHONY: clean
clean: $(SUBDIRECCTORY_CLEAN)
	@rm -f $(OBJ)
	@rm -f libengine.a