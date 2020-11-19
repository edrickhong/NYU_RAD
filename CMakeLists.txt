
cmake_minimum_required(VERSION 3.9)
project(RAD)

enable_language(CXX ASM)

#Output directory variables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


if (APPLE)
else(APPLE)

	set(CMAKE_SYSTEM_NAME Generic)

	if(UNIX)
		set(CMAKE_C_COMPILER /usr/bin/avr-gcc)
		set(CMAKE_CXX_COMPILER /usr/bin/avr-g++)
		set(CMAKE_ASM_COMPILER /usr/bin/avr-g++)
	else(UNIX)

		set(CMAKE_C_COMPILER C:/WinAVR-20100110/bin/avr-gcc.exe)
		set(CMAKE_CXX_COMPILER C:/WinAVR-20100110/bin/avr-g++.exe)
		message(STATUS "Setting Windows compilers")

	endif(UNIX)

	set(COMPILE_FLAGS "-gstabs -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -O0 -mmcu=atmega2560 -DF_CPU=16000000")
	set(ASM_FLAGS "-x assembler-with-cpp")

	set(CMAKE_C_FLAGS ${COMPILE_FLAGS})
	set(CMAKE_CXX_FLAGS ${COMPILE_FLAGS})
	set(CMAKE_ASM_FLAGS "${ASM_FLAGS} ${COMPILE_FLAGS}")

	include_directories(${CMAKE_SOURCE_DIR}/include/)

	file(GLOB SCREEN 
		${CMAKE_SOURCE_DIR}/src/screen/main.cpp)

	file(GLOB ARDUINOCORE 
		${CMAKE_SOURCE_DIR}/src/core/wiring_pulse.S
		${CMAKE_SOURCE_DIR}/src/core/WInterrupts.c
		${CMAKE_SOURCE_DIR}/src/core/wiring.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_analog.c
		${CMAKE_SOURCE_DIR}/src/core/hooks.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_shift.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_pulse.c
		${CMAKE_SOURCE_DIR}/src/core/wiring_digital.c
		${CMAKE_SOURCE_DIR}/src/core/PluggableUSB.cpp
		${CMAKE_SOURCE_DIR}/src/core/USBCore.cpp
		${CMAKE_SOURCE_DIR}/src/core/Print.cpp
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial3.cpp
		${CMAKE_SOURCE_DIR}/src/core/WMath.cpp
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial1.cpp
		${CMAKE_SOURCE_DIR}/src/core/main.cpp
		${CMAKE_SOURCE_DIR}/src/core/Stream.cpp
		${CMAKE_SOURCE_DIR}/src/core/Tone.cpp
		${CMAKE_SOURCE_DIR}/src/core/abi.cpp
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial2.cpp
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial10.cpp
		${CMAKE_SOURCE_DIR}/src/core/IPAddress.cpp
		${CMAKE_SOURCE_DIR}/src/core/HardwareSerial.cpp
		${CMAKE_SOURCE_DIR}/src/core/WString.cpp
		${CMAKE_SOURCE_DIR}/src/core/CDC.cpp
		${CMAKE_SOURCE_DIR}/src/core/new.cpp

		)

	add_library(arduinocore STATIC ${ARDUINOCORE})
	add_executable(screen ${SCREEN})
	target_link_libraries(screen arduinocore)

	#convert the elf file to hex

	add_custom_command(
		OUTPUT screen.hex
		DEPENDS screen

		COMMAND avr-objcopy -O ihex -R .eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/screen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/screen.hex
		)

	add_custom_target(run ALL DEPENDS screen.hex)

endif(APPLE)


