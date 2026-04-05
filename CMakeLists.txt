cmake_minimum_required(VERSION 3.10)
project(CGTea)
set(CMAKE_CXX_STANDARD 17)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include(${wxWidgets_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
file(GLOB BoostTestSrc "BoostTestSrc/*.cpp")
file(GLOB Reports "reports/*.cpp")
file(GLOB Generators "generators/*.cpp")
file(GLOB Actions "actions/*.cpp")
file(GLOB ConjectureCheck "ConjectureCheck/*.cpp")
#set( CMAKE_CXX_FLAGS "`wx-config --cxxflags --libs`")
add_executable(CGTea CGTeaApp.cpp BasicDrawPane.cpp CGTeaFrame.cpp CGTeaSidebar.cpp
        ConjectureCheckerDialog.cpp ConjectureCheckerDialog.h
        ${Reports} ${Generators} ${Actions}
        const_values.h
        SettingsDialog.cpp
        SettingsDialog.h)
add_executable(BoostTest ${Reports} ${Generators} ${BoostTestSrc} ${ConjectureCheck} ${Actions})
target_compile_options(BoostTest PRIVATE --coverage)
target_link_options(BoostTest PRIVATE --coverage)
target_link_libraries(CGTea ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(BoostTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# ─── Python bindings (optional) ─────────────────────────────────────────────
option(BUILD_PYTHON_BINDINGS "Build the cgtea Python extension module" OFF)
if(BUILD_PYTHON_BINDINGS)
    execute_process(
        COMMAND python3 -m pybind11 --cmakedir
        OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")
    find_package(pybind11 REQUIRED)

    # Collect the same .cpp sources the main targets use, minus GUI files
    pybind11_add_module(cgtea_py
        python/bindings.cpp
        ${Reports}
        ${Generators}
        ${Actions}
    )

    target_include_directories(cgtea_py PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
    )
    target_link_libraries(cgtea_py PRIVATE ${Boost_LIBRARIES})

    # Allow users to import as `import cgtea` by renaming the output file
    set_target_properties(cgtea_py PROPERTIES OUTPUT_NAME cgtea)
endif()
