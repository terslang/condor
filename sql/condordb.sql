PRAGMA foreign_keys = ON;

CREATE TABLE election (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    name VARCHAR(255) NOT NULL,
    body TEXT NOT NULL,
    quorum INTEGER NOT NULL,
    polling_open TIMESTAMP,
    polling_close TIMESTAMP,
    result_id INTEGER REFERENCES result(id) ON DELETE RESTRICT
);

CREATE TABLE option (
    id TEXT PRIMARY KEY NOT NULL, 
    name VARCHAR(255) NOT NULL,
    body TEXT NOT NULL,
    election_id INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election (id) ON DELETE CASCADE
);

CREATE TABLE result (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    election_id INTEGER NOT NULL,
    option_id TEXT,
    FOREIGN KEY (election_id) REFERENCES election(id) ON DELETE CASCADE,
    FOREIGN KEY (option_id) REFERENCES option(id) ON DELETE CASCADE
);

CREATE TABLE ballot (
    id TEXT PRIMARY KEY NOT NULL,
    election_id INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id) ON DELETE CASCADE
);

CREATE TABLE voter (
    id TEXT PRIMARY KEY NOT NULL,
    election_id INTEGER NOT NULL,
    email VARCHAR(255) NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id) ON DELETE CASCADE
);

CREATE TABLE pairwise_contest (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    election_id INTEGER NOT NULL,
    option_a_id TEXT NOT NULL,
    option_b_id TEXT NOT NULL,
    option_a_count INTEGER NOT NULL,
    option_b_count INTEGER NOT NULL,
    FOREIGN KEY (election_id) REFERENCES election(id) ON DELETE CASCADE,
    FOREIGN KEY (option_a_id) REFERENCES option(id) ON DELETE CASCADE,
    FOREIGN KEY (option_b_id) REFERENCES option(id) ON DELETE CASCADE
);

CREATE TABLE ballot_choice (
    ballot_id TEXT NOT NULL,
    option_id TEXT NOT NULL,
    rank INTEGER NOT NULL,
    PRIMARY KEY (ballot_id, option_id),
    FOREIGN KEY (ballot_id) REFERENCES ballot(id) ON DELETE CASCADE,
    FOREIGN KEY (option_id) REFERENCES option(id) ON DELETE CASCADE
);
