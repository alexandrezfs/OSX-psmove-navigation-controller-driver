cmake_minimum_required(VERSION 2.8)
project(OSX-psmove-navigation-controller-driver)


find_path(HIDAPI_INCLUDE_DIR
        NAMES
        hidapi.h
        PATHS
        /usr/local/include
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(HIDAPI
        DEFAULT_MSG
        HIDAPI_LIBRARY
        HIDAPI_INCLUDE_DIR)

if(HIDAPI_FOUND)
    set(HIDAPI_LIBRARIES "${HIDAPI_LIBRARY}")
    set(HIDAPI_INCLUDE_DIRS "${HIDAPI_INCLUDE_DIR}")
endif()

mark_as_advanced(HIDAPI_INCLUDE_DIR HIDAPI_LIBRARY)


include_directories(${HIDAPI_INCLUDE_DIR})

list(APPEND PSMOVEAPI_REQUIRED_LIBS ${HIDAPI_LIBRARIES})



set(SOURCE_FILES src/nav.c)



add_library(OSX-psmove-navigation-controller-driver STATIC ${SOURCE_FILES})

target_link_libraries(OSX-psmove-navigation-controller-driver ${PSMOVEAPI_REQUIRED_LIBS})


