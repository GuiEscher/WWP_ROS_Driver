# Use a imagem base do Ubuntu 22.04 (Jammy)
FROM ubuntu:22.04

# Defina a variável de ambiente para não interativo
ENV DEBIAN_FRONTEND=noninteractive

# Atualiza e instala pacotes essenciais
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    curl \
    gnupg2 \
    lsb-release \
    wget \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Atualiza as CA Certificates
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    ca-certificates \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Adiciona a chave de assinatura do ROS 2 (Humble)
RUN curl -fsSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | gpg --dearmor -o /usr/share/keyrings/ros-archive-keyring.gpg

# Configura o repositório do ROS 2 (Humble) para Ubuntu Jammy (22.04)
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Instala o ROS 2 (Humble) e ferramentas adicionais
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    ros-humble-desktop \
    python3-rosdep \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Inicializa o rosdep
RUN rosdep init && \
    rosdep update

# Configuração do ambiente ROS 2 (Humble)
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

# Copia o código fonte para o diretório de trabalho
WORKDIR /ros2_ws
COPY src/wwpcamera /ros2_ws/src/wwpcamera
COPY lib/WTLIB-0.1-linux64 /ros2_ws/lib/WTLIB-0.1-linux64

# Compilação do projeto
RUN /bin/bash -c "source /opt/ros/humble/setup.bash && \
    cd /ros2_ws && \
    colcon build"

# Comando padrão a ser executado ao iniciar o contêiner
CMD ["bash"]
