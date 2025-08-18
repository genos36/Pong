FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    libsfml-dev \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Copy ALL files (except those in .dockerignore)
WORKDIR /app
COPY . .

# Build
RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make
# Run
CMD ["./Pong"]