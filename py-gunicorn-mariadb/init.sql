USE web;

CREATE TABLE answers
(
    id INTEGER AUTO_INCREMENT,
    question_id INTEGER,
    answer TEXT,
    PRIMARY KEY (id)
);