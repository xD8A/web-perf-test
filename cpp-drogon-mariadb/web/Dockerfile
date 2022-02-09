FROM debian:11-slim AS base

RUN DEBIAN_FRONTEND=noninteractive apt update -y \
    && apt-get install -y git gcc g++ cmake libjsoncpp-dev uuid-dev libssl-dev zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*
RUN DEBIAN_FRONTEND=noninteractive apt update -y \
    && apt-get install -y libmariadb-dev \
    && rm -rf /var/lib/apt/lists/*


FROM base AS build

WORKDIR /tmp
RUN git clone https://github.com/an-tao/drogon
WORKDIR /tmp/drogon
RUN git submodule update --init
RUN mkdir build
WORKDIR /tmp/drogon/build
RUN cmake ..
RUN make && make install

WORKDIR /
RUN drogon_ctl create project app
WORKDIR /app
RUN echo 'configure_file(config.json config.json COPYONLY)' >> CMakeLists.txt
COPY . .
#WORKDIR /app/models
#RUN drogon_ctl create model . -f
#WORKDIR /app/controllers
#RUN drogon_ctl create controller -r Answer -f
WORKDIR /app/build
#RUN cmake -DCMAKE_BUILD_TYPE=Release .. 
RUN cmake ..
RUN make


FROM base AS final

WORKDIR /app
COPY --from=build /app/build .

EXPOSE 8080

CMD ["./app"]
