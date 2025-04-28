cmake_minimum_required(VERSION 3.26)

project(ProjectNotePad LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
file(GLOB_RECURSE SOURCES "source/*.cpp" "include/*.hpp" "include/*.h")

add_executable(note_pad ${SOURCES})

target_link_libraries(note_pad PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(note_pad PRIVATE include)

#设置qDebug在终端输出
set_target_properties(note_pad PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE ON
)