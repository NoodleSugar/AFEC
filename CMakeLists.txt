cmake_minimum_required(VERSION 3.22.0)
project(
	AFECS
		VERSION 0.1.0
		DESCRIPTION "Another Funny Entity Component System"
		LANGUAGES CXX
)

set(VERSION_FILE version.h)
configure_file(
	${CMAKE_SOURCE_DIR}/cmake/${VERSION_FILE}.in
	${CMAKE_SOURCE_DIR}/include/afecs/${VERSION_FILE}
)



find_package(Boost REQUIRED)
find_package(EASTL CONFIG REQUIRED)

include(CTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# AFECS Library

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		EASTL
)

target_sources(${PROJECT_NAME}
	PRIVATE
		src/World.cpp
)

# AFECS Tests

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(tests)
endif ()

enable_testing()

# Install AFECS package

set(PROJECT_EXPORT ${PROJECT_NAME}Export)
set(PROJECT_CONFIG ${PROJECT_NAME}Config)
set(PROJECT_CONFIG_VERSION ${PROJECT_NAME}ConfigVersion)
set(PROJECT_PATH_WITH_VERSION ${PROJECT_NAME}-${PROJECT_VERSION})

install(FILES ${CMAKE_BINARY_DIR}/${VERSION_FILE}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/afecs
)

install(DIRECTORY include/afecs
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN *.hpp
)

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_EXPORT}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ${PROJECT_EXPORT}
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_PATH_WITH_VERSION}
	NAMESPACE afecs::
)

# Configure AFECS for find_package

configure_package_config_file(
	${PROJECT_SOURCE_DIR}/cmake/${PROJECT_CONFIG}.cmake.in
	${PROJECT_BINARY_DIR}/${PROJECT_CONFIG}.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_PATH_WITH_VERSION}
)

write_basic_package_version_file(
	${PROJECT_CONFIG_VERSION}.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CONFIG}.cmake
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CONFIG_VERSION}.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_PATH_WITH_VERSION}
)