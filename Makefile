PORT_AUDIO_DIR = vendor/portaudio
PORT_AUDIO_LIB = $(PORT_AUDIO_DIR)/lib/.libs/libportaudio.a
PORT_AUDIO_MAKEFILE = $(PORT_AUDIO_DIR)/Makefile
FRAMEWORKS = -framework CoreAudio -framework AudioToolbox \
	-framework AudioUnit -framework CoreFoundation -framework CoreServices
INCLUDE_DIRS = -I$(PORT_AUDIO_DIR)/include -Ivendor/rapidjson/include \
	-Ivendor/concurrentqueue
SOURCES = $(wildcard src/*.cc src/modules/*.cc)
HEADERS = $(wildcard src/*.hh src/modules/*.hh)

all: main

main: $(SOURCES) $(HEADERS) $(PORT_AUDIO_LIB)
	g++ -Isrc $(INCLUDE_DIRS) $(PORT_AUDIO_LIB) $(FRAMEWORKS) \
		$(SOURCES)  -o main

$(PORT_AUDIO_LIB): $(PORT_AUDIO_MAKEFILE)
	cd $(PORT_AUDIO_DIR) && make

$(PORT_AUDIO_MAKEFILE):
	cd $(PORT_AUDIO_DIR) && ./configure --prefix=$(pwd)/$(PORT_AUDIO_DIR)

clean:
	rm -f main
	cd $(PORT_AUDIO_DIR) && make clean

.PHONY: all clean

