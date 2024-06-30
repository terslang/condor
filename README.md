# condor
Condorcet Voting Engine


## First Time Setup
run sql/condordb.sql and create a sqlite3 db in db/condordb
```bash
sqlite3 db/condordb < sql/condordb.sql
```

add some users to the database like:
```bash
sqlite3 db/condordb
> INSERT INTO user(email, password) VALUES ('admin@example.org', '482c811da5d5b4bc6d497ffa98491e38');
```

`password` is a simple md5 hashed password. It can be generated using the following command (Here "password123" is used as an example):

```bash
echo -n "password123" | md5sum
```


## Building and Running
```bash
cd condor
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -C build -j$(nproc)
cd ..
treefrog -e dev
```

Navigate to localhost:8800/Election
or localhost:8800/Ballot after creating an election and adding some options

## Screenshots

![image](https://github.com/terslang/condor/assets/127589779/e74e4a00-fea5-41e9-9100-33a8f1433583)

![condor-screenshot](https://github.com/terslang/condor/assets/127589779/f9791917-2cd5-4584-a933-0a01db59671f)

## Database Design

![condor](https://github.com/terslang/condor/assets/127589779/fffe32de-1f8d-4451-bf46-ca83926504f3)
