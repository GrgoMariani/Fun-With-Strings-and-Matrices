MAKEFILE_BUILDER = make -f makefile_builder --no-print-directory


all: symmatrix


SYMMATRIX_SOURCES_CPP := main.cpp

symmatrix:
	@$(MAKEFILE_BUILDER) CPP_TO_COMPILE="$(SYMMATRIX_SOURCES_CPP)" EXE_TARGET="execute_me"

