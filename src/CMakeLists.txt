cmake_minimum_required(VERSION 3.27)

target_sources(app PRIVATE
    main.cpp
    # bt.c

    # gcc/sys.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    gcc
)

target_link_libraries(app PUBLIC
    etl
)

target_compile_options(app PUBLIC
    "-w" # TODO enable warnings
)
