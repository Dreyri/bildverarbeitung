set(SRC
  main.cpp
)

add_executable(aufgabe1 ${SRC})
target_include_directories(aufgabe1 PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(aufgabe1 ${OpenCV_LIBS})
