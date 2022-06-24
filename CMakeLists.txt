#==============================
# Requirements
#==============================

cmake_minimum_required(VERSION 3.10)

#==============================
# Project Settings
#==============================

if (NOT PROJECT_DECLARED)
    project("Easy Serial Porting" LANGUAGES CXX VERSION 1.0.0)
    set(PROJECT_DECLARED)
endif()

#==============================
# Project Modules
#==============================

add_subdirectory("EasySerialPorting")

if (WITH_TEST)
    add_subdirectory("EasySerialPortingTestSender")
    add_subdirectory("EasySerialPortingTestReceiver")
endif()