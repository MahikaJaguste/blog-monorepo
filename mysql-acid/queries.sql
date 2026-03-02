CREATE DATABASE IF NOT EXISTS games_db;
USE games_db;

DROP TABLE game_points;
DROP TABLE players;

CREATE TABLE IF NOT EXISTS players (
    id INT PRIMARY KEY,
	name VARCHAR(50),
	badge VARCHAR(20),
	last_updated TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO players (id, name, badge) VALUES
(1, 'Alice', 'gold'),
(2, 'Bob', 'silver'),
(3, 'Charlie', 'regular');
-- (4, 'Diana', 'regular'),
-- (5, 'Eve', 'regular');

CREATE TABLE IF NOT EXISTS game_points (
	game_id INT,
	player_id INT,
	points INT,
	last_updated TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    -- id INT AUTO_INCREMENT PRIMARY KEY,
	PRIMARY KEY (player_id, game_id),
    FOREIGN KEY (player_id) REFERENCES players(id)
);

INSERT INTO game_points (game_id, player_id, points) VALUES
(1, 1, 150),
(1, 2, 100),
(1, 3, 50),
(2, 1, 100),
(2, 3, 50);
-- (3, 4, 25),
-- (3, 2, 50),
-- (4, 4, 10),
-- (4, 5, 10),
-- (5, 1, 30),
-- (5, 5, 20);

SELECT * FROM players;
SELECT * FROM game_points;

SHOW INDEX FROM players;
SHOW INDEX FROM game_points;

select trx_id, trx_state, trx_started, trx_mysql_thread_id, trx_tables_locked, trx_rows_locked, trx_isolation_level FROM information_schema.INNODB_TRX;
select * from information_schema.INNODB_TRX;


select * FROM performance_schema.data_lock_waits;
select * from performance_schema.data_locks where ENGINE_LOCK_ID='5577251832:24:830:4:1:5444409880';

select ENGINE_TRANSACTION_ID, THREAD_ID, OBJECT_SCHEMA, OBJECT_NAME, INDEX_NAME, LOCK_TYPE, LOCK_MODE, LOCK_STATUS, LOCK_DATA FROM performance_schema.data_locks;

CREATE UNIQUE INDEX idx_tuple ON game_points(player_id,game_id);