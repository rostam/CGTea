cmake_minimum_required(VERSION 3.10)
project(CGTea)
set(CMAKE_CXX_STANDARD 17)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include(${wxWidgets_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
file(GLOB BoostTestSrc
    "BoostTest/*.cpp"
)
file(GLOB Reports
        "reports/*.cpp"
)
file(GLOB Generators
        "generators/*.cpp"
        )
#set( CMAKE_CXX_FLAGS "`wx-config --cxxflags --libs`")
add_executable(CGTea CGTeaApp.cpp BasicDrawPane.cpp CGTeaFrame.cpp CGTeaSidebar.cpp  ${Reports} ${Generators})
add_executable(BoostTest ${Reports} ${Generators}  ${BoostTestSrc})
target_link_libraries(CGTea ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(BoostTest ${Boost_LIBRARIES})
