EXE := prog

BUILD_DIR := build
SOURCE_DIR := source

SOURCES := $(shell find ${SOURCE_DIR} -name *.asm)
OBJECTS := $(SOURCES:%.asm=${BUILD_DIR}/%.o)

all: ${OBJECTS}
	ld ${OBJECTS} -o ${BUILD_DIR}/${EXE}

${BUILD_DIR}/%.o: %.asm
	mkdir -p $(dir $@)
	fasm $^
	mv $(patsubst %.asm,%.o,$^) $(dir $@)

run:
	${BUILD_DIR}/${EXE}

clean:
	rm -rf ${BUILD_DIR}

