FROM debian:11-slim AS base

RUN DEBIAN_FRONTEND=noninteractive apt update -y \
    && apt-get install -y git gcc g++ cmake libjsoncpp-dev uuid-dev libssl-dev zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*
RUN DEBIAN_FRONTEND=noninteractive apt update -y \
    && apt-get install -y postgresql-all \
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
#RUN (cd controllers && drogon_ctl create controller -r Answer)
WORKDIR /app/build
#RUN cmake -DCMAKE_BUILD_TYPE=Release .. 
RUN cmake ..
RUN make


FROM base AS final

WORKDIR /app
COPY --from=build /app/build .
RUN echo '#!/bin/sh\n\
# wait-for-postgres.sh\n\
\n\
set -e\n\
\n\
host="$1"\n\
shift\n\
\n\
until PGPASSWORD=password psql -h "$host" -U "web" -c "\\q"; do\n\
  >&2 echo "Postgres is unavailable - sleeping"\n\
  sleep 1\n\
done\n\
\n\
>&2 echo "Postgres is up - executing command"\n\
exec "$@"\n'\
>> ./wait-for-postgres.sh
RUN chmod +x ./wait-for-postgres.sh

EXPOSE 8080

CMD ["./wait-for-postgres.sh", "db", "./app"]
