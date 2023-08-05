# Shared Memory Debugging tools (shm-debugger)

This set of tools provides a comprehensive solution for debugging apps that rely on
reading data from shared memory. It allows recording and replaying data, making it easier
to analyze and troubleshoot issues. Primarily aimed for racing simulators,
but can be expanded to use with any app with similar usage pattern
(read data updated by app in shared memory).

TODO:

* [ ] GitHub Actions CI
* [ ] AC support
* [ ] R3E support?
* [ ] Docs

# Bundled tools

## Dumper

This tool reads shared memory with the specified frequency and saves
raw data to file. It uses compression to make files smaller. Usually
40 minutes iRacing file written with 5 Hz frequency is about 100MB.

```
Allowed options:
--help              Produce help message
--fps arg           Frames per second (default =5)
```

Usage:

Start an application by double-clicking on it or by opening a console and
typing `shmd-dumper.exe`. Go into the sim and drive. After you're finished
go to the console window that runs dumper and press `Ctrl+C`. The message
`Ctrl+C detected. Stopping the job. Please wait patiently...` should appear.
Wait patiently as it says, in a couple of seconds it should say
`You can now close this window`. Don't close the console window with the
dumper running or the output file can be corrupted. The output file will
be saved in the same folder with the dumper binary with the name started
with `shmd_dump_`, current date and time in the name and `.bin` extension.

## Emulator

This tool reads the specified file (generated by dumper) and outputs
data to shared memory as if it was generated by the simulator allowing
third-party apps to connect to shared memory.

```
Allowed options:
  --help                Produce help message
  --input-file arg      Input file name (required)
```

Usage:

Open a console, type `shmd-dumper.exe --input-file=path/to/shmd_dump.bin`.
Emulator will start streaming data into shared memory. When finished stop
emulator with `Ctrl+C`. Wait for the message saying `You can now close
this window`.

Start

# Supported simulators

- iRacing
- Assetto Corsa Competizione

Vanilla AC is coming later

# Dependencies

- boost
- zlib
- GTest

# Build

## Using conan 1.x

```
conan install . -if cmake-build-release-visual-studio/dependencies/conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Release
cmake -S . -B cmake-build-release-visual-studio -D "CMAKE_MODULE_PATH=cmake-build-release-visual-studio/dependencies/conan"
cmake --build
```

Debug

```
conan install . -if cmake-build-debug-visual-studio/dependencies/conan --build missing -s compiler="Visual Studio" -s compiler.version=16 -s cppstd=20 -s build_type=Debug
```

## Repo content

- `shmd-lib` - main application library
- `shmd-tests` - GTest-based unit tests for `shmd-lib`
- `shmd-dumper` - a commandline tool for dumping simulator-generated data to disk
- `shmd-emulator` - a commandline tool for reading dumps and streaming data to shared memory as if it
  was generated by the simulator

# License

This project is distributed under MIT license

Copyright (c) Dmitriy Linev 2023