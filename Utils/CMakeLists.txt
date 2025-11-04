add_library(Utils STATIC
    src/yaml.cpp
)

target_link_libraries(Utils PUBLIC yaml-cpp::yaml-cpp)

target_include_directories(Utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)