# condor
Condorcet Voting Engine

## First Time Setup
run sql/condordb.sql and create a sqlite3 db in db/condordb

## Building and Running
```bash
cd condor
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cd build 
make -j$(nproc)
cd ..
treefrog -e dev
```

Navigate to localhost:8800/<view-name>
