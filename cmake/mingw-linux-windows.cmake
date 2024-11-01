SET(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_FIND_ROOT_PATH
        /usr/x86_64-w64-mingw32
    )
SET(CMAKE_INCLUDE_PATH ${CMAKE_FIND_ROOT_PATH}/include)
SET(CMAKE_LIBRARY_PATH ${CMAKE_FIND_ROOT_PATH}/lib)
SET(CURSES_INCLUDE_PATH ${CMAKE_FIND_ROOT_PATH}/include)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)