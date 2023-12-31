project(nv12_sample)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/NV12/)

set(IMGUI_PATH    "${CMAKE_SOURCE_DIR}/third_party/imgui/")
set(IMGUI_INCLUDE "${IMGUI_PATH}" "${IMGUI_PATH}/backends/")
set(IMGUI_SRC     "${IMGUI_PATH}/backends/imgui_impl_dx11.cpp"
                  "${IMGUI_PATH}/backends/imgui_impl_win32.cpp"
                  "${IMGUI_PATH}/imgui.cpp"
                  "${IMGUI_PATH}/imgui_demo.cpp"
                  "${IMGUI_PATH}/imgui_draw.cpp"
                  "${IMGUI_PATH}/imgui_tables.cpp"
                  "${IMGUI_PATH}/imgui_widgets.cpp"
)

set(TINYEXR_PATH    "${CMAKE_SOURCE_DIR}/third_party/tinyexr/")
set(TINYEXR_INCLUDE "${TINYEXR_PATH}" "${TINYEXR_PATH}/deps/miniz")
set(TINYEXR_SRC     "${TINYEXR_PATH}/deps/miniz/miniz.c")

set(STB_PATH     "${CMAKE_SOURCE_DIR}/third_party/stb/")
set(STB_INCLUDE  "${STB_PATH}")

set(NIS_PATH "${CMAKE_SOURCE_DIR}/../NIS")

set(SAMPLES_PATH "${CMAKE_SOURCE_DIR}")

set(DX_SAMPLE_SRC "src/Sample.cpp"
                  "src/AppRenderer.cpp"
                  "src/UIRenderer.cpp"
                  "src/DeviceResources.cpp"
                  "src/NVScaler.cpp"
                  "src/NVSharpen.cpp"
                  "src/BilinearUpscale.cpp"
                  "${SAMPLES_PATH}/common/Image.cpp"
                  "src/dpi.manifest"
)

set(DX_SAMPLE_HEADERS "include/AppRenderer.h"
                      "include/DeviceResources.h"
                      "include/NVScaler.h"
                      "include/NVSharpen.h"
                      "include/UIRenderer.h"
                      "include/BilinearUpscale.h"
                      "include/DXUtilities.h"
                      "${NIS_PATH}/NIS_Config.h"
                      "${SAMPLES_PATH}/common/Image.h"
                      "${SAMPLES_PATH}/common/Utilities.h"
)

set(DX_SAMPLE_SHADERS "${NIS_PATH}/NIS_Scaler.h"
                      "${NIS_PATH}/NIS_Main.hlsl"
)

set(DX_SAMPLE_MEDIA "${SAMPLES_PATH}/media/images/1080.png"
                    "${SAMPLES_PATH}/media/images/1440.png"
                    "${SAMPLES_PATH}/media/images/1660.png"
)

set_source_files_properties(${DX_SAMPLE_SHADERS} PROPERTIES VS_COPY_TO_OUT_DIR TRUE)

source_group("external" FILES ${IMGUI_SRC} ${TINYEXR_SRC})
source_group("shaders" FILES ${DX_SAMPLE_SHADERS})
add_executable(${PROJECT_NAME} ${DX_SAMPLE_SRC} ${IMGUI_SRC} ${TINYEXR_SRC} ${DX_SAMPLE_HEADERS} ${DX_SAMPLE_SHADERS})
target_include_directories (${PROJECT_NAME} PUBLIC include ${IMGUI_INCLUDE} ${TINYEXR_INCLUDE} ${STB_INCLUDE} ${NIS_PATH} ${SAMPLES_PATH}/common)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/NIS
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${NIS_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>/NIS
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/media/images
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SAMPLES_PATH}/media/images $<TARGET_FILE_DIR:${PROJECT_NAME}>/media/images
)

