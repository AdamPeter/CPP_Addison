set(name ch18_concurrency)

project(${name})

set(SRCS
    main.cc
)

include_directories("../../include")

add_executable(${name} ${SRCS})



