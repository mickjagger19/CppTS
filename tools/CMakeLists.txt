#
# Xin YUAN, 2019, BSD (2)
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
INCLUDE("${CMAKE_SOURCE_DIR}/CSL/csl.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/third/fltk/fltk.cmk")

PROJECT(tools)

#directories

ADD_SUBDIRECTORY(wmc wmc)
ADD_SUBDIRECTORY(WmarkEditor WmarkEditor)

# end
