set(name ch6_stl)

project(${name})

set(HDRS
    vector1.h
)

set(SRCS
    stl.cc
    vector1.cc
)

include_directories("${HEADERS}/core/")

add_executable(${name} ${HDRS} ${SRCS})

target_link_libraries(${name} core)

