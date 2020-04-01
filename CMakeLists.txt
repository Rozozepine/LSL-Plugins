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
	src/lsl_plugin.cpp
	src/lsl_plugin_prop.cpp)
    
set(lsl_plugin_HEADERS
	src/header/lsl_output.h
	src/header/lsl_plugin_prop.h)

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
		DESTINATION "${CMAKE_INSTALL_PREFIX}/share/obs/obs-plugins/lsl_plugin/locale")
endif()

# Windows
if(WIN32)
	set(OBS_FRONTEND_LIB "OBS_FRONTEND_LIB-NOTFOUND" CACHE FILEPATH "OBS frontend library")
	if(OBS_FRONTEND_LIB EQUAL "OBS_FRONTEND_LIB-NOTFOUND")
		message(FATAL_ERROR "Could not find OBS Frontend API\'s library !")
	endif()

    if(MSVC)
	    add_compile_options("/MP")
    endif()

	add_definitions(/O2)
	string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	message("${CMAKE_CXX_FLAGS_RELEASE}")

	if(ARCH EQUAL 64)
		set(OBS_ARCH_NAME "64bit")
		set(OBS_BUILDDIR_ARCH "build64")
	else()
		set(OBS_ARCH_NAME "32bit")
		set(OBS_BUILDDIR_ARCH "build32")
		add_definitions(/arch:SSE2)
	endif()

	target_link_libraries(lsl_plugin
		obs-frontend-api)

	set(RELEASE_DIR "${PROJECT_SOURCE_DIR}/release")
	add_custom_command(TARGET lsl_plugin POST_BUILD
        # If config is Release, package release files
		COMMAND if $<CONFIG:Release>==1 (
			"${CMAKE_COMMAND}" -E make_directory
				"${RELEASE_DIR}/data/obs-plugins/lsl_plugin"
				"${RELEASE_DIR}/obs-plugins/${OBS_ARCH_NAME}")

		COMMAND if $<CONFIG:Release>==1 (
			"${CMAKE_COMMAND}" -E copy_directory
				"${PROJECT_SOURCE_DIR}/data"
				"${RELEASE_DIR}/data/obs-plugins/lsl_plugin")

		COMMAND if $<CONFIG:Release>==1 (
			"${CMAKE_COMMAND}" -E copy
				"$<TARGET_FILE:lsl_plugin>"
				"${RELEASE_DIR}/obs-plugins/${OBS_ARCH_NAME}")

        # If config is RelWithDebInfo, package release files
		COMMAND if $<CONFIG:RelWithDebInfo>==1 (
			"${CMAKE_COMMAND}" -E make_directory
			    "${RELEASE_DIR}/data/obs-plugins/lsl_plugin"
			    "${RELEASE_DIR}/obs-plugins/${OBS_ARCH_NAME}")

		COMMAND if $<CONFIG:RelWithDebInfo>==1 (
            "${CMAKE_COMMAND}" -E copy_directory
			    "${PROJECT_SOURCE_DIR}/data"
			    "${RELEASE_DIR}/data/obs-plugins/lsl_plugin")

		COMMAND if $<CONFIG:RelWithDebInfo>==1 (
            "${CMAKE_COMMAND}" -E copy
			    "$<TARGET_FILE:lsl_plugin>"
			    "${RELEASE_DIR}/obs-plugins/${OBS_ARCH_NAME}")

		COMMAND if $<CONFIG:RelWithDebInfo>==1 (
            "${CMAKE_COMMAND}" -E copy
			    "$<TARGET_PDB_FILE:lsl_plugin>"
			    "${RELEASE_DIR}/obs-plugins/${OBS_ARCH_NAME}")

		# Copy to obs-studio dev environment for immediate testing
		COMMAND if $<CONFIG:Debug>==1 (
			"${CMAKE_COMMAND}" -E copy
				"$<TARGET_FILE:lsl_plugin>"
				"${LIBOBS_INCLUDE_DIR}/../${OBS_BUILDDIR_ARCH}/rundir/$<CONFIG>/obs-plugins/${OBS_ARCH_NAME}")

		COMMAND if $<CONFIG:Debug>==1 (
			"${CMAKE_COMMAND}" -E make_directory
				"${LIBOBS_INCLUDE_DIR}/../${OBS_BUILDDIR_ARCH}/rundir/$<CONFIG>/data/obs-plugins/lsl_plugin")

		COMMAND if $<CONFIG:Debug>==1 (
			"${CMAKE_COMMAND}" -E copy_directory
				"${PROJECT_SOURCE_DIR}/data"
				"${LIBOBS_INCLUDE_DIR}/../${OBS_BUILDDIR_ARCH}/rundir/$<CONFIG>/data/obs-plugins/lsl_plugin")
	)
endif()