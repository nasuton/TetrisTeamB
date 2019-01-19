
# set friendly platform define
 if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
     set(WINDOWS TRUE)
     set(SYSTEM_STRING "Windows Desktop")
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
     set(SYSTEM_STRING "Android")
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
     if(ANDROID)
         set(SYSTEM_STRING "Android")
     else()
         set(LINUX TRUE)
         set(SYSTEM_STRING "Linux")
     endif()
 elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     if(IOS)
         set(APPLE TRUE)
         set(SYSTEM_STRING "IOS")
     else()
         set(APPLE TRUE)
         set(MACOSX TRUE)
         set(SYSTEM_STRING "Mac OSX")
     endif()
 endif()

# part libs existed debug and release both type
string(TOLOWER ${CMAKE_BUILD_TYPE} _type_folder)
# Visual Studio 2017 default build type include "Debug Release MinSizRel RelWithDebInfo"
if(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    set(_type_folder "debug")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizRel")
    set(_type_folder "release")
endif()

# set platform specific path
set(_path_prefix ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/)
if(IOS)
    set(platform_name ios)
    set(platform_spec_path ios)
elseif(ANDROID)
    set(platform_name android)
    set(platform_spec_path android/${ANDROID_ABI})
elseif(WINDOWS)
    set(platform_name win32)
    # win32/, win32/debug, win32/debug-lib 
    if(EXISTS ${_path_prefix}/win32/${_type_folder}-lib)
        set(platform_spec_path win32/${_type_folder}-lib)
    elseif(EXISTS ${_path_prefix}win32/${_type_folder})
        set(platform_spec_path win32/${_type_folder})
    else()
        set(platform_spec_path win32)
    endif()
elseif(MACOSX)
    set(platform_name mac)
    set(platform_spec_path mac)
elseif(LINUX)
    set(platform_name linux)
    set(platform_spec_path linux/64-bit)
endif()

set(platform_spec_path "${_path_prefix}${platform_spec_path}")
