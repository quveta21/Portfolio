USE Lab1;

CREATE TABLE Legaturi_Eliminate(
	cod_l INT PRIMARY KEY IDENTITY,
	NumeTabelSt VARCHAR(50),
	idSt INT,
	NumeTabelDr VARCHAR(50),
	idDr INT
);
---------------------------------------------------------------------------------------

-- Minigames M:N Categorii => 1:N (un minigame are o categorie, o categorie apartine mai multor minigame-uri)
CREATE TRIGGER EliminareMinigamesCategorii
ON MinigamesCategorii
AFTER DELETE
AS
BEGIN
INSERT INTO Legaturi_Eliminate (NumeTabelSt, idSt, NumeTabelDr, idDr)
SELECT 
'Minigames' AS NumeTabelSt, 
id_m AS idSt, 
'Categorii' as NumeTabelDr, 
id_c AS idDr 
FROM deleted;
END;
---------------------------------------------------------------------------------------
ALTER TABLE Minigames
ADD id_c INT;

DECLARE @id_m INT, @id_c INT;
DECLARE cur CURSOR FOR SELECT id_m, id_c FROM MinigamesCategorii;

OPEN cur;
FETCH NEXT FROM cur INTO @id_m, @id_c;

WHILE @@FETCH_STATUS = 0
BEGIN
	UPDATE Minigames SET id_c = @id_c WHERE id_m = @id_m;
	DELETE FROM MinigamesCategorii WHERE id_m = @id_m AND id_c = @id_c;

	FETCH NEXT FROM cur INTO @id_m, @id_c;
END

CLOSE cur;
DEALLOCATE cur;

SELECT * FROM Legaturi_Eliminate;
---------------------------------------------------------------------------------------

-- Minigames 1:N Players (prin JocuriPreferate) => M:N (un player poate avea mai multe jocuri preferate)
SELECT * FROM JocuriPreferate;

ALTER TABLE JocuriPreferate
DROP CONSTRAINT PK_JocuriPreferate_1;

ALTER TABLE JocuriPreferate
ADD CONSTRAINT pk_JocuriPreferate PRIMARY KEY (id_p, id_m);

INSERT INTO JocuriPreferate (id_p, id_m) VALUES
(1, 4), (2, 3), (3, 6), (4, 10), (5, 9), (6, 1), (7, 5), (8, 8), (9, 4), (10, 7);

---------------------------------------------------------------------------------------

-- Accesorii 1:N Achizitii => 1:1 (un accesoriu poate fi achizitionat de un singur cumparator)

CREATE TRIGGER EliminareAchizitii
ON Achizitii
AFTER DELETE
AS
BEGIN
    INSERT INTO Legaturi_Eliminate (NumeTabelSt, idSt, NumeTabelDr, idDr)
    SELECT
        'Accesorii', id_a,
        'Players', id_p
    FROM deleted
END;

-- inseram date pentru a fi vizibila schimbarea in Legaturi_Eliminate

INSERT INTO Achizitii (id_a, id_p, pret, data_achizitiei) VALUES
(1, 3, 100, '2025-07-10'),
(3, 4, 150, '2025-10-04'),
(7, 5, 700, '2025-03-21'),
(9, 1, 180, '2025-05-05'),
(2, 9, 50, '2025-01-01'),
(6, 8, 200, '2025-07-30'),
(10, 2, 1500, '2025-10-16'),
(4, 5, 70, '2025-09-29'),
(8, 7, 10, '2025-02-08'),
(5, 6, 500, '2025-09-09');

-- pastram doar cate o achizitie cu fiecare id_a pastrand id_p cel mai mare

DELETE A
FROM Achizitii A
WHERE A.id_p <> (
    SELECT MAX(A2.id_p)
    FROM Achizitii A2
    WHERE A2.id_a = A.id_a
);

ALTER TABLE Achizitii
DROP CONSTRAINT pk_Achizitii;

ALTER TABLE Achizitii
ADD CONSTRAINT pk_Achizitii PRIMARY KEY (id_a);

SELECT * FROM Legaturi_Eliminate;

---------------------------------------------------------------------------------------

-- Players 1:N Rating => N:1 (mai multi playeri pot face referire la un rating)

ALTER TABLE Players
ADD id_m INT NULL;
-- adaugam FK catre Minigames in tabela Players
ALTER TABLE Players
ADD CONSTRAINT fk_Players_Minigames
FOREIGN KEY (id_m) REFERENCES Minigames(id_m);

-- adaugam inca 10 inregistrari in tabela rating
INSERT INTO Rating (id_p, id_m, valoare) VALUES
(10, 3, 4),
(2, 4, 3),
(3, 5, 5),
(7, 6, 2),
(9, 1, 4),
(1, 6, 5),
(8, 8, 2),
(4, 10, 5),
(3, 1, 1),
(6, 2, 2),
(2, 8, 5);

-- setam id_m pentru fiecare player in functie de valoarea din Rating
UPDATE P
SET id_m = R.id_m
FROM Players P
INNER JOIN (
    -- luam doar inregistrarea cu id_m maxim pentru fiecare player
    SELECT id_p, MAX(id_m) AS id_m
    FROM Rating
    GROUP BY id_p
) R ON P.id_p = R.id_p;

-- trigger pentru eliminarea duplicatelor (id_m) din Rating
CREATE TRIGGER EliminareRating
ON Rating
AFTER DELETE
AS
BEGIN
    INSERT INTO Legaturi_Eliminate (NumeTabelSt, idSt, NumeTabelDr, idDr)
    SELECT
        'Players',
        D.id_p,
        'Rating',
        D.id_m
    FROM deleted D;
END;


-- pastram doar id_m cu id_p cel mai mare
DELETE R
FROM Rating R
WHERE R.id_p <> (
    SELECT MAX(R2.id_p)
    FROM Rating R2
    WHERE R2.id_m = R.id_m
);

-- stergem coloana id_p din Rating
ALTER TABLE Rating DROP CONSTRAINT pk_Rating;
ALTER TABLE Rating DROP CONSTRAINT fk_PlayersRating;
ALTER TABLE Rating DROP COLUMN id_p;

-- setam PK doar pe id_m
ALTER TABLE Rating
ADD CONSTRAINT pk_Rating PRIMARY KEY (id_m);


SELECT * FROM Legaturi_Eliminate;
