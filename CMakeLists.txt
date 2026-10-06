cmake_minimum_required(VERSION 3.21.1)

project(LicensingPortal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appLicensingPortal src/main.cpp)

qt_add_qml_module(appLicensingPortal
    URI LicensingPortalContent
    VERSION 1.0
    QML_FILES
        qml/App.qml
        qml/pages/LoginScreen.ui.qml
        qml/pages/UserDashboard.ui.qml
    SOURCES
        # core
        src/core/ApiClient.h
        src/core/ApiClient.cpp
        src/core/SessionManager.h
        src/core/SessionManager.cpp
        src/core/Config.h
        # models
        src/models/License.h
        src/models/LicenseListModel.h
        src/models/LicenseListModel.cpp
        src/models/User.h
        # services
        src/services/AuthService.h
        src/services/AuthService.cpp
        src/services/LicenseService.h
        src/services/LicenseService.cpp
        # viewmodels
        src/viewmodels/LoginViewModel.h
        src/viewmodels/LoginViewModel.cpp
        src/viewmodels/AppViewModel.h
        src/viewmodels/AppViewModel.cpp
        src/viewmodels/UserDashboardViewModel.h
        src/viewmodels/UserDashboardViewModel.cpp
)

set_target_properties(appLicensingPortal PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_include_directories(appLicensingPortal PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/services
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodels
)

target_link_libraries(appLicensingPortal PRIVATE Qt6::Quick Qt6::Network)

include(GNUInstallDirs)
install(TARGETS appLicensingPortal
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
