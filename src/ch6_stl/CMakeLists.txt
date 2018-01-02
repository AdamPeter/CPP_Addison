set(name ch6_stl)

project(${name})

set(HDRS
    vector1.h
    multimap1.h
    algo1.h
    find1.h
    copy2.h
    ioiter1.h
    reviter1.h
)

set(SRCS
    stl.cc
    vector1.cc
    multimap1.cc
    algo1.cc
    find1.cc
    copy2.cc
    ioiter1.cc
    reviter1.cc
)

include_directories("${HEADERS}/core/")

add_executable(${name} ${HDRS} ${SRCS})

target_link_libraries(${name} core)

