cmake_minimum_required(VERSION 3.10)
project(TUBES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Direktori output untuk executable, library, dan archive
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Include direktori
include_directories(${CMAKE_SOURCE_DIR}/include)

# Sumber kode
set(SOURCES
    src/main.c

    lib/auth.c
    lib/bioskop.c
    lib/db.c
    lib/film.c
    lib/jadwal.c
    lib/kota.c
    lib/menu.c
    lib/security.c
    lib/studio.c
    lib/user.c
    lib/petugas.c
)

# Buat executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Properti target (harus setelah add_executable)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Include dan Link direktori serta library
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE crypto ssl)

# Opsi tambahan untuk kompilasi
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# Buat direktori untuk runtime output jika belum ada
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Copy folder db ke direktori output
file(COPY ${CMAKE_SOURCE_DIR}/db DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
