OBS_INCLUDE = /usr/include/obs/
API_INCLUDE = lib/header/
OBS_LIB = /usr/lib
API_LIB = lib/
LDFLAGS  = -L$(OBS_LIB) -L$(API_LIB)
LDLIBS_LIB   = -lobs -lobs-frontend-api -llsl64

C_FLAG = -Wall -g -fPIC -I$(OBS_INCLUDE) -I$(API_INCLUDE)
CC = gcc

ARCH = $(shell getconf LONG_BIT)
PLUGIN_BIN_DIR = $(PLUGIN_BUILD_DIR)/bin/$(ARCH)bit

PLUGIN_NAME = lsl-filter
SRC = src/lsl_plugin.c src/lsl_filter.c
LIB = $(PLUGIN_BIN_DIR)/$(PLUGIN_NAME).so
OBJ= build/obj/lsl_plugin.o  build/obj/lsl_filter.o

PLUGIN_BUILD_DIR = build/
PLUGIN_DATA_DIR = data

PLUGIN_INSTALL_DIR = /usr/lib/obs-plugins/
PLUGIN_INSTALL_DATA_DIR = /usr/share/obs/obs-plugins/


all: $(LIB)

.PHONY:plugin
plugin: $(LIB)
	

.PHONY:install 
install: 
	sudo mkdir -p $(PLUGIN_INSTALL_DATA_DIR)/$(PLUGIN_NAME)
	sudo cp -r $(LIB) $(PLUGIN_INSTALL_DIR)
	sudo cp -r $(PLUGIN_DATA_DIR) $(PLUGIN_INSTALL_DATA_DIR)/$(PLUGIN_NAME)
	

$(LIB): $(OBJ)
	$(CC) -shared $(LDFLAGS) $^ $(LDLIBS_LIB) -o $@

build/obj/%.o: src/%.c
	$(CC) -c $(C_FLAG) $< -o $@ $(LDLIBS_LIB)


