# C++ Development Environment with WSL, Docker and VS Code

This repository demonstrates a modern C++ development setup based on:

- WSL2 (Ubuntu)
- Docker Desktop
- Visual Studio Code
- Dev Containers
- CMake
- GCC/G++
- Conan

The entire toolchain is defined inside a Docker container to ensure a reproducible development environment across all machines.

---

# Prerequisites

Before using this repository, make sure the following software is installed on your Windows machine:

- Windows 11 (or Windows 10 with WSL2 support)
- Docker Desktop
- Visual Studio Code

---

# 1. Install and Configure WSL

Open PowerShell as Administrator and install WSL:

```powershell
wsl --install
```

Restart your computer if requested.

Verify the installation:

```powershell
wsl --status
```

Install Ubuntu if it is not already present:

```powershell
wsl --install -d Ubuntu
```

List installed distributions:

```powershell
wsl -l -v
```

Expected output:

```text
NAME              STATE           VERSION
* Ubuntu          Running         2
```

---

# 2. Install and Configure Docker Desktop

Download and install Docker Desktop:

https://www.docker.com/products/docker-desktop/

During installation ensure:

```text
Use WSL 2 based engine
```

is enabled.

After installation:

```text
Docker Desktop
→ Settings
→ Resources
→ WSL Integration
```

Enable integration for your Ubuntu distribution.

Verify Docker from an Ubuntu terminal:

```bash
docker --version
```

Expected output:

```text
Docker version ...
```

---

# 3. Install and Configure VS Code

Download Visual Studio Code:

https://code.visualstudio.com/

Install the following extensions:

### Required

- Remote - WSL
- Dev Containers
- C/C++
- CMake Tools

### Recommended

- clangd
- Docker
- GitLens

---

# 4. Clone the Repository

Open an Ubuntu terminal.

Create a workspace:

```bash
mkdir -p ~/projects
cd ~/projects
```

Clone the repository:

```bash
git clone <repository-url>
cd <repository-name>
```

Open the project in VS Code:

```bash
code .
```

Verify that VS Code is connected to WSL:

```text
WSL: Ubuntu
```

should appear in the lower-left corner.

---

# 5. Build the Development Container

Inside VS Code:

```text
Ctrl + Shift + P
```

Run:

```text
Dev Containers: Rebuild and Reopen in Container
```

VS Code will:

1. Build the Docker image
2. Start the development container
3. Reopen the workspace inside the container

When finished, the lower-left corner should display:

```text
Dev Container
```

---

# 6. Verify Tool Installation

Open a terminal inside VS Code and execute:

```bash
g++ --version
cmake --version
conan --version
```

All commands should return a version number.

---

# 7. Build the Project

Configure CMake:

```bash
cmake -B build -S .
```

Build:

```bash
cmake --build build
```

Expected output:

```text
[100%] Built target my_app
```

---

# 8. Run the Application

Execute:

```bash
./build/my_app
```

Expected output:

```text
Hello Dev Container!
```