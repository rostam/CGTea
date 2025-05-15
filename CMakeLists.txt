cmake_minimum_required(VERSION 3.10)
project(CGTea)
set(CMAKE_CXX_STANDARD 17)
enable_testing()
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
file(GLOB BoostTestSrc "BoostTestSrc/*.cpp")
file(GLOB Reports "reports/*.cpp")
file(GLOB Generators "generators/*.cpp")
file(GLOB Actions "actions/*.cpp")
file(GLOB ConjectureCheck "ConjectureCheck/*.cpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
#set( CMAKE_CXX_FLAGS "`wx-config --cxxflags --libs`")
add_executable(CGTea CGTeaApp.cpp BasicDrawPane.cpp CGTeaFrame.cpp CGTeaSidebar.cpp  ${Reports} ${Generators} ${Actions})
add_executable(BoostTest ${Reports} ${Generators}  ${BoostTestSrc} ${ConjectureCheck} ${Actions}
        tests/test_generator.cpp
        tests/test_index.cpp
        tests/test_g6format.cpp)
target_link_libraries(CGTea ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(BoostTest ${Boost_LIBRARIES})

