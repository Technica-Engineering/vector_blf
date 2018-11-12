# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Fixed
- Test AllLogFiles fixed

## [2.1.1] - 2018-11-11
### Added
- Jenkinsfile and Dockerfiles added
### Changed
- Update binlog examples to 4.7.1.0
### Fixed
- Fix padding in FlexRayVFrReceiveMsgEx
- Compilation of example parser with VS >=2015

## [2.1.0] - 2018-09-15
### Added
- New Objects: FunctionBus, DataLostBegin/End, WaterMarkEvent, TriggerCondition
### Changed
- Updated from binlog API version 4.5.2.2 to 4.7.1.0
### Fixed
- Fixed CanFdMessage64

## [2.0.1] - 2018-08-23
### Fixed
- Fixed memory leak with introduction of std::shared_ptr

## [2.0.0] - 2018-03-06
### Changed
- Multi-Threading support using two threads between three data structures.
- File::OpenMode replaced by standard std::ios_base::openmode.
- LogContainer now contains uncompressedFile and compressedFile containers.
- LogContainer now contains uncompress/compress methods.
- UncompressedFile now based on std::list<LogContainer *> for performance.

## [1.2.1] - 2017-12-29
### Added
- Preliminary support for object type 115. EOF message incl. FileStatistics.
### Fixed
- Further tests, especially writing files.
- Fix log write with compressionLevel = 0.
- Correct test BLF files.

## [1.2.0] - 2017-12-20
### Added
- Object generator to create blf test samples under Windows.
### Changed
- Updated from binlog API version 3.9.6.0 to 4.5.2.2.
### Fixed
- Implemented test cases for all object types, and fixed them.

## [1.1.2] - 2017-10-27
### Changed
- CXX_EXTENSIONS added and gcc pedantic flag for portability reasons
### Fixed
- CXX_STANDARD_REQUIRED was fixed to reflect C++11 requirement

## [1.1.1] - 2017-09-22
### Changed
- Update to latest project template
- "using" instead of "typedef"
### Fixed
- generate_export_header got lost.

## [1.1.0] - 2016-03-22
### Added
- Exceptions to handle unexpected file or object signature.
### Changed
- C++11 override and final clauses
- Fixed further static compiler warnings under msvc, clang
### Fixed
- compressionLevel is now used. Previously only default compression was applied.
- Update CMakeLists.txt to latest project standard. Maybe fix #1.

## [1.0.2] - 2016-06-30
### Changed
- Performance improvements in File::read
- Closed many static compiler warnings under gcc, msvc, clang
### Fixed
- Fixed crash when using Visual Studio and 32-bit compilation
- Compiler hardening flags made compatible with gcc-4.8

## [1.0.1] - 2016-05-20
### Changed
- Compiler hardening flags enabled

## [1.0.0] - 2016-05-20
### Added
- Initial version
