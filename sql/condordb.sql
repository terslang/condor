PRAGMA foreign_keys = ON;

CREATE TABLE election (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    name VARCHAR(255) NOT NULL,
    body TEXT NOT NULL,
    quorum INTEGER NOT NULL,
    polling_open TIMESTAMP,
    polling_close TIMESTAMP,
    result_id INTEGER REFERENCES result(id)
);

CREATE TABLE option (
    id TEXT PRIMARY KEY NOT NULL ON CONFLICT REPLACE DEFAULT (hex(randomblob(4))), 
    name VARCHAR(255) NOT NULL,
    body TEXT NOT NULL,
    election_id INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election (id)
);

CREATE TABLE result (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    election_id INTEGER NOT NULL,
    option_id TEXT,
    FOREIGN KEY (election_id) REFERENCES election(id),
    FOREIGN KEY (option_id) REFERENCES option(id)
);

CREATE TABLE ballot (
    id TEXT PRIMARY KEY NOT NULL ON CONFLICT REPLACE DEFAULT (hex(randomblob(4))),
    election_id INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id)
);

CREATE TABLE voter (
    id TEXT PRIMARY KEY NOT NULL ON CONFLICT REPLACE DEFAULT (hex(randomblob(4))),
    election_id INTEGER NOT NULL,
    email VARCHAR(255) NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id)
);

CREATE TABLE pairwise_contest (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    election_id INTEGER NOT NULL,
    option_a_id TEXT NOT NULL,
    option_b_id TEXT NOT NULL,
    option_a_count INTEGER NOT NULL,
    option_b_count INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id),
    FOREIGN KEY (option_a_id) REFERENCES option(id),
    FOREIGN KEY (option_b_id) REFERENCES option(id)
);

CREATE TABLE ballot_choice (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    ballot_id TEXT NOT NULL,
    option_id TEXT NOT NULL,
    rank INTEGER NOT NULL,
    FOREIGN KEY (ballot_id) REFERENCES ballot(id),
    FOREIGN KEY (option_id) REFERENCES option(id)
);
