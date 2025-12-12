cmake_minimum_required(VERSION 3.16)

project(InventarioLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Preferir Qt6, si está disponible
find_package(Qt6 COMPONENTS Core Widgets Sql QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Widgets Sql REQUIRED)
    set(USE_QT5 TRUE)
endif()

# --- Lista correcta de fuentes ---
set(SRC
    main.cpp
    mainwindow.cpp
    component.cpp
    databasemanager.cpp
    inventorymanager.cpp
    reportgenerator.cpp
)

set(HEADERS
    mainwindow.h
    component.h
    databasemanager.h
    inventorymanager.h
    reportgenerator.h
)

set(UI
    mainwindow.ui
)

# --- Ejecutable ---
if(Qt6_FOUND)
    qt_add_executable(InventarioLab
        ${SRC} ${HEADERS} ${UI}
    )
    target_link_libraries(InventarioLab PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)
else()
    add_executable(InventarioLab
        ${SRC} ${HEADERS} ${UI}
    )
    target_link_libraries(InventarioLab PRIVATE Qt5::Core Qt5::Widgets Qt5::Sql)
endif()

set_target_properties(InventarioLab PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS InventarioLab
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(Qt6_FOUND)
    qt_finalize_executable(InventarioLab)
endif()
