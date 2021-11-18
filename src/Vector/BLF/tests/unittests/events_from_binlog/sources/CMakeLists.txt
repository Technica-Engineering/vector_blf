# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.8)

project(Vector_BLF_sample_generator
    VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Release)

enable_testing()

find_path(BINLOG_INCLUDE_DIR
    binlog.h
    HINTS .)

if (WIN32)
    include_directories(${BINLOG_INCLUDE_DIR})
else()
    include_directories(
        ${BINLOG_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/linux-compat)
    add_definitions(-DBINLOG_EXPORTS)
endif()

if (WIN32)
    find_library(BINLOG_LIBRARY
        binlog
        HINTS .)

    add_custom_target(CopyDLL ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/binlog.dll
            $<TARGET_FILE_DIR:AppTrigger>) # just one of the tests...
else()
    add_library(binlog SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/binlog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/binlog_objects.h
        ${CMAKE_CURRENT_SOURCE_DIR}/binlog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/linux-compat/tchar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/linux-compat/windows.h
        ${CMAKE_CURRENT_SOURCE_DIR}/linux-compat/wtypes.h)
    set(BINLOG_LIBRARY binlog)

    message("Library not available under Linux. Using stub library instead.")
endif()

function(add_generator name)
    # targets
    add_executable(${name}
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/binlog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/binlog_objects.h)

    target_link_libraries(${name}
        ${BINLOG_LIBRARY})

    # tests
    add_test(
        NAME ${name}
        COMMAND ${name})
endfunction()

# overall tests
add_generator(A429BusStatistic)
add_generator(A429Error)
add_generator(A429Message)
add_generator(A429Status)
add_generator(AfdxBusStatistic)
add_generator(AfdxErrorEvent)
add_generator(AfdxFrame)
add_generator(AfdxStatistic)
add_generator(AfdxStatus)
add_generator(AppText)
add_generator(AppTrigger)
add_generator(CanDriverError)
add_generator(CanDriverErrorExt)
add_generator(CanDriverHwSync)
add_generator(CanDriverStatistic)
add_generator(CanErrorFrame)
add_generator(CanErrorFrameExt)
add_generator(CanFdErrorFrame64)
add_generator(CanFdMessage)
add_generator(CanFdMessage64)
add_generator(CanMessage)
add_generator(CanMessage2)
add_generator(CanOverloadFrame)
add_generator(DiagRequestInterpretation)
add_generator(DriverOverrun)
add_generator(EnvironmentVariable)
add_generator(EthernetErrorEx)
add_generator(EthernetErrorForwarded)
add_generator(EthernetFrameEx)
add_generator(EthernetFrameForwarded)
add_generator(EthernetFrame)
add_generator(EthernetRxError)
add_generator(EthernetStatistic)
add_generator(EthernetStatus)
add_generator(EventComment)
add_generator(FlexRayData)
add_generator(FlexRayStatusEvent)
add_generator(FlexRaySync)
add_generator(FlexRayV6Message)
add_generator(FlexRayV6StartCycleEvent)
add_generator(FlexRayVFrError)
add_generator(FlexRayVFrReceiveMsg)
add_generator(FlexRayVFrReceiveMsgEx)
add_generator(FlexRayVFrStartCycle)
add_generator(FlexRayVFrStatus)
add_generator(GlobalMarker)
add_generator(GpsEvent)
add_generator(J1708Message)
add_generator(KLineStatusEvent)
add_generator(LinBaudrateEvent)
add_generator(LinChecksumInfo)
add_generator(LinCrcError)
add_generator(LinCrcError2)
add_generator(LinDisturbanceEvent)
add_generator(LinDlcInfo)
add_generator(LinLongDomSignalEvent)
add_generator(LinLongDomSignalEvent2)
add_generator(LinMessage)
add_generator(LinMessage2)
add_generator(LinReceiveError)
add_generator(LinReceiveError2)
add_generator(LinSchedulerModeChange)
add_generator(LinSendError)
add_generator(LinSendError2)
add_generator(LinShortOrSlowResponse)
add_generator(LinShortOrSlowResponse2)
add_generator(LinSlaveTimeout)
add_generator(LinSleepModeEvent)
add_generator(LinSpikeEvent)
add_generator(LinSpikeEvent2)
add_generator(LinStatisticEvent)
add_generator(LinSyncError)
add_generator(LinSyncError2)
add_generator(LinUnexpectedWakeup)
add_generator(LinWakeupEvent)
add_generator(LinWakeupEvent2)
add_generator(Most150AllocTab)
add_generator(Most150Message)
add_generator(Most150MessageFragment)
add_generator(Most150Pkt)
add_generator(Most150PktFragment)
add_generator(Most50Message)
add_generator(Most50Pkt)
add_generator(MostAllocTab)
add_generator(MostCtrl)
add_generator(MostDataLost)
add_generator(MostEcl)
add_generator(MostEthernetPkt)
add_generator(MostEthernetPktFragment)
add_generator(MostGenReg)
add_generator(MostHwMode)
add_generator(MostLightLock)
add_generator(MostNetState)
add_generator(MostPkt)
add_generator(MostPkt2)
add_generator(MostReg)
add_generator(MostSpy)
add_generator(MostStatistic)
add_generator(MostStatisticEx)
add_generator(MostStress)
add_generator(MostSystemEvent)
add_generator(MostTrigger)
add_generator(MostTxLight)
add_generator(RealtimeClock)
add_generator(SerialEvent)
add_generator(SystemVariable)
add_generator(TestStructure)
add_generator(WlanFrame)
add_generator(WlanStatistic)
