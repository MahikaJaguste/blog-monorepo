use games_db;

SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Select for update of points
START TRANSACTION;
SELECT * FROM points
WHERE game_id = 1 AND player_id = 1
FOR UPDATE;
COMMIT;

-- Insert is allowed if other RC transaction is locking select
START TRANSACTION;
INSERT INTO points (game_id, player_id, points) VALUES
(100, 1, 150);
COMMIT;

-- 

-- Get badge distribution
START TRANSACTION;
SELECT COUNT(*) FROM players
WHERE badge = 'gold';

SELECT COUNT(*) FROM players
WHERE badge = 'silver';
COMMIT;

---

-- Get player global points and update badge
START TRANSACTION;
SELECT SUM(points) FROM points
WHERE player_id = 1
FOR SHARE;

SELECT SUM(points) FROM points
WHERE player_id = 1;
COMMIT;

-- 