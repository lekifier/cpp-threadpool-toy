file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.hpp)
add_library(threadpool STATIC ${srcs})

target_include_directories(threadpool PUBLIC include)
target_link_libraries(threadpool PUBLIC utils)
