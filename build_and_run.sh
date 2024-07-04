#!/bin/bash

# Nome da imagem Docker
IMAGE_NAME=wwpcamera:latest

# Construir a imagem Docker
docker build -t $IMAGE_NAME .

# Executar o contêiner Docker
docker run -it --rm --name wwpcamera_container \
    -v $(pwd):/home/catkin_ws/src/wwpcamera \
    $IMAGE_NAME
