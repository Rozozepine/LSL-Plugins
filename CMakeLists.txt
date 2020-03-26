cmake_minimum_required(VERSION 3.5)
project(lsl-plugin VERSION 1)

set(CMAKE_PREFIX_PATH "${QTDIR}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include(external/findLibObs.cmake)
find_package(LibObs REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ARCH 64)
else()
	set(ARCH 32)
endif()

set(lsl-plugin_SOURCES
    src/lsl_output.cpp
    src/lsl_plugin.cpp)
    
set(lsl_plugin_HEADERS
    src/header/lsl_output.h)

add_library(lsl_plugin MODULE
    ${lsl-plugin_SOURCES}
    ${lsl_plugin_HEADERS})



include_directories(
    "lib/header/"
    ${Qt5Core_INCLUDES}
    ${Qt5Widgets_INCLUDES})

target_link_libraries(lsl_plugin
    libobs
    lsl64
	Qt5::Core
    Qt5::Widgets)
    

# Linux
if(UNIX AND NOT APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -mtune=core2 -Ofast")

	if(ARCH EQUAL 64)
		set(ARCH_NAME "x86_64")
	else()
		set(ARCH_NAME "i686")
	endif()

	set_target_properties(lsl_plugin PROPERTIES PREFIX "")

	target_link_libraries(lsl_plugin
		obs-frontend-api)

	file(GLOB locale_files data/locale/*.ini)
        execute_process(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE UNAME_MACHINE)

	install(TARGETS lsl_plugin
                LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/obs-plugins)
	# Dirty fix for Ubuntu
	install(TARGETS lsl_plugin
		LIBRARY DESTINATION usr/lib/obs-plugins)

	install(FILES ${locale_files}
		DESTINATION "${CMAKE_INSTALL_PREFIX}/share/obs/obs-plugins/obs-ndi/locale")
endif()