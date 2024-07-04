cmake_minimum_required(VERSION 3.0.2)
project(wwpcamera)

## Adicione esta linha para usar o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir o compilador GCC 11
set(CMAKE_C_COMPILER /usr/bin/gcc-11)
set(CMAKE_CXX_COMPILER /usr/bin/g++-11)

# Encontrar pacotes necessários
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

find_package(Threads REQUIRED)

# Definir o pacote catkin
catkin_package()

# Incluir diretórios
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  /home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/include
)

# Adicionar diretório de linkagem para a biblioteca personalizada
link_directories(/home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/lib)

# Adicionar executável
add_executable(main_node main.cpp backend.cpp)

# Linkar bibliotecas ao executável
target_link_libraries(main_node
  ${catkin_LIBRARIES}
  /home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/lib/libinternal.a
  /home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/lib/libcore.a
  /home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/lib/libsources.so
  ${CMAKE_THREAD_LIBS_INIT}
  pthread
  stdc++
)
