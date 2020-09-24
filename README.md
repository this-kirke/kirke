# libkirke

# Author: Justin Kirkegaard

# License:

Copyright 2020 Justin Kirkegaard

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## <ins>About</ins>

This project provides generic functionality for building C applications. This document gives a brief overview of the libkirke project.  Detailed documentation is hosted by Github Pages [here](https://this-kirke.github.io/kirke-docs/index.html).
  
## <ins>Building</ins>

CMake is the build system used for building libkirke.  To Build the project with the following commands: 

`<kirke project root>$ cmake -B build`  
`<kirke project root>$ cmake --build build`

This will build the project without tests, coverage or generated documentation in the directory `<kirke project root>/build`.

The generated target is a static library by default. To build a shared library instead of a static library, add the cmake option `-DBUILD_SHARED_LIBS=ON` to the generate (first) command.

Tests, coverage report and generated documentation can be enabled by setting the desired option as defined in the root CMakeLists.txt file. To generate the build with all options enabled, invoke the following command:  
    `<kirke project root>$ cmake -B build -DKIRKE_BUILD_TESTS=ON -DKIRKE_BUILD_DOCUMENTATION=ON`  

## <ins>Usage</ins>

This project is intended to be built as a library which consumer projects can link to. To bring libkirke into another project's build system as a dependency, simply clone the repository into the project tree then instruct CMake to build it with the command add_subdirectory( <path/to/kirke> ).  It is recommended to clone the repository using git submodule into a stuttered directory structure.  This allows having a separate CMakeLists.txt file in which build options and aliases can be configured, where they won't be overwritten when updating the submodule.

An example directory structure follows.

```
<project root>
    ├── 3rdParty  
        ├── kirke  
            ├── kirke (cloned repository - https://github.com/this-kirke/kirke )  
            ├── CMakeLists.txt  
```

Then, in `<project root>/3rdParty/kirke/CMakeLists.txt:`  
```
    # Set any desired options
    set( KIRKE_BUILD_TESTS ON )
    set( KIRKE_BUILD_DOCUMENTATION OFF )

    # Add the kirke source subdirectory
    add_subdiretory( kirke )
```

Then, in your root CMakeLists.txt, add the line `add_subdirectory( 3rdParty/kirke)`

At this point, the kirke target can be linked by any other targets in your build system via the CMake command target_link_libraries.

## <ins>Testing</ins>

Testing is accomplished using the Catch2 C++ testing framework. Tests can be built by setting the `KIRKE_BUILD_TESTS` option in kirke's root CMakeLists.txt. You can use CMake to run the tests with the following commands:
```
    <kirke_root>$ cmake -B build -DKIRKE_BUILD_TESTS=ON
    <kirke_root>$ cmake --build build
    <kirke_root>$ build/test__all
```
