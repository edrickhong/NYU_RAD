
cmake_minimum_required(VERSION 3.9)
project(RAD)

include(${CMAKE_SOURCE_DIR}/cmake/arduino_diecimila_crosscompile.cmake)

#Output directory variables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


if (APPLE)
else(APPLE)

	set(CMAKE_C_COMPILER /usr/bin/avr-gcc)
	set(CMAKE_CXX_COMPILER /usr/bin/avr-g++)

	include_directories(${CMAKE_SOURCE_DIR}/include/)

	file(GLOB SCREEN 
		${CMAKE_SOURCE_DIR}/src/screen/main.cpp)

	file(GLOB ARDUINOCORE 
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial.cpp
		${CMAKE_SOURCE_DIR}/src/core/Print.cpp
		${CMAKE_SOURCE_DIR}/src/core/wiring.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_shift.c
		${CMAKE_SOURCE_DIR}/src/core/WInterrupts.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_digital.c
		${CMAKE_SOURCE_DIR}/src/core/WMath.cpp
		${CMAKE_SOURCE_DIR}/src/core/pins_arduino.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_analog.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_pulse.c
		)

	# This will probably not be an exectuable

	add_library(arduinocore STATIC ${ARDUINOCORE})

	add_executable(screen ${SCREEN})
	
	target_link_libraries(screen arduinocore)

endif(APPLE)


