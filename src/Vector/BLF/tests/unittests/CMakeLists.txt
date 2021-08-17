# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

# combines: targets, sources/headers, compiler/linker settings, tests
set(test_targets )
function(add_boost_test test_name test_target)
    # targets
    add_executable(${test_target} "")

    # sources/headers
    target_sources(${test_target} PRIVATE ${ARGN})

    # compiler/linker settings
    set_target_properties(${test_target} PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON)
    target_link_libraries(${test_target}
        PRIVATE
            ${PROJECT_NAME}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    if(OPTION_USE_GCOV)
        target_link_libraries(${test_target} PRIVATE gcov)
    endif()

    # tests
    add_test(
        NAME ${test_name}
        COMMAND ${test_target})

    # add target to list of test targets
    set(test_targets ${test_targets} ${test_target} PARENT_SCOPE)
endfunction()

# search paths
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR})
link_directories(
    ${Boost_LIBRARY_DIRS})

# compiler/linker settings
add_definitions(
    -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

# overall tests
add_boost_test(AllLogfiles test_AllLogfiles test_AllLogfiles.cpp)

# single class tests
add_boost_test(A429BusStatistic test_A429BusStatistic test_A429BusStatistic.cpp)
add_boost_test(A429Error test_A429Error test_A429Error.cpp)
add_boost_test(A429Message test_A429Message test_A429Message.cpp)
add_boost_test(A429Status test_A429Status test_A429Status.cpp)
add_boost_test(AfdxBusStatistic test_AfdxBusStatistic test_AfdxBusStatistic.cpp)
add_boost_test(AfdxErrorEvent test_AfdxErrorEvent test_AfdxErrorEvent.cpp)
add_boost_test(AfdxFrame test_AfdxFrame test_AfdxFrame.cpp)
add_boost_test(AfdxStatistic test_AfdxStatistic test_AfdxStatistic.cpp)
add_boost_test(AfdxStatus test_AfdxStatus test_AfdxStatus.cpp)
add_boost_test(AppText test_AppText test_AppText.cpp)
add_boost_test(AppTrigger test_AppTrigger test_AppTrigger.cpp)
add_boost_test(CanDriverError test_CanDriverError test_CanDriverError.cpp)
add_boost_test(CanDriverErrorExt test_CanDriverErrorExt test_CanDriverErrorExt.cpp)
add_boost_test(CanDriverHwSync test_CanDriverHwSync test_CanDriverHwSync.cpp)
add_boost_test(CanDriverStatistic test_CanDriverStatistic test_CanDriverStatistic.cpp)
add_boost_test(CanErrorFrame test_CanErrorFrame test_CanErrorFrame.cpp)
add_boost_test(CanErrorFrameExt test_CanErrorFrameExt test_CanErrorFrameExt.cpp)
add_boost_test(CanFdErrorFrame64 test_CanFdErrorFrame64 test_CanFdErrorFrame64.cpp)
add_boost_test(CanFdMessage64 test_CanFdMessage64 test_CanFdMessage64.cpp)
add_boost_test(CanFdMessage test_CanFdMessage test_CanFdMessage.cpp)
add_boost_test(CanMessage test_CanMessage test_CanMessage.cpp)
add_boost_test(CanMessage2 test_CanMessage2 test_CanMessage2.cpp)
add_boost_test(CanOverloadFrame test_CanOverloadFrame test_CanOverloadFrame.cpp)
add_boost_test(CompactSerialEvent test_CompactSerialEvent test_CompactSerialEvent.cpp)
add_boost_test(CompressedFile test_CompressedFile test_CompressedFile.cpp)
add_boost_test(DataLostBegin test_DataLostBegin test_DataLostBegin.cpp)
add_boost_test(DataLostEnd test_DataLostEnd test_DataLostEnd.cpp)
add_boost_test(DiagRequestInterpretation test_DiagRequestInterpretation test_DiagRequestInterpretation.cpp)
add_boost_test(DriverOverrun test_DriverOverrun test_DriverOverrun.cpp)
add_boost_test(EnvironmentVariable test_EnvironmentVariable test_EnvironmentVariable.cpp)
add_boost_test(EthernetErrorEx test_EthernetErrorEx test_EthernetErrorEx.cpp)
add_boost_test(EthernetErrorForwarded test_EthernetErrorForwarded test_EthernetErrorForwarded.cpp)
add_boost_test(EthernetFrameEx test_EthernetFrameEx test_EthernetFrameEx.cpp)
add_boost_test(EthernetFrameForwarded test_EthernetFrameForwarded test_EthernetFrameForwarded.cpp)
add_boost_test(EthernetFrame test_EthernetFrame test_EthernetFrame.cpp)
add_boost_test(EthernetRxError test_EthernetRxError test_EthernetRxError.cpp)
add_boost_test(EthernetStatistic test_EthernetStatistic test_EthernetStatistic.cpp)
add_boost_test(EthernetStatus test_EthernetStatus test_EthernetStatus.cpp)
add_boost_test(EventComment test_EventComment test_EventComment.cpp)
add_boost_test(Exceptions test_Exceptions test_Exceptions.cpp)
add_boost_test(File test_File test_File.cpp)
add_boost_test(FileStatistics test_FileStatistics test_FileStatistics.cpp)
add_boost_test(FlexRayData test_FlexRayData test_FlexRayData.cpp)
add_boost_test(FlexRayStatusEvent test_FlexRayStatusEvent test_FlexRayStatusEvent.cpp)
add_boost_test(FlexRaySync test_FlexRaySync test_FlexRaySync.cpp)
add_boost_test(FlexRayV6Message test_FlexRayV6Message test_FlexRayV6Message.cpp)
add_boost_test(FlexRayV6StartCycleEvent test_FlexRayV6StartCycleEvent test_FlexRayV6StartCycleEvent.cpp)
add_boost_test(FlexRayVFrError test_FlexRayVFrError test_FlexRayVFrError.cpp)
add_boost_test(FlexRayVFrReceiveMsgEx test_FlexRayVFrReceiveMsgEx test_FlexRayVFrReceiveMsgEx.cpp)
add_boost_test(FlexRayVFrReceiveMsg test_FlexRayVFrReceiveMsg test_FlexRayVFrReceiveMsg.cpp)
add_boost_test(FlexRayVFrStartCycle test_FlexRayVFrStartCycle test_FlexRayVFrStartCycle.cpp)
add_boost_test(FlexRayVFrStatus test_FlexRayVFrStatus test_FlexRayVFrStatus.cpp)
add_boost_test(FunctionBus test_FunctionBus test_FunctionBus.cpp)
add_boost_test(GeneralSerialEvent test_GeneralSerialEvent test_GeneralSerialEvent.cpp)
add_boost_test(GlobalMarker test_GlobalMarker test_GlobalMarker.cpp)
add_boost_test(GpsEvent test_GpsEvent test_GpsEvent.cpp)
add_boost_test(J1708Message test_J1708Message test_J1708Message.cpp)
add_boost_test(KLineStatusEvent test_KLineStatusEvent test_KLineStatusEvent.cpp)
add_boost_test(LinBaudrateEvent test_LinBaudrateEvent test_LinBaudrateEvent.cpp)
add_boost_test(LinChecksumInfo test_LinChecksumInfo test_LinChecksumInfo.cpp)
add_boost_test(LinCrcError2 test_LinCrcError2 test_LinCrcError2.cpp)
add_boost_test(LinCrcError test_LinCrcError test_LinCrcError.cpp)
add_boost_test(LinDisturbanceEvent test_LinDisturbanceEvent test_LinDisturbanceEvent.cpp)
add_boost_test(LinDlcInfo test_LinDlcInfo test_LinDlcInfo.cpp)
add_boost_test(LinLongDomSignalEvent2 test_LinLongDomSignalEvent2 test_LinLongDomSignalEvent2.cpp)
add_boost_test(LinLongDomSignalEvent test_LinLongDomSignalEvent test_LinLongDomSignalEvent.cpp)
add_boost_test(LinMessage2 test_LinMessage2 test_LinMessage2.cpp)
add_boost_test(LinMessage test_LinMessage test_LinMessage.cpp)
add_boost_test(LinReceiveError2 test_LinReceiveError2 test_LinReceiveError2.cpp)
add_boost_test(LinReceiveError test_LinReceiveError test_LinReceiveError.cpp)
add_boost_test(LinSchedulerModeChange test_LinSchedulerModeChange test_LinSchedulerModeChange.cpp)
add_boost_test(LinSendError2 test_LinSendError2 test_LinSendError2.cpp)
add_boost_test(LinSendError test_LinSendError test_LinSendError.cpp)
add_boost_test(LinShortOrSlowResponse2 test_LinShortOrSlowResponse2 test_LinShortOrSlowResponse2.cpp)
add_boost_test(LinShortOrSlowResponse test_LinShortOrSlowResponse test_LinShortOrSlowResponse.cpp)
add_boost_test(LinSlaveTimeout test_LinSlaveTimeout test_LinSlaveTimeout.cpp)
add_boost_test(LinSleepModeEvent test_LinSleepModeEvent test_LinSleepModeEvent.cpp)
add_boost_test(LinSpikeEvent2 test_LinSpikeEvent2 test_LinSpikeEvent2.cpp)
add_boost_test(LinSpikeEvent test_LinSpikeEvent test_LinSpikeEvent.cpp)
add_boost_test(LinStatisticEvent test_LinStatisticEvent test_LinStatisticEvent.cpp)
add_boost_test(LinSyncError2 test_LinSyncError2 test_LinSyncError2.cpp)
add_boost_test(LinSyncError test_LinSyncError test_LinSyncError.cpp)
add_boost_test(LinUnexpectedWakeup test_LinUnexpectedWakeup test_LinUnexpectedWakeup.cpp)
add_boost_test(LinWakeupEvent2 test_LinWakeupEvent2 test_LinWakeupEvent2.cpp)
add_boost_test(LinWakeupEvent test_LinWakeupEvent test_LinWakeupEvent.cpp)
add_boost_test(LogContainer test_LogContainer test_LogContainer.cpp)
add_boost_test(Most150AllocTab test_Most150AllocTab test_Most150AllocTab.cpp)
add_boost_test(Most150MessageFragment test_Most150MessageFragment test_Most150MessageFragment.cpp)
add_boost_test(Most150Message test_Most150Message test_Most150Message.cpp)
add_boost_test(Most150PktFragment test_Most150PktFragment test_Most150PktFragment.cpp)
add_boost_test(Most150Pkt test_Most150Pkt test_Most150Pkt.cpp)
add_boost_test(Most50Message test_Most50Message test_Most50Message.cpp)
add_boost_test(Most50Pkt test_Most50Pkt test_Most50Pkt.cpp)
add_boost_test(MostAllocTab test_MostAllocTab test_MostAllocTab.cpp)
add_boost_test(MostCtrl test_MostCtrl test_MostCtrl.cpp)
add_boost_test(MostDataLost test_MostDataLost test_MostDataLost.cpp)
add_boost_test(MostEcl test_MostEcl test_MostEcl.cpp)
add_boost_test(MostEthernetPktFragment test_MostEthernetPktFragment test_MostEthernetPktFragment.cpp)
add_boost_test(MostEthernetPkt test_MostEthernetPkt test_MostEthernetPkt.cpp)
add_boost_test(MostGenReg test_MostGenReg test_MostGenReg.cpp)
add_boost_test(MostHwMode test_MostHwMode test_MostHwMode.cpp)
add_boost_test(MostLightLock test_MostLightLock test_MostLightLock.cpp)
add_boost_test(MostNetState test_MostNetState test_MostNetState.cpp)
add_boost_test(MostPkt2 test_MostPkt2 test_MostPkt2.cpp)
add_boost_test(MostPkt test_MostPkt test_MostPkt.cpp)
add_boost_test(MostReg test_MostReg test_MostReg.cpp)
add_boost_test(MostSpy test_MostSpy test_MostSpy.cpp)
add_boost_test(MostStatisticEx test_MostStatisticEx test_MostStatisticEx.cpp)
add_boost_test(MostStatistic test_MostStatistic test_MostStatistic.cpp)
add_boost_test(MostStress test_MostStress test_MostStress.cpp)
add_boost_test(MostSystemEvent test_MostSystemEvent test_MostSystemEvent.cpp)
add_boost_test(MostTrigger test_MostTrigger test_MostTrigger.cpp)
add_boost_test(MostTxLight test_MostTxLight test_MostTxLight.cpp)
add_boost_test(ObjectHeaderBase test_ObjectHeaderBase test_ObjectHeaderBase.cpp)
add_boost_test(ObjectQueue test_ObjectQueue test_ObjectQueue.cpp)
add_boost_test(RealtimeClock test_RealtimeClock test_RealtimeClock.cpp)
add_boost_test(SerialEvent test_SerialEvent test_SerialEvent.cpp)
add_boost_test(SingleByteSerialEvent test_SingleByteSerialEvent test_SingleByteSerialEvent.cpp)
add_boost_test(SystemVariable test_SystemVariable test_SystemVariable.cpp)
add_boost_test(TestStructure test_TestStructure test_TestStructure.cpp)
add_boost_test(TriggerCondition test_TriggerCondition test_TriggerCondition.cpp)
add_boost_test(UncompressedFile test_UncompressedFile test_UncompressedFile.cpp)
add_boost_test(WaterMarkEvent test_WaterMarkEvent test_WaterMarkEvent.cpp)
add_boost_test(WlanFrame test_WlanFrame test_WlanFrame.cpp)
add_boost_test(WlanStatistic test_WlanStatistic test_WlanStatistic.cpp)

# coverage
if(OPTION_USE_GCOV)
    add_custom_target(gcov_clean
        COMMAND find ${PROJECT_BINARY_DIR} -name '*.gcda' -delete)
endif()
if(OPTION_ADD_LCOV)
    add_custom_target(lcov_capture
        COMMAND ${LCOV_EXECUTABLE}
            --capture
            --directory ${PROJECT_BINARY_DIR}
            --output-file coverage.info
        DEPENDS
            ${test_targets})

    add_custom_target(lcov_genhtml
        ALL
        COMMAND ${LCOV_GENHTML_EXECUTABLE}
            --output-directory lcov
            coverage.info
        DEPENDS lcov_capture)

    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lcov
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()
