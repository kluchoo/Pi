# Używamy uniwersalnego obrazu deweloperskiego od Microsoft jako obrazu bazowego
FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu


# Copy the setup scripts to the container
COPY setup-*.sh /usr/local/bin/
ENV DEBIAN_FRONTEND=noninteractive \
    PYTHONUNBUFFERED=1 \
    PIP_NO_CACHE_DIR=1
RUN set -ex && \
    apt-get update && \
    apt-get install -y --no-install-recommends nala && \
    nala install -y --no-install-recommends curl apt-transport-https ca-certificates && \
    curl -sSL https://raw.githubusercontent.com/vegardit/fast-apt-mirror.sh/v1/fast-apt-mirror.sh -o /usr/local/bin/fast-apt-mirror.sh && \
    chmod 755 /usr/local/bin/fast-apt-mirror.sh && \
    /usr/local/bin/fast-apt-mirror.sh find --apply && \
    # Install main packages and configure Python
    nala update && \
    nala install -y --no-install-recommends \
    python3 \
    python3-pip \
    mingw-w64 \
    g++ \
    cmake \
    make \
    git \
    gdb \
    ghostscript \
    graphviz && \
    # Set permissions and run setup-doxygen script
    chmod 777 /usr/local/bin/setup-doxygen.sh && \
    /usr/local/bin/setup-doxygen.sh && \
    # Configure and run setup-bash script
    chmod +x /usr/local/bin/setup-bash.sh && \
    /usr/local/bin/setup-bash.sh && \
    rm /usr/local/bin/setup-*.sh && \
    # Install Python packages
    pip install --no-cache-dir uv ruff && \
    # Clean up
    apt-get clean && \
    apt-get autoremove -y && \
    rm -rf \
    /var/lib/apt/lists/* \
    /tmp/* \
    /var/tmp/* \
    /usr/share/doc/* \
    /usr/share/man/* \
    /var/log/* \
    /var/cache/apt/* \
    ~/.cache/pip/*