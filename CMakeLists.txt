cmake_minimum_required(VERSION 3.28.3)

project(pMSSMdive)


# Main excecutable
add_executable(pmssmdive)

target_sources(pmssmdive
    PRIVATE
        pmssmdive.cpp
)




# YAML-CPP Integration
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)



# Utils lib
add_subdirectory(Utils)
target_link_libraries(pmssmdive PUBLIC Utils)