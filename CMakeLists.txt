cmake_minimum_required(VERSION 3.10)
project(readesm)
set(VERSION_DATE "2026-11-14")
set(VERSION_STRING "2026.11")
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/fileformat/config.h)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Svg LinguistTools REQUIRED)

file(GLOB_RECURSE SOURCES "fileformat/*.cpp" "gui/*.cpp")
list(APPEND SOURCES "readesm.cpp" "OptionParser.cpp")
file(GLOB_RECURSE HEADERS "fileformat/*.h" "gui/*.h" "*.h")

qt5_add_resources(RCC_SRCS readesm.qrc)

# Detect headers with Q_OBJECT for moc
set(QT_HEADERS)
foreach(h ${HEADERS})
    file(READ ${h} CONTENTS)
    if(CONTENTS MATCHES "Q_OBJECT")
        list(APPEND QT_HEADERS ${h})
    endif()
endforeach()
qt5_wrap_cpp(MOC_SRCS ${QT_HEADERS})

add_executable(readesm ${SOURCES} ${RCC_SRCS} ${MOC_SRCS})
target_link_libraries(readesm Qt5::Widgets Qt5::Svg Qt5::Core gcrypt gmp)
target_compile_options(readesm PRIVATE -include QCoreApplication)

# Traductions : les .ts sont compilés en .qm à chaque construction
include(GNUInstallDirs)
file(GLOB TS_FILES "ressources/translations/*.ts")
qt5_add_translation(QM_FILES ${TS_FILES})
add_custom_target(translations ALL DEPENDS ${QM_FILES})

install(TARGETS readesm RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES readesm.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES readesm.svg DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
install(FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/readesm/translations)
install(FILES COPYING copyright DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/readesm-qt5)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "readesm-qt5")
set(CPACK_PACKAGE_VERSION "${VERSION_STRING}")
set(CPACK_PACKAGE_CONTACT "Jean-Paul FRAYSSE <jpaul.fraysse@orange.fr>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jean-Paul FRAYSSE <jpaul.fraysse@orange.fr>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Digital tachograph file reader")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Reader for digital tachograph files (.ddd).\n Produces an HTML report with daily activity graphs and monthly timesheets.")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/Bosctre/ReadEsm-Qt5-2026.11")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
include(CPack)