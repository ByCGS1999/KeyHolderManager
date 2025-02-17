# CMakeList.txt: proyecto de CMake para KeyHolderManager, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_TOOLCHAIN_FILE}" CACHE STRING "Path to vcpkg toolchain file" FORCE)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("KeyHolderManager")

add_executable (KeyHolderManager 
"KeyHolderManager.cpp" 
"KeyHolderManager.h" 
"source/KeyContainer.cpp" 
"include/Includes.h" 
"include/KeyContainer.h" 
"source/SafeString.cpp" 
"include/SafeString.h" 
"ImguiImpl/imgui_impl_glfw.cpp" 
"ImguiImpl/imgui_impl_glfw.h" 
"ImguiImpl/imgui_impl_opengl3.h" 
"ImguiImpl/imgui_impl_opengl3.cpp"
"imgui/imconfig.h" 
"imgui/imgui.cpp" 
"imgui/imgui.h" 
"imgui/imgui_demo.cpp" 
"imgui/imgui_draw.cpp" 
"imgui/imgui_internal.h" 
"imgui/imgui_tables.cpp" 
"imgui/imgui_widgets.cpp" 
"imgui/imstb_rectpack.h"
"imgui/imstb_textedit.h"
"imgui/imstb_truetype.h"
"ImguiImpl/imgui_impl_opengl3_loader.h" 
"source/Themes.cpp"
"include/Themes.h" 
"source/DataBase.cpp"
"include/DataBase.h"
"imgui/imgui_stdlib.h" 
"imgui/imgui_stdlib.cpp" 
"include/PasswordGenerator.h"
"source/PasswordGenerator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KeyHolderManager PROPERTY CXX_STANDARD 17)
endif()

include_directories ("./include/")
set_target_properties(KeyHolderManager PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")

# PACKAGES #

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(KeyHolderManager PRIVATE glfw)
target_link_libraries(KeyHolderManager PRIVATE glad::glad)
target_link_libraries(KeyHolderManager PRIVATE cryptopp::cryptopp)
target_link_libraries(KeyHolderManager PRIVATE unofficial::sqlite3::sqlite3)

# TODO: Agregue pruebas y destinos de instalación si es necesario.
