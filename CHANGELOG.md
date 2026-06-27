# Changelog

All notable changes to this package will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Configurable settings for Time module.
- Job module.
- World module.
- File module.
- Resource module.
- Resource file module.
- File resource manifest compiler.

### Changed

- IRawInputContext doesn't have functions for registering/unregistering devices and adding input any more. Now IInputProvider gets special interfaces for that in its Begin(), End() and Tick().
- PonyEngine.Application.Impl is an optional module now.

### Removed

- Axis and DeviceType classes removed from raw input module. Now usual string views are used instead.

## [0.1.1] - 2026-04-21

### Fixed

- Incorrect GIT_TAG in samples.

## [0.1.0] - 2026-04-14

### Added

- Core module.
- Application module.
- Log module.
- Log file module.
- Time module.
- Message pump module.
- Surface module.
- Raw input module.
- Raw input keyboard module.
- Raw input mouse module.
- Raw input XInput module.
- Shader module.
- Render device module.
- Direct3D12 backend module.
- Windows platform support.
- MSVC compiler support.
- DXC compiler support.

[unreleased]: https://github.com/ZorPastaman/PonyEngine/compare/v0.1.1...HEAD
[0.1.1]: https://github.com/ZorPastaman/PonyEngine/releases/tag/v0.1.1
[0.1.0]: https://github.com/ZorPastaman/PonyEngine/releases/tag/v0.1.0
