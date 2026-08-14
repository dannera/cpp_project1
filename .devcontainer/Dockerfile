FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04


RUN apt-get update && \
    apt-get install -y python3-pip

# Conan installieren
RUN python3 -m pip install --no-cache-dir --break-system-packages conan==2.31.2

# Versionscheck beim Build
RUN gcc --version && \
    g++ --version && \
    cmake --version && \
    conan --version
