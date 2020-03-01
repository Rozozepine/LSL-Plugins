OBS_INCLUDE = /usr/include/obs/
OBS_LIB = /usr/lib
LDFLAGS  = -L$(OBS_LIB)
LDLIBS_LIB   = -lobs

C_FLAG = -Wall -g -fPIC -I$(OBS_INCLUDE)
CC = gcc


PLUGIN_NAME = lls-filter
SRC = lls_filter.c lls_plugin.c
LIB = build/lls-plugin.so
OBJ= build/lls_filter.o build/lls_plugin.o

PLUGIN_BUILD_DIR = build/
PLUGIN_INSTALL_DIR = /usr/lib/obs-plugins/
PLUGIN_INSTALL_DATA_DIR = /usr/share/obs/obs-plugins/
PLUGIN_DATA_DIR = data
ARCH = $(shell getconf LONG_BIT)
PLUGIN_BIN_DIR = $(PLUGIN_BUILD_DIR)/bin/$(ARCH)bit

all: plugin

.PHONY:plugin
plugin: $(LIB)
	mkdir -p $(PLUGIN_BIN_DIR)
	cp $(LIB) $(PLUGIN_BIN_DIR)



.PHONY:install 
install: 
	sudo mkdir -p $(PLUGIN_INSTALL_DATA_DIR)/$(PLUGIN_NAME)
	sudo cp -r $(LIB) $(PLUGIN_INSTALL_DIR)
	sudo cp -r $(PLUGIN_DATA_DIR) $(PLUGIN_INSTALL_DATA_DIR)/$(PLUGIN_NAME)
	

$(LIB): $(OBJ)
	$(CC) -shared $(LDFLAGS) $^ $(LDLIBS_LIB) -o $@

build/%.o: %.c
	$(CC) -c $(C_FLAG) $< -o $@ $(LDLIBS_LIB)
