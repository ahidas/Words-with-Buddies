DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS boards;


CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user TEXT NOT NULL,
    pass TEXT NOT NULL
);

CREATE TABLE boards (
    id INTEGER NOT NULL,
    board_name TEXT NOT NULL,
    vals TEXT NOT NULL
);

