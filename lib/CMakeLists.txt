
# Library source files
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS include/*.h)

# Build the library
add_library(RasterizerLib STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set include directories for the library
target_include_directories(RasterizerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
