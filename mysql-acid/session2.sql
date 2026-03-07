use games_db;

SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- Select for update of points
START TRANSACTION;
SELECT * FROM points
WHERE game_id = 1 AND player_id = 1
FOR UPDATE;
COMMIT;

-- Insert is blocked if other RR transaction is locking select as it places a gap lock (when not using unique primary key in search)
INSERT INTO points (game_id, player_id, points) VALUES
(100, 1, 150);

-- 

-- Get badge distribution
START TRANSACTION;
SELECT COUNT(*) FROM players
WHERE badge = 'gold';

SELECT COUNT(*) FROM players
WHERE badge = 'silver';
COMMIT;




-- 