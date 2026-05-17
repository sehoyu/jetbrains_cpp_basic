# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-src")
  file(MAKE_DIRECTORY "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-src")
endif()
file(MAKE_DIRECTORY
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-build"
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix"
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/tmp"
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/src/googletest-stamp"
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/src"
  "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/yu/CLionProjects/C++_Basics/test-framework/googletest-prefix/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
