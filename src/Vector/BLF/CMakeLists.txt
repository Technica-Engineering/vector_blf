# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

# dependencies
include(GenerateExportHeader)

# targets
add_library(${PROJECT_NAME} SHARED "")

# search paths
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${ZLIB_INCLUDE_DIRS})

# sources/headers
target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/AppText.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AppTrigger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AttributeEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverErrorExt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverHwSync.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverStatistic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrameExt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdErrorFrame64.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdExtFrameData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage64.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanMessage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanOverloadFrame.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CanSettingChanged.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CompactSerialEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressedFile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DataLostBegin.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DataLostEnd.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DiagRequestInterpretation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DistributedObjectMember.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DriverOverrun.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentVariable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EventComment.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Exceptions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/File.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileStatistics.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionBus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GeneralSerialEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GlobalMarker.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LogContainer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectHeaderBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectHeader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectQueue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RealtimeClock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePointContainer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePoints.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SerialEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SingleByteSerialEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemVariable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TestStructure.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TriggerCondition.h
        ${CMAKE_CURRENT_SOURCE_DIR}/UncompressedFile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VarObjectHeader.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/AbstractFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AppText.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AppTrigger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AttributeEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverErrorExt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverHwSync.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanDriverStatistic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanErrorFrameExt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdErrorFrame64.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdExtFrameData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage64.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanFdMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanMessage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanOverloadFrame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanSettingChanged.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CompactSerialEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressedFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DataLostBegin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DataLostEnd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DiagRequestInterpretation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DistributedObjectMember.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/DriverOverrun.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EventComment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileStatistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FunctionBus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GeneralSerialEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GlobalMarker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LogContainer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectHeaderBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectHeader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ObjectQueue.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RealtimeClock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePointContainer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RestorePoints.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SerialEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SingleByteSerialEvent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TestStructure.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TriggerCondition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UncompressedFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VarObjectHeader.cpp)

# generated files
configure_file(config.h.in config.h)
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
generate_export_header(${PROJECT_NAME})

# compiler/linker settings
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET "hidden"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
    VISIBILITY_INLINES_HIDDEN 1)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-pedantic)
    add_definitions(-D_FORTIFY_SOURCE=2)
    #add_definitions(-fPIE -pie)
    add_definitions(-Wl,-z,relro,-z,now)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
        add_definitions(-fstack-protector-strong)
    endif()
    if(OPTION_USE_GCOV)
        add_definitions(-g -O0 --coverage)
    endif()
    if(OPTION_USE_GPROF)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
    endif()
endif()
target_link_libraries(${PROJECT_NAME}
    Threads::Threads
    ${ZLIB_LIBRARIES})
if(OPTION_USE_GCOV)
    target_link_libraries(${PROJECT_NAME} gcov)
endif()

# install
install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/vector_blf_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
        $<TARGET_PROPERTY:${PROJECT_NAME},INTERFACE_SOURCES>
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Vector/BLF)
