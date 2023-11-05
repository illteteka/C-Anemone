if(PSP)
cmake_minimum_required(VERSION 3.0)
elseif(WIN32)
cmake_minimum_required(VERSION 3.5)
elseif(UNIX)
cmake_minimum_required(VERSION 3.5)
endif()

project(anemone-alpha)

if(WIN32)
set(CMAKE_GENERATOR_PLATFORM x64)
elseif(UNIX)
set(CMAKE_GENERATOR_PLATFORM x64)
endif()

file(GLOB SOURCES "*.c" "engine/*.c" "levels/*.c" "objects/*.c")
file(GLOB HEADERS "*.h" "engine/*.h" "levels/*.h" "objects/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${SDL2_LIBRARIES}
)

if(PSP)
	set(BUILD_PRX 1)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		SDL2_image
		png16
		jpeg
		z
		osl
		pspaudiolib
		pspaudio
	)
	create_pbp_file(
		TARGET ${PROJECT_NAME}
		ICON_PATH ICON0.png
		BACKGROUND_PATH ICON1.png
		PREVIEW_PATH NULL
		TITLE "anemone alpha"
	)
elseif(WIN32)
		target_link_libraries(${PROJECT_NAME} PRIVATE
		SDL2_image
		SDL2_mixer
		png16
		jpeg
		z
	)
elseif(UNIX)
		target_link_libraries(${PROJECT_NAME} PRIVATE
		SDL2_image
		SDL2_mixer
		m
	)
endif()
