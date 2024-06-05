cmake_minimum_required(VERSION 3.0.2)
project(wwpcamera)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package()

# Inclua os diretórios de cabeçalho do projeto e do SDK
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  /home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers
)

# Adicione o diretório onde a biblioteca está localizada
link_directories(
  /home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/lib-linux
)

# Defina o executável
add_executable(main_node src/main.cpp src/backend.cpp)

# Linke a biblioteca ao executável
target_link_libraries(main_node
  ${catkin_LIBRARIES}
  libwwp-data-sdk.a
)
