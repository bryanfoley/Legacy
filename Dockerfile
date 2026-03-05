# Use a minimal Debian-based image with GCC and Make available
FROM debian:bookworm-slim

# Install build tools (gcc, make) and the C math library
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        gcc \
        make \
        libc6-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy all source files into the container
COPY Compress.c ./
COPY makefile ./
COPY config1.dat ./
COPY incl/ ./incl/
COPY intf/ ./intf/
COPY src/ ./src/
COPY results/ ./results/

# Build the simulation
RUN make

# Run the simulation by default
CMD ["./Compress"]
