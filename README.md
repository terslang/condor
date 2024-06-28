# condor
Condorcet Voting Engine

## First Time Setup
run sql/condordb.sql and create a sqlite3 db in db/condordb
```bash
sqlite3 db/condordb < sql/condordb.sql
```

## Building and Running
```bash
cd condor
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cd build 
make -j$(nproc)
cd ..
treefrog -e dev
```

Navigate to localhost:8800/Election
or localhost:8800/Ballot after creating an election and adding some options


