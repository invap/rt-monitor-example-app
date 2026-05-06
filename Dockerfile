FROM ubuntu:24.04 AS development-image

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and compilers
RUN apt-get update && apt-get install -y \
    # GCC and C build tools
    build-essential \
    gcc \
    g++ \
    # Clang/LLVM
    clang \
    lldb \
    llvm \
    # Make
    make \
    cmake \
    # Other useful tools
    curl \
    git \
    vim \
    nano \
    gdb \
    valgrind \
    pkg-config \
    autoconf \
    automake \
    libtool \
    ca-certificates \
    # Clean up to reduce image size
    && rm -rf /var/lib/apt/lists/*

# Install Rust using rustup (as a single RUN command to keep it in the same layer)
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y && \
    echo 'source $HOME/.cargo/env' >> $HOME/.bashrc

# Add Rust to PATH for all subsequent RUN commands
ENV PATH="/root/.cargo/bin:${PATH}"

# Verify installations (in a single RUN to ensure Rust is available)
RUN gcc --version && \
    clang --version && \
    make --version && \
    rustc --version && \
    cargo --version

# Set working directory
WORKDIR .

# Restore environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=
