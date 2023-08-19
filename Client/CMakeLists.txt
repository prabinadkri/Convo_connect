cmake_minimum_required(VERSION 3.0)
project(chat)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find Boost package
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Set the path to Homebrew libraries (modify this to match your installation path)
set(HOMEBREW_LIB_PATH /opt/homebrew)

# Find wxWidgets package
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


# Set the path to the bcrypt library (relative to your project root)
set(BCRYPT_LIB_PATH ${CMAKE_SOURCE_DIR}/bcrypt)

# Add include directory for bcrypt
include_directories(${BCRYPT_LIB_PATH}/include)

# Add your source files here
set(SOURCES
    MainApp.cpp
    main.cpp
    MainFrame.cpp
    SignupFrame.cpp
    # UI/bcrypt/bcrypt.cpp
    # bcrypt/blowfish.cpp
    MessageFrame.cpp
    ChatPanel.cpp 
    ContactListPanel.cpp 
    MessageBubble.cpp 
    UserProfileDialog.cpp
    

    # Add your other source files here
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Boost and wxWidgets libraries
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${wxWidgets_LIBRARIES}
)
 
