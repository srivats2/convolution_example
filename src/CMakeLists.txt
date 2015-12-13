
# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( " " )
  Message(FATAL_ERROR "Source and build  directories are the same.C reate an empty build directory, change into it and re-invoke cmake")
endif()


# To use PKG_CHECK_MODULES to find some optional packages
find_package(PkgConfig)

#    Tell CMake where to leave executables
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
IF(APPLE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/macosx/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/macosx/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/macosx/)
ELSEIF(UNIX)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/linux/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/linux/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
ELSEIF(WIN32)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/win32/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/win32/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win32/)
ENDIF()

SET( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )


#Path of CImg.h file relative to this file path
set(CIMG_H_PATH ${PROJECT_SOURCE_DIR}/headers/)

include_directories( ${CIMG_H_PATH})


# ### CIMG related stuff
# Flags to enable fast image display, using the XSHM library.
SET(CIMG_XSHM_CCFLAGS  -Dcimg_use_xshm)

# Flags to enable screen mode switching, using the XRandr library.
SET(CIMG_XRANDR_CCFLAGS  -Dcimg_use_xrandr)

# Flags to enable native support for JPEG image files, using the JPEG library.
# ( http://www.ijg.org/ )
SET(CIMG_JPEG_CCFLAGS  -Dcimg_use_jpeg)

# Flags to enable native support for TIFF image files, using the TIFF library.
# ( http://www.libtiff.org/ )
SET(CIMG_TIFF_CCFLAGS  -Dcimg_use_tiff)

# Flags to enable native support for PNG image files, using the PNG library.
# ( http://www.libpng.org/ )
SET(CIMG_PNG_CCFLAGS  -Dcimg_use_png)

#Flags to enable OPENCV support (Camera)
# ( http://www.opencv.org/ )
SET(CIMG_OPENCV_CCFLAGS -Dcimg_use_opencv)

# Flags to enable native support for EXR image files, using the OpenEXR library.
# ( http://www.openexr.com/ )
SET(CIMG_OPENEXR_CCFLAGS  -Dcimg_use_openexr)

# Flags to enable native support for various video files, using the FFMPEG library.
# ( http://www.ffmpeg.org/ )
SET(CIMG_FFMPEG_CCFLAGS  -Dcimg_use_ffmpeg)

# Flags to enable native support of most classical image file formats, using the Magick++ library.
# ( http://www.imagemagick.org/Magick++/ )
# added quantum depth to support the newest library
SET(CIMG_MAGICK_CCFLAGS -Dcimg_use_magick)


# Flags to enable faster Discrete Fourier Transform computation, using the FFTW3 library
# ( http://www.fftw.org/ )
SET(CIMG_FFTW3_CCFLAGS  -Dcimg_use_fftw3)


# Flags to enable OpenMP support for CIMG...WARNING!! FFTW3 library needs to be compiled with OpenMP support
# if you wish to use this otherwise this might be slower
# On AUR the package is called fftw-mpi

SET(CIMG_OPENMP_CCFLAGS -Dcimg_use_openmp)





# ### Search Additional Libraries ##########
FIND_PACKAGE(ZLIB)
FIND_PACKAGE(PNG)
FIND_PACKAGE(JPEG)
FIND_PACKAGE(TIFF)
FIND_PACKAGE(OpenCV)
FIND_PACKAGE(LAPACK)
FIND_PACKAGE(BLAS)
FIND_PACKAGE(OpenMP REQUIRED)
FIND_PACKAGE(CXX11)
FIND_PACKAGE(FFTW)


if(NOT WIN32)
  FIND_PACKAGE(X11)
  FIND_PACKAGE(Threads REQUIRED)
endif()

# #### End of additional libraries search ##########
### Configure Paths according to detected packages
if(TIFF_FOUND)
  get_filename_component(TIFF_LIB_DIRS ${TIFF_LIBRARIES} PATH)
  SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_TIFF_CCFLAGS}")
  link_directories(${TIFF_LIB_DIRS})
  #MESSAGE(${TIFF_LIB_DIRS})
  include_directories(${TIFF_INCLUDE_DIR})
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${TIFF_LIBRARIES})
endif()



if(JPEG_FOUND)
  get_filename_component(JPEG_LIB_DIRS ${JPEG_LIBRARIES} PATH)
  SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_JPEG_CCFLAGS}")
  link_directories(${JPEG_LIB_DIRS})
  #MESSAGE(${JPEG_LIB_DIRS})
  include_directories(${JPEG_INCLUDE_DIR})
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${JPEG_LIBRARIES})
endif()




if (ZLIB_FOUND)
  SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_ZLIB_CCFLAGS}")
  link_directories(${ZLIB_LIB_DIRS})
  include_directories(${ZLIB_INCLUDE_DIR})
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${ZLIB_LIBRARIES})

  # PNG requires ZLIB
  if(PNG_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_PNG_CCFLAGS}")
    link_directories(${PNG_LIB_DIRS})
    include_directories(${PNG_INCLUDE_DIR} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${PNG_LIBRARIES} )
  endif()
endif()




if(FFTW_FOUND)
  MESSAGE("FFTW3 FOUND")
  SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_FFTW3_CCFLAGS}")
  link_directories( ${FFTW_LIBRARY_DIRS} )
  include_directories( ${FFTW_INCLUDE_DIRS} )
  include_directories( ${FFTW_INCLUDES})
  SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${FFTW_LIBRARIES} )
endif()



if(NOT APPLE)
  if(NOT WIN32)
    if(X11_FOUND)
      SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_XSHM_CCFLAGS} ${CIMG_XRANDR_CCFLAGS}")
      SET(SYSTEM_LIBS ${SYSTEM_LIBS} Xext Xrandr)
    endif()
  endif(NOT WIN32)
endif(NOT APPLE)

if(X11_FOUND)
  link_directories(${X11_LIB_DIRS})
  include_directories(${X11_INCLUDE_DIR})
  SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()

if (NOT WIN32)
  SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if( WIN32)
  SET( SYSTEM_LIBS  ${SYSTEM_LIBS}  gdi32 )
endif()



if (OPENMP_FOUND)
    MESSAGE("OPENMP FOUND")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    #SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_OPENMP_CCFLAGS}")
endif()


#Enable C++11 support
if(CXX11_FOUND)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  # needed for gcc 4.6+
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()



# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")


add_executable(convolution_test main.cxx 
ImageConvolutionFilter.cxx 
ImageBase.cxx 
Image2D.cxx
GaussianFilterConvolution.cxx
${CIMG_H_PATH}/GaussianFilterConvolution.hxx
${CIMG_H_PATH}/ImageConvolutionFilter.hxx
${CIMG_H_PATH}/ImageBase.hxx
${CIMG_H_PATH}/Image2D.hxx
${CIMG_H_PATH}/ImageFilterBase.hxx)

target_link_libraries(convolution_test ${SYSTEM_LIBS})
