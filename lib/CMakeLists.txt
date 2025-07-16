
# lib/CMakeLists.txt

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS include/*.h)

add_library(RasterizerLib STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Include headers
target_include_directories(RasterizerLib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /opt/homebrew/include  # <- raylib, png.h, etc.
)

# Link raylib and png (zlib is auto by raylib)
target_link_libraries(RasterizerLib PUBLIC
  raylib
  png
)
