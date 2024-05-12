set(NRF5_SDK_PATH "" CACHE PATH "Path to the nRF5 SDK")

if(NOT NRF5_SDK_PATH)
  set(NRF5_SDK_PATH $ENV{NRF5_SDK_PATH})

  if(NOT NRF5_SDK_PATH)
    message(FATAL_ERROR "")
  endif()
endif()
