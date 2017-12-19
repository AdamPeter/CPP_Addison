set(name core)

project(${name})

set(SRCS
    example_runner.cc
)

include_directories("${HEADERS}/core/")
add_library(${name} STATIC ${SRCS})

