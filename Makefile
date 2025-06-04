PORT_AUDIO_DIR = vendor/portaudio
PORT_AUDIO_LIB = $(PORT_AUDIO_DIR)/lib/.libs/libportaudio.a
PORT_AUDIO_MAKEFILE = $(PORT_AUDIO_DIR)/Makefile
FRAMEWORKS = -framework CoreAudio -framework AudioToolbox \
	-framework AudioUnit -framework CoreFoundation -framework CoreServices

all: main

main: src/main.cc $(PORT_AUDIO_LIB)
	g++ -Isrc -I$(PORT_AUDIO_DIR)/include $(PORT_AUDIO_LIB) \
		$(FRAMEWORKS) src/main.cc  -o main

$(PORT_AUDIO_LIB): $(PORT_AUDIO_MAKEFILE)
	cd $(PORT_AUDIO_DIR) && make

$(PORT_AUDIO_MAKEFILE):
	cd $(PORT_AUDIO_DIR) && ./configure --prefix=$(pwd)/$(PORT_AUDIO_DIR)

clean:
	rm -f main
	cd $(PORT_AUDIO_DIR) && make clean

.PHONY: all clean

