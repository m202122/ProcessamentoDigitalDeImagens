# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()

# This project is designed to be built outside the Insight source tree.
project(Projeto)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

#find wx
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(main filter.cpp ImagePanel.cpp MainFrame.cpp Main.cpp)

target_link_libraries(main ${ITK_LIBRARIES} ${wxWidgets_LIBRARIES} )
