CREATE DATABASE IF NOT EXISTS games_db_benchmark;
USE games_db_benchmark;

DROP TABLE points_a;
DROP TABLE points_b;
DROP TABLE points_c;
DROP TABLE players;

SELECT * FROM players;
SELECT * FROM points_a;
SELECT * FROM points_b;
SELECT * FROM points_c;

select * from information_schema.INNODB_TRX;
