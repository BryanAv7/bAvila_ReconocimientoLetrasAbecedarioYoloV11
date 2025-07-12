cmake_minimum_required(VERSION 3.0.0)
project(yolo_ort)

option(ONNXRUNTIME_DIR "Path to built ONNX Runtime directory." STRING)
message(STATUS "ONNXRUNTIME_DIR: ${ONNXRUNTIME_DIR}")

find_package(OpenCV REQUIRED)

include_directories("include/")

# Ejecutable único principal.cpp
add_executable(principal
    src/principal.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(principal PRIVATE "${ONNXRUNTIME_DIR}/include")

target_compile_features(principal PRIVATE cxx_std_14)

target_link_libraries(principal ${OpenCV_LIBS})

if(WIN32)
    target_link_libraries(principal "${ONNXRUNTIME_DIR}/lib/onnxruntime.lib")
endif(WIN32)

if(UNIX)
    target_link_libraries(principal "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")
endif(UNIX)
