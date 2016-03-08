cmake_minimum_required(VERSION 2.8)

find_package(ZLIB)

include(GenerateExportHeader)

configure_file(config.h.in config.h)
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

include_directories(
    ${ZLIB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

set(source_files
    AbstractFile.cpp
    AfdxFrame.cpp
    AfdxStatistic.cpp
    AppText.cpp
    AppTrigger.cpp
    CanDriverErrorExt.cpp
    CanDriverError.cpp
    CanDriverHwSync.cpp
    CanDriverStatistic.cpp
    CanErrorFrameExt.cpp
    CanErrorFrame.cpp
    CanFdErrorFrame64.cpp
    CanFdMessage64.cpp
    CanFdMessage.cpp
    CanMessage2.cpp
    CanMessage.cpp
    CanOverloadFrame.cpp
    CompressedFile.cpp
    DriverOverrun.cpp
    EnvironmentVariable.cpp
    EthernetFrame.cpp
    EthernetRxError.cpp
    EthernetStatus.cpp
    EventComment.cpp
    FileStatistics.cpp
    File.cpp
    FlexRayData.cpp
    FlexRayStatusEvent.cpp
    FlexRaySync.cpp
    FlexRayV6Message.cpp
    FlexRayV6StartCycleEvent.cpp
    FlexRayVFrError.cpp
    FlexRayVFrReceiveMsgEx.cpp
    FlexRayVFrReceiveMsg.cpp
    FlexRayVFrStartCycle.cpp
    FlexRayVFrStatus.cpp
    GlobalMarker.cpp
    GpsEvent.cpp
    J1708Message.cpp
    KLineStatusEvent.cpp
    LinBaudrateEvent.cpp
    LinBusEvent.cpp
    LinChecksumInfo.cpp
    LinCrcError2.cpp
    LinCrcError.cpp
    LinDatabyteTimestampEvent.cpp
    LinDisturbanceEvent.cpp
    LinDlcInfo.cpp
    LinLongDomSignalEvent2.cpp
    LinLongDomSignalEvent.cpp
    LinMessage2.cpp
    LinMessageDescriptor.cpp
    LinMessage.cpp
    LinReceiveError2.cpp
    LinReceiveError.cpp
    LinSchedulerModeChange.cpp
    LinSendError2.cpp
    LinSendError.cpp
    LinShortOrSlowResponse.cpp
    LinSlaveTimeout.cpp
    LinSleepModeEvent.cpp
    LinSpikeEvent2.cpp
    LinSpikeEvent.cpp
    LinStatisticEvent.cpp
    LinSyncError2.cpp
    LinSyncError.cpp
    LinSynchFieldEvent.cpp
    LinUnexpectedWakeup.cpp
    LinWakeupEvent2.cpp
    LinWakeupEvent.cpp
    LogContainer.cpp
    Most150AllocTab.cpp
    Most150MessageFragment.cpp
    Most150Message.cpp
    Most150PktFragment.cpp
    Most150Pkt.cpp
    Most50Message.cpp
    Most50Pkt.cpp
    MostAllocTab.cpp
    MostCtrl.cpp
    MostDataLost.cpp
    MostEcl.cpp
    MostEthernetPktFragment.cpp
    MostEthernetPkt.cpp
    MostGenReg.cpp
    MostHwMode.cpp
    MostLightLock.cpp
    MostNetState.cpp
    MostPkt2.cpp
    MostPkt.cpp
    MostReg.cpp
    MostSpy.cpp
    MostStatisticEx.cpp
    MostStatistic.cpp
    MostStress.cpp
    MostSystemEvent.cpp
    MostTrigger.cpp
    MostTxLight.cpp
    ObjectHeader2.cpp
    ObjectHeaderBase.cpp
    ObjectHeader.cpp
    RealtimeClock.cpp
    SerialEvent.cpp
    SystemVariable.cpp
    UncompressedFile.cpp
    WlanFrame.cpp
    WlanStatistic.cpp)

set(public_header_files
    AbstractFile.h
    AfdxFrame.h
    AfdxStatistic.h
    AppText.h
    AppTrigger.h
    CanDriverErrorExt.h
    CanDriverError.h
    CanDriverHwSync.h
    CanDriverStatistic.h
    CanErrorFrameExt.h
    CanErrorFrame.h
    CanFdErrorFrame64.h
    CanFdMessage64.h
    CanFdMessage.h
    CanMessage2.h
    CanMessage.h
    CanOverloadFrame.h
    CompressedFile.h
    DriverOverrun.h
    EnvironmentVariable.h
    EthernetFrame.h
    EthernetRxError.h
    EthernetStatus.h
    EventComment.h
    FileStatistics.h
    File.h
    FlexRayData.h
    FlexRayStatusEvent.h
    FlexRaySync.h
    FlexRayV6Message.h
    FlexRayV6StartCycleEvent.h
    FlexRayVFrError.h
    FlexRayVFrReceiveMsgEx.h
    FlexRayVFrReceiveMsg.h
    FlexRayVFrStartCycle.h
    FlexRayVFrStatus.h
    GlobalMarker.h
    GpsEvent.h
    J1708Message.h
    KLineStatusEvent.h
    LinBaudrateEvent.h
    LinBusEvent.h
    LinChecksumInfo.h
    LinCrcError2.h
    LinCrcError.h
    LinDatabyteTimestampEvent.h
    LinDisturbanceEvent.h
    LinDlcInfo.h
    LinLongDomSignalEvent2.h
    LinLongDomSignalEvent.h
    LinMessage2.h
    LinMessageDescriptor.h
    LinMessage.h
    LinReceiveError2.h
    LinReceiveError.h
    LinSchedulerModeChange.h
    LinSendError2.h
    LinSendError.h
    LinShortOrSlowResponse.h
    LinSlaveTimeout.h
    LinSleepModeEvent.h
    LinSpikeEvent2.h
    LinSpikeEvent.h
    LinStatisticEvent.h
    LinSyncError2.h
    LinSyncError.h
    LinSynchFieldEvent.h
    LinUnexpectedWakeup.h
    LinWakeupEvent2.h
    LinWakeupEvent.h
    LogContainer.h
    Most150AllocTab.h
    Most150MessageFragment.h
    Most150Message.h
    Most150PktFragment.h
    Most150Pkt.h
    Most50Message.h
    Most50Pkt.h
    MostAllocTab.h
    MostCtrl.h
    MostDataLost.h
    MostEcl.h
    MostEthernetPktFragment.h
    MostEthernetPkt.h
    MostGenReg.h
    MostHwMode.h
    MostLightLock.h
    MostNetState.h
    MostPkt2.h
    MostPkt.h
    MostReg.h
    MostSpy.h
    MostStatisticEx.h
    MostStatistic.h
    MostStress.h
    MostSystemEvent.h
    MostTrigger.h
    MostTxLight.h
    ObjectHeader2.h
    ObjectHeaderBase.h
    ObjectHeader.h
    platform.h
    RealtimeClock.h
    SerialEvent.h
    SystemVariable.h
    VectorTypes.h
    UncompressedFile.h
    WlanFrame.h
    WlanStatistic.h)

set(private_header_files
    )

add_compiler_export_flags()

add_library(${PROJECT_NAME} SHARED
    ${source_files} ${public_header_files} ${private_header_files})

if(OPTION_USE_GCOV_LCOV)
    target_link_libraries(${PROJECT_NAME} gcov)
    add_definitions(-g -O0 -fprofile-arcs -ftest-coverage)
endif()

generate_export_header(${PROJECT_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARY})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
        ${CMAKE_CURRENT_BINARY_DIR}/vector_blf_export.h
        ${public_header_files}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Vector/BLF)

add_subdirectory(docs)
add_subdirectory(tests)
