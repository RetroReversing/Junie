WASI_SDK := $(HOME)/wasi-sdk-13.0
CC       := $(WASI_SDK)/bin/clang --sysroot=$(WASI_SDK)/share/wasi-sysroot -DEMSCRIPTEN
CXX      := $(WASI_SDK)/bin/clang++ --sysroot=$(WASI_SDK)/share/wasi-sysroot -DEMSCRIPTEN
AR       := $(WASI_SDK)/bin/ar

TARGET       := genesisRR 
# quicknes mgba snes9x genesis melonds
TARGET_LIB   := $(addprefix lib, $(addsuffix .a, $(TARGET)))
TARGET_CLEAN := $(TARGET_LIB:%=%-clean)

# Test libRR:
SOURCES_GENRR = ${wildcard genesisRR/*.cpp}
OBJ_GENRR = $(SOURCES_GENRR:genesisRR/%.cpp=genesisRR/%.o)
OBJ := $(SRC:.c=.o)
# End test LibRR

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ_GENRR)
	make -f Makefile.$(@:lib%.a=%) PLATFORM=emscripten CC="$(CC)" CXX="$(CXX)" AR="$(AR)"

clean: $(TARGET_CLEAN)

$(TARGET_CLEAN):
	make -f Makefile.$(@:lib%.a-clean=%) PLATFORM=emscripten clean
	$(RM) $(TARGET_LIB)
