cmake_minimum_required(VERSION 3.16)

project(InventarioLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# ENCONTRAR QT (Core, Widgets, Sql)
# -------------------------------
find_package(Qt6 COMPONENTS Core Widgets Sql REQUIRED) # Para Qt6
# find_package(Qt5 COMPONENTS Core Widgets Sql REQUIRED) # Para Qt5 si usas Qt5

# -------------------------------
# AGREGAR TODOS LOS ARCHIVOS
# -------------------------------
file(GLOB PROJECT_SOURCES
    "*.cpp"
    "*.h"
    "*.ui"
)

# -------------------------------
# CREAR EL EJECUTABLE
# -------------------------------
if(Qt6_FOUND)
    qt_add_executable(InventarioLab
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(InventarioLab
        ${PROJECT_SOURCES}
    )
endif()

# -------------------------------
# VINCULAR LAS LIBRERÍAS
# -------------------------------
target_link_libraries(InventarioLab PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

# -------------------------------
# CONFIGURACIONES MAC/WIN
# -------------------------------
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.InventarioLab)
endif()

set_target_properties(InventarioLab PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# -------------------------------
# INSTALACIÓN
# -------------------------------
include(GNUInstallDirs)

install(TARGETS InventarioLab
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(Qt6_FOUND)
    qt_finalize_executable(InventarioLab)
endif()
