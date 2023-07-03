file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.hpp)

add_library(utils STATIC ${srcs})
target_include_directories(utils PUBLIC include)
