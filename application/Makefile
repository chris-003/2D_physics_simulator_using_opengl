.PHONY: default
default: build

include $(MAKEFILE_COMMON)

.PHONY: build
build: main

main: $(OBJ) $(TOP_DIRECTORY)/engine/libengine.a $(TOP_DIRECTORY)/glad/libglad.a
	@echo Link application/main
	@$(CXX) $(LFLAGS) $(OBJ) $(TOP_DIRECTORY)/engine/libengine.a $(TOP_DIRECTORY)/glad/libglad.a -o main

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@rm -f ./main