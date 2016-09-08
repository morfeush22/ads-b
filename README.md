# ADS-B decoder
Purpose of program is to continuously receive and decode ADS-B messages.
Input is gathered either from antenna or file. Readable messages can be displayed on console.

# BUILD

### Windows for Visual
    mkdir win_build
    cd win_build
    cmake -G "Visual Studio 14 2015 Win64" ..
Then open generated solution in visual
Run Unit Tests (in project Tests)
Set ads_b as StartUp project and run

### Linux
    mkdir linux_build
    cd linux_build
    cmake ..
    make -j4
    ./Tests
    ./ads_b
