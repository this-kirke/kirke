\page about About

## <ins>About</ins>

This project provides generic functionality for building C applications.

This project relies heavily on open source software and tools. Acknowledgements to 

* Build system using [CMake](https://cmake.org "CMake")
* Unit testing using [Catch2](https://github.com/catchorg/Catch2/ "Catch2")
* Code coverage reports using [LCOV](http://ltp.sourceforge.net/coverage/lcov.php "LCOV")
* Documentation using [Doxygen](http://www.doxygen.nl "Doxygen")
* [doxygen_dark_theme]( https://github.com/MaJerle/doxygen-dark-theme "doxygen_dark_theme" ) written by MaJerle 
* Continuous Integration using [Travis.CI](https://travis-ci.org/ "Travis.CI" )

It is likely that other open source software was used in this project but not acknowledged. If your work was used but not acknowledged and you would like it to be, or if you notice another's work which was not acknowledged, please open an issue on the [project's GitHub page]( https://github.com/this-kirke/kata-word-search "project's GitHub page" ) and I will address it as soon as possible.  

  
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
