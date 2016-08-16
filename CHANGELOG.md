# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Changed
- C++11 override and final clauses
- Fixed further static compiler warnings under msvc, clang
### Fixed
- compressionLevel is now used. Previously only default compression was applied.

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
