cmake_minimum_required(VERSION 3.6)
project(PackageDownloader)

# Output to
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/downloader.cpp src/summary.cpp src/util.cpp src/util.h src/porttester.cpp src/porttester.h src/httpsclient.cpp src/httpsclient.h)
add_executable(PackageDownloader ${SOURCE_FILES})

find_library(PFOUNDATION libPocoFoundation.a PocoFoundation)
find_library(PUTIL libPocoUtil.a PocoUtil)
find_library(PNET libPocoNet.a PocoNet)
find_library(PNETSSL libPocoNetSSL.a PocoNetSSL)
find_library(PCRYPTO libPocoCrypto.a PocoCrypto)
find_library(PXML libPocoXML.a PocoXML)
find_library(PJSON libPocoJSON.a PocoJSON)

target_link_libraries(
        PackageDownloader
        ssl
        crypto
        ${PNETSSL}
        ${PCRYPTO}
        ${PNET}
        ${PUTIL}
        ${PXML}
        pthread
        ${PFOUNDATION}
        ${PJSON}
)
