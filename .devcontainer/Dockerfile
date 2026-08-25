FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04


RUN apt-get update && \
    apt-get install -y \
    python3-pip \
    libgl1-mesa-dev \
    libx11-dev \
    libxcursor-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxi-dev \
    libxext-dev \
    libxfixes-dev \
    libwayland-dev \
    libxkbcommon-dev \
    libasound2-dev \
    libx11-xcb-dev \
    libfontenc-dev \
    libice-dev \
    libsm-dev \
    libxaw7-dev \
    libxcomposite-dev \
    libxdamage-dev \
    libxkbfile-dev \
    libxmu-dev \
    libxmuu-dev \
    libxpm-dev \
    libxres-dev \
    libxss-dev \
    libxt-dev \
    libxtst-dev \
    libxv-dev \
    libxxf86vm-dev \
    libxcb-glx0-dev \
    libxcb-render0-dev \
    libxcb-render-util0-dev \
    libxcb-xkb-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-randr0-dev \
    libxcb-shape0-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb-xinerama0-dev \
    libxcb-dri3-dev \
    uuid-dev \
    libxcb-cursor-dev \
    libxcb-dri2-0-dev \
    libxcb-present-dev \
    libxcb-composite0-dev \
    libxcb-ewmh-dev \
    libxcb-res0-dev \
    libxcb-util-dev && \
    rm -rf /var/lib/apt/lists/*

# Conan installieren
RUN python3 -m pip install --no-cache-dir --break-system-packages conan==2.31.2

# Versionscheck beim Build
RUN gcc --version && \
    g++ --version && \
    cmake --version && \
    conan --version