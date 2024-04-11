FROM fedora:39 AS build
RUN dnf install -y git make cmake g++ SDL2 SDL2-devel boost-devel
COPY . /gb-emu
RUN mkdir gb-emu/build \
      && cd gb-emu/build \
      && cmake .. \
      && make

FROM fedora:39
# SDL2-devel brings in 500MB of dependencies. Maybe only a specific package from it is required?
RUN dnf install -y boost SDL SDL2-devel
ENTRYPOINT ["/usr/bin/gbemu"]
COPY --from=build /gb-emu/build/gbemu /usr/bin/gbemu
