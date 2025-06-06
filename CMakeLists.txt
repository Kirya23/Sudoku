cmake_minimum_required(VERSION 3.16)

project(Sudoku VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

# Основные исходные файлы приложения
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    gamewindow.h gamewindow.cpp gamewindow.ui
    sudokugenerator.h sudokugenerator.cpp
    levels.h levels.cpp levels.ui
    gamesave.h gamesave.cpp
    help.h help.cpp help.ui
    settings.h settings.cpp settings.ui
)

# Основное приложение
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sudoku
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resourses.qrc
    )
else()
    add_executable(Sudoku
        ${PROJECT_SOURCES}
        resourses.qrc
    )
endif()

target_link_libraries(Sudoku PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Настройка тестов
enable_testing()

# Файлы для тестирования (исключаем main.cpp и файлы UI)
set(TEST_SOURCES
    testgamewindow.cpp
    gamewindow.cpp
    gamewindow.h
    sudokugenerator.cpp
    sudokugenerator.h
    gamesave.cpp
    gamesave.h
)

# Создаем отдельный исполняемый файл для тестов
add_executable(TestGameWindow ${TEST_SOURCES})
target_link_libraries(TestGameWindow PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)

# Добавляем тест в CTest
add_test(NAME GameWindowTests COMMAND TestGameWindow)

# Дополнительные настройки для основного приложения
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Sudoku)
endif()

set_target_properties(Sudoku PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Sudoku
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sudoku)
endif()
