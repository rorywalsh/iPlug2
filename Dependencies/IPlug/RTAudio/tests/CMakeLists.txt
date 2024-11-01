include_directories(..)
if (WIN32)
    include_directories(../include)
endif (WIN32)

set(LIBRTAUDIO "/usr/local/lib/librtaudio.7.0.0.dylib")


# list(GET LIB_TARGETS 0 LIBRTAUDIO)

add_executable(audioprobe audioprobe.cpp)
set_property(TARGET audioprobe PROPERTY CXX_STANDARD 17)
target_link_libraries(audioprobe ${LIBRTAUDIO})

