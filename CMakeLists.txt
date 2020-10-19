cmake_minimum_required(VERSION 3.5)

project(RemoteWorkouts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "C:/Program Files/MySQL/Connector C++ 8.0")



# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(RemoteWorkouts SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
  )
else()
  add_executable(RemoteWorkouts
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    newuserwindow.cpp
    newuserwindow.h
    newuserwindow.ui
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/jdbc
        )
target_include_directories(${PROJECT_NAME} PRIVATE
        ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/jdbc/cppconn
        )
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/mysqlcppconn8.lib
        )

target_link_libraries(RemoteWorkouts PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
