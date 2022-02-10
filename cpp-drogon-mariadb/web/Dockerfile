FROM debian:11-slim AS base


FROM base AS build

ENV DEBIAN_FRONTEND=noninteractive 
RUN apt-get update -y
RUN apt-get install -y git gcc g++ cmake libjsoncpp-dev uuid-dev libssl-dev zlib1g-dev
#RUN apt-get install -y postgresql-all libmariadb-dev libsqlite3-dev
RUN apt-get install -y libmariadb-dev
RUN rm -rf /var/lib/apt/lists/*

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

RUN DEBIAN_FRONTEND=noninteractive apt-get update -y \
    && apt-get install -y libjsoncpp24 uuid libssl1.1 zlib1g libmariadb3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build .

EXPOSE 8080

CMD ["./app"]
