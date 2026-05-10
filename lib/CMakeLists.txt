add_library(open-simplex-noise open-simplex-noise.c)

target_include_directories(open-simplex-noise
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}

)