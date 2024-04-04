# Scripts

## Building
Two build scripts are provided for debug and release builds. The binaries will
be output to a top-level `bin` directory.

Dependencies are currently managed with Conan, but support for alternative
dependency managers will be added at a later date.

## Tests
If you would like to run tests, a `test.sh` script is also included. This will
build a Google Test executable.
