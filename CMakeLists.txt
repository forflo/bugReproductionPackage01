cmake_minimum_required(VERSION 3.2.3)
project (REPRODUCTION_PACKAGE)

set (CMAKE_CXX_STANDARD 17)

set (ORKA_ROSE_INST_DIR /opt/rose)

# This is needed for Cmake to include the -pthread flag in GCC
# g++ needs -pthread in order to set some preprocessor flags (-D_REENTRANT)
# which is needed for things to work out
set (CMAKE_THREAD_PREFER_PTHREAD TRUE)
set (THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package (Threads REQUIRED)

set (PROJECT_DYN_LIBS librose.so
                      libquadmath.so
                      libboost_system.so
                      libboost_filesystem.so)

# absolute paths for the time being
link_directories(
        /usr/lib/jvm/java-8-openjdk/jre/lib/amd64/server/
        /usr/lib/
        ${ORKA_ROSE_INST_DIR}/lib
        /opt/boost/1.65.0/lib
)

include_directories(
        ${ORKA_ROSE_INST_DIR}/include/rose
        ./procxx/include
        ./json/single_include
        ./
        /opt/boost/1.65.0/include
)

add_executable(fail fail.cpp)
add_executable(success success.cpp)
target_link_libraries(fail Threads::Threads
                                    ${PROJECT_DYN_LIBS}
                                    ${PROJECT_STAT_LIBS})
target_link_libraries(success Threads::Threads
                                    ${PROJECT_DYN_LIBS}
                                    ${PROJECT_STAT_LIBS})
