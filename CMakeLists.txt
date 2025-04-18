cmake_minimum_required(VERSION 3.10)

set(reflection_api_qt_project_name ReflectionApi_Qt)
option(REFLECTION_API_QT_EXAMPLE "Add ReflectionApi examples file as executable (on|off)" OFF )

project(${reflection_api_qt_project_name} LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core REQUIRED)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

if(NOT TARGET ReflectionApi)
    add_subdirectory(include/external/ReflectionApi)
endif()

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
)

if(${WIN32})
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        ReflectionApi
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include
        DESTINATION include
)

if(${REFLECTION_API_QT_EXAMPLE})
    add_subdirectory(example)
endif ()