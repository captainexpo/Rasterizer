# App source files
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS include/*.h)

# Build the executable
add_executable(RasterizerApp ${APP_SOURCES} ${APP_HEADERS})

# Include directories
target_include_directories(RasterizerApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the library
target_link_libraries(RasterizerApp RasterizerLib)

# Link raylib and OpenMP
find_package(OpenMP)
if(OpenMP_C_FOUND)
  target_link_libraries(RasterizerApp OpenMP::OpenMP_C)
endif()

find_package(raylib REQUIRED)
target_link_libraries(RasterizerApp raylib m png)

