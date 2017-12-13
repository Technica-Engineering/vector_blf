# combines: targets, sources/headers, compiler/linker settings, tests
set(test_targets )
function(add_boost_test test_name test_target)
    # targets
    add_executable(${test_target} "")

    # sources/headers
    target_sources(${test_target} PRIVATE ${ARGN})

    # compiler/linker settings
    target_link_libraries(${test_target}
        PRIVATE
            ${PROJECT_NAME}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    if(OPTION_USE_GCOV_LCOV)
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

# test events
#add_boost_test(A429BusStatistic test_A429BusStatistic events/test_A429BusStatistic.cpp)
#add_boost_test(A429Error test_A429Error events/test_A429Error.cpp)
#add_boost_test(A429Message test_A429Message events/test_A429Message.cpp)
#add_boost_test(A429Status test_A429Status events/test_A429Status.cpp)
#add_boost_test(AfdxBusStatistic test_AfdxBusStatistic events/test_AfdxBusStatistic.cpp)
#add_boost_test(AfdxErrorEvent test_AfdxErrorEvent events/test_AfdxErrorEvent.cpp)
#add_boost_test(AfdxFrame test_AfdxFrame events/test_AfdxFrame.cpp)
#add_boost_test(AfdxStatistic test_AfdxStatistic events/test_AfdxStatistic.cpp)
#add_boost_test(AfdxStatus test_AfdxStatus events/test_AfdxStatus.cpp)
add_boost_test(AppText test_AppText events/test_AppText.cpp)
add_boost_test(AppTrigger test_AppTrigger events/test_AppTrigger.cpp)
add_boost_test(CanDriverError test_CanDriverError events/test_CanDriverError.cpp)
add_boost_test(CanDriverErrorExt test_CanDriverErrorExt events/test_CanDriverErrorExt.cpp)
add_boost_test(CanDriverHwSync test_CanDriverHwSync events/test_CanDriverHwSync.cpp)
add_boost_test(CanDriverStatistic test_CanDriverStatistic events/test_CanDriverStatistic.cpp)
add_boost_test(CanErrorFrame test_CanErrorFrame events/test_CanErrorFrame.cpp)
add_boost_test(CanErrorFrameExt test_CanErrorFrameExt events/test_CanErrorFrameExt.cpp)
#add_boost_test(CanFdErrorFrame64 test_CanFdErrorFrame64 events/test_CanFdErrorFrame64.cpp)
#add_boost_test(CanFdMessage64 test_CanFdMessage64 events/test_CanFdMessage64.cpp)
#add_boost_test(CanFdMessage test_CanFdMessage events/test_CanFdMessage.cpp)
add_boost_test(CanMessage test_CanMessage events/test_CanMessage.cpp)
add_boost_test(CanMessage2 test_CanMessage2 events/test_CanMessage2.cpp)
add_boost_test(CanOverloadFrame test_CanOverloadFrame events/test_CanOverloadFrame.cpp)
#add_boost_test(DiagRequestInterpretation test_DiagRequestInterpretation events/test_DiagRequestInterpretation.cpp)
add_boost_test(DriverOverrun test_DriverOverrun events/test_DriverOverrun.cpp)
#add_boost_test(EnvironmentVariable test_EnvironmentVariable events/test_EnvironmentVariable.cpp)
#add_boost_test(EthernetErrorEx test_EthernetErrorEx events/test_EthernetErrorEx.cpp)
#add_boost_test(EthernetErrorForwarded test_EthernetErrorForwarded events/test_EthernetErrorForwarded.cpp)
#add_boost_test(EthernetFrameEx test_EthernetFrameEx events/test_EthernetFrameEx.cpp)
#add_boost_test(EthernetFrameForwarded test_EthernetFrameForwarded events/test_EthernetFrameForwarded.cpp)
#add_boost_test(EthernetFrame test_EthernetFrame events/test_EthernetFrame.cpp)
#add_boost_test(EthernetRxError test_EthernetRxError events/test_EthernetRxError.cpp)
#add_boost_test(EthernetStatistic test_EthernetStatistic events/test_EthernetStatistic.cpp)
#add_boost_test(EthernetStatus test_EthernetStatus events/test_EthernetStatus.cpp)
#add_boost_test(EventComment test_EventComment events/test_EventComment.cpp)
#add_boost_test(FlexRayData test_FlexRayData events/test_FlexRayData.cpp)
#add_boost_test(FlexRayStatusEvent test_FlexRayStatusEvent events/test_FlexRayStatusEvent.cpp)
#add_boost_test(FlexRaySync test_FlexRaySync events/test_FlexRaySync.cpp)
#add_boost_test(FlexRayV6Message test_FlexRayV6Message events/test_FlexRayV6Message.cpp)
#add_boost_test(FlexRayV6StartCycleEvent test_FlexRayV6StartCycleEvent events/test_FlexRayV6StartCycleEvent.cpp)
#add_boost_test(FlexRayVFrError test_FlexRayVFrError events/test_FlexRayVFrError.cpp)
#add_boost_test(FlexRayVFrReceiveMsgEx test_FlexRayVFrReceiveMsgEx events/test_FlexRayVFrReceiveMsgEx.cpp)
#add_boost_test(FlexRayVFrReceiveMsg test_FlexRayVFrReceiveMsg events/test_FlexRayVFrReceiveMsg.cpp)
#add_boost_test(FlexRayVFrStartCycle test_FlexRayVFrStartCycle events/test_FlexRayVFrStartCycle.cpp)
#add_boost_test(FlexRayVFrStatus test_FlexRayVFrStatus events/test_FlexRayVFrStatus.cpp)
#add_boost_test(GlobalMarker test_GlobalMarker events/test_GlobalMarker.cpp)
#add_boost_test(GpsEvent test_GpsEvent events/test_GpsEvent.cpp)
#add_boost_test(J1708Message test_J1708Message events/test_J1708Message.cpp)
#add_boost_test(KLineStatusEvent test_KLineStatusEvent events/test_KLineStatusEvent.cpp)
#add_boost_test(LinBaudrateEvent test_LinBaudrateEvent events/test_LinBaudrateEvent.cpp)
#add_boost_test(LinChecksumInfo test_LinChecksumInfo events/test_LinChecksumInfo.cpp)
#add_boost_test(LinCrcError2 test_LinCrcError2 events/test_LinCrcError2.cpp)
#add_boost_test(LinCrcError test_LinCrcError events/test_LinCrcError.cpp)
#add_boost_test(LinDisturbanceEvent test_LinDisturbanceEvent events/test_LinDisturbanceEvent.cpp)
#add_boost_test(LinDlcInfo test_LinDlcInfo events/test_LinDlcInfo.cpp)
#add_boost_test(LinLongDomSignalEvent2 test_LinLongDomSignalEvent2 events/test_LinLongDomSignalEvent2.cpp)
#add_boost_test(LinLongDomSignalEvent test_LinLongDomSignalEvent events/test_LinLongDomSignalEvent.cpp)
#add_boost_test(LinMessage2 test_LinMessage2 events/test_LinMessage2.cpp)
#add_boost_test(LinMessage test_LinMessage events/test_LinMessage.cpp)
#add_boost_test(LinReceiveError2 test_LinReceiveError2 events/test_LinReceiveError2.cpp)
#add_boost_test(LinReceiveError test_LinReceiveError events/test_LinReceiveError.cpp)
#add_boost_test(LinSchedulerModeChange test_LinSchedulerModeChange events/test_LinSchedulerModeChange.cpp)
#add_boost_test(LinSendError2 test_LinSendError2 events/test_LinSendError2.cpp)
#add_boost_test(LinSendError test_LinSendError events/test_LinSendError.cpp)
#add_boost_test(LinShortOrSlowResponse2 test_LinShortOrSlowResponse2 events/test_LinShortOrSlowResponse2.cpp)
#add_boost_test(LinShortOrSlowResponse test_LinShortOrSlowResponse events/test_LinShortOrSlowResponse.cpp)
#add_boost_test(LinSlaveTimeout test_LinSlaveTimeout events/test_LinSlaveTimeout.cpp)
#add_boost_test(LinSleepModeEvent test_LinSleepModeEvent events/test_LinSleepModeEvent.cpp)
#add_boost_test(LinSpikeEvent2 test_LinSpikeEvent2 events/test_LinSpikeEvent2.cpp)
#add_boost_test(LinSpikeEvent test_LinSpikeEvent events/test_LinSpikeEvent.cpp)
#add_boost_test(LinStatisticEvent test_LinStatisticEvent events/test_LinStatisticEvent.cpp)
#add_boost_test(LinSyncError2 test_LinSyncError2 events/test_LinSyncError2.cpp)
#add_boost_test(LinSyncError test_LinSyncError events/test_LinSyncError.cpp)
#add_boost_test(LinUnexpectedWakeup test_LinUnexpectedWakeup events/test_LinUnexpectedWakeup.cpp)
#add_boost_test(LinWakeupEvent2 test_LinWakeupEvent2 events/test_LinWakeupEvent2.cpp)
#add_boost_test(LinWakeupEvent test_LinWakeupEvent events/test_LinWakeupEvent.cpp)
#add_boost_test(Most150AllocTab test_Most150AllocTab events/test_Most150AllocTab.cpp)
#add_boost_test(Most150MessageFragment test_Most150MessageFragment events/test_Most150MessageFragment.cpp)
#add_boost_test(Most150Message test_Most150Message events/test_Most150Message.cpp)
#add_boost_test(Most150PktFragment test_Most150PktFragment events/test_Most150PktFragment.cpp)
#add_boost_test(Most150Pkt test_Most150Pkt events/test_Most150Pkt.cpp)
#add_boost_test(Most50Message test_Most50Message events/test_Most50Message.cpp)
#add_boost_test(Most50Pkt test_Most50Pkt events/test_Most50Pkt.cpp)
#add_boost_test(MostAllocTab test_MostAllocTab events/test_MostAllocTab.cpp)
#add_boost_test(MostCtrl test_MostCtrl events/test_MostCtrl.cpp)
#add_boost_test(MostDataLost test_MostDataLost events/test_MostDataLost.cpp)
#add_boost_test(MostEcl test_MostEcl events/test_MostEcl.cpp)
#add_boost_test(MostEthernetPktFragment test_MostEthernetPktFragment events/test_MostEthernetPktFragment.cpp)
#add_boost_test(MostEthernetPkt test_MostEthernetPkt events/test_MostEthernetPkt.cpp)
#add_boost_test(MostGenReg test_MostGenReg events/test_MostGenReg.cpp)
#add_boost_test(MostHwMode test_MostHwMode events/test_MostHwMode.cpp)
#add_boost_test(MostLightLock test_MostLightLock events/test_MostLightLock.cpp)
#add_boost_test(MostNetState test_MostNetState events/test_MostNetState.cpp)
#add_boost_test(MostPkt2 test_MostPkt2 events/test_MostPkt2.cpp)
#add_boost_test(MostPkt test_MostPkt events/test_MostPkt.cpp)
#add_boost_test(MostReg test_MostReg events/test_MostReg.cpp)
#add_boost_test(MostSpy test_MostSpy events/test_MostSpy.cpp)
#add_boost_test(MostStatisticEx test_MostStatisticEx events/test_MostStatisticEx.cpp)
#add_boost_test(MostStatistic test_MostStatistic events/test_MostStatistic.cpp)
#add_boost_test(MostStress test_MostStress events/test_MostStress.cpp)
#add_boost_test(MostSystemEvent test_MostSystemEvent events/test_MostSystemEvent.cpp)
#add_boost_test(MostTrigger test_MostTrigger events/test_MostTrigger.cpp)
#add_boost_test(MostTxLight test_MostTxLight events/test_MostTxLight.cpp)
add_boost_test(RealtimeClock test_RealtimeClock events/test_RealtimeClock.cpp)
#add_boost_test(SerialEvent test_SerialEvent events/test_SerialEvent.cpp)
#add_boost_test(SystemVariable test_SystemVariable events/test_SystemVariable.cpp)
add_boost_test(TestStructure test_TestStructure events/test_TestStructure.cpp)
#add_boost_test(WlanFrame test_WlanFrame events/test_WlanFrame.cpp)
#add_boost_test(WlanStatistic test_WlanStatistic events/test_WlanStatistic.cpp)

# do we need these tests?
#add_boost_test(AbstractFile test_AbstractFile events/test_AbstractFile.cpp)
#add_boost_test(CanFdExtFrameData test_CanFdExtFrameData events/test_CanFdExtFrameData.cpp)
#add_boost_test(CompressedFile test_CompressedFile events/test_CompressedFile.cpp)
#add_boost_test(Exceptions test_Exceptions events/test_Exceptions.cpp)
#add_boost_test(File test_File events/test_File.cpp)
#add_boost_test(FileStatistics test_FileStatistics events/test_FileStatistics.cpp)
#add_boost_test(LinBusEvent test_LinBusEvent events/test_LinBusEvent.cpp)
#add_boost_test(LinDatabyteTimestampEvent test_LinDatabyteTimestampEvent events/test_LinDatabyteTimestampEvent.cpp)
#add_boost_test(LinMessageDescriptor test_LinMessageDescriptor events/test_LinMessageDescriptor.cpp)
#add_boost_test(LinSynchFieldEvent test_LinSynchFieldEvent events/test_LinSynchFieldEvent.cpp)
#add_boost_test(LogContainer test_LogContainer events/test_LogContainer.cpp)
#add_boost_test(ObjectHeader2 test_ObjectHeader2 events/test_ObjectHeader2.cpp)
#add_boost_test(ObjectHeaderBase test_ObjectHeaderBase events/test_ObjectHeaderBase.cpp)
#add_boost_test(ObjectHeader test_ObjectHeader events/test_ObjectHeader.cpp)
#add_boost_test(platform test_platform events/test_platform.cpp)
#add_boost_test(UncompressedFile test_UncompressedFile events/test_UncompressedFile.cpp)
#add_boost_test(VectorTypes test_VectorTypes events/test_VectorTypes.cpp)

# overall tests
#add_boost_test(AllEvents test_AllEvents test_AllEvents.cpp)
#add_boost_test(AllLogfiles test_AllLogfiles test_AllLogfiles.cpp)

# coverage
if(OPTION_USE_GCOV_LCOV)
    add_custom_target(lcov_capture ALL
        COMMAND ${LCOV_EXECUTABLE}
            --capture
            --directory ${PROJECT_BINARY_DIR}
            --output-file coverage.info || true
        DEPENDS
            ${test_targets})

    add_custom_target(lcov_genhtml ALL
        COMMAND ${LCOV_GENHTML_EXECUTABLE}
            coverage.info
            --output-directory lcov || true
        DEPENDS lcov_capture)

    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lcov
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()
