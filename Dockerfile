FROM debian:trixie-slim

RUN apt-get update \
    && apt-get install --no-install-recommends -y wget sqlite3 libsqlite3-dev ca-certificates build-essential pkg-config tzdata coreutils qmake6 qt6-base-dev qt6-base-dev-tools qt6-tools-dev-tools qt6-declarative-dev libqt6sql6-mysql libqt6sql6-psql libqt6sql6-odbc libqt6sql6-sqlite libqt6core6 libqt6qml6 libqt6xml6 libpq5 libodbc2 libmongoc-dev libbson-dev cmake;

RUN wget -c https://github.com/treefrogframework/treefrog-framework/archive/refs/tags/v2.9.0.tar.gz \
    && tar xvzf v2.9.0.tar.gz

RUN cd treefrog-framework-2.9.0/ && ./configure --enable-shared-mongoc \
    && cd src/ && make && make install && cd ../tools/ && make && make install \
    && ldconfig 

RUN rm -rf treefrog-framework-2.9.0 v2.9.0.tar.gz

COPY . /condor/

WORKDIR /condor

RUN mkdir db && sqlite3 db/condordb < sql/condordb.sql

RUN mkdir build && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && make -C build

EXPOSE 8800

CMD [ "treefrog", "-e", "product" ]
