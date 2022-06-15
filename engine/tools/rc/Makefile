.PHONY: default
default: build

include $(MAKEFILE_COMMON)

.PHONY: build
build: rc

rc: $(OBJ)
	@echo Link engine/tools/rc/rc
	@$(CXX) $(OBJ) -o rc

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@rm -f ./rc