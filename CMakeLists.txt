cmake_minimum_required(VERSION 3.0)

project(anemone-alpha)

file(GLOB SOURCES "*.c" "engine/*.c")
file(GLOB HEADERS "*.h" "engine/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
)

if(PSP)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2_ttf
		SDL2_image
        freetype
        m
        bz2
        png16
		jpeg
        z
    )
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH ICON0.png
        BACKGROUND_PATH ICON1.png
        PREVIEW_PATH NULL
        TITLE "anemone alpha"
    )
endif()
