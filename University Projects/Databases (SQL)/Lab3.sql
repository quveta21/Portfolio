USE Lab1;

CREATE TABLE Versiuni  
(cod_v INT PRIMARY KEY IDENTITY,
versiune_curenta INT
);
INSERT INTO Versiuni (versiune_curenta) VALUES (0);

-------------------------------------------------------------------------------------

-- modifica tipul unei coloane
ALTER PROCEDURE ModificaTipRating
AS
BEGIN
-- nu putem modifica tipul coloanei daca are o constrangere
ALTER TABLE Rating
DROP CONSTRAINT ck_valoare;
ALTER TABLE Rating
ALTER COLUMN valoare DECIMAL(2,1);
--refacem constrangerea
ALTER TABLE Rating
ADD CONSTRAINT ck_valoare CHECK (valoare >= 1 AND valoare <= 5);
UPDATE Versiuni SET versiune_curenta = 1;
END;

ALTER PROCEDURE RevenireTipRating
AS
BEGIN
ALTER TABLE Rating
DROP CONSTRAINT ck_valoare;
ALTER TABLE Rating
ALTER COLUMN valoare INT;
ALTER TABLE Rating
ADD CONSTRAINT ck_valoare CHECK (valoare >= 1 AND valoare <= 5);
UPDATE Versiuni SET versiune_curenta = 0;
END;

EXEC ModificaTipRating;
EXEC RevenireTipRating;

-------------------------------------------------------------------------------------

CREATE PROCEDURE AdaugaConstrangereDefault
AS
BEGIN
ALTER TABLE Players
ADD CONSTRAINT df_nume_display DEFAULT 'Anonim' FOR nume_display;
UPDATE Versiuni SET versiune_curenta = 2;
END;

CREATE PROCEDURE StergeConstrangereDefault
AS
BEGIN
ALTER TABLE Players
DROP CONSTRAINT df_nume_display;
UPDATE Versiuni SET versiune_curenta = 1;
END;

EXEC AdaugaConstrangereDefault;
EXEC StergeConstrangereDefault;

-------------------------------------------------------------------------------------

CREATE PROCEDURE CreazaTabelDificultate
AS
BEGIN
CREATE TABLE Dificultate
(id_d INT PRIMARY KEY IDENTITY
);
UPDATE Versiuni SET versiune_curenta = 3;
END;

CREATE PROCEDURE StergeTabelDificultate
AS
BEGIN
DROP TABLE Dificultate;
UPDATE Versiuni SET versiune_curenta = 2;
END;

EXEC CreazaTabelDificultate;
EXEC StergeTabelDificultate;

-------------------------------------------------------------------------------------

ALTER PROCEDURE AdaugaCampDificultate
AS
BEGIN
ALTER TABLE Dificultate ADD diff VARCHAR(50);
-- adaugam si un constraint pentru a asigura integritatea datelor
-- folosim exec pentru a crea campul inaintea adaugarii constrangerii
EXEC('ALTER TABLE Dificultate
ADD CONSTRAINT ck_diff CHECK(diff IN (''hard'', ''normal'', ''easy''))');
UPDATE Versiuni SET versiune_curenta = 4;
END;

ALTER PROCEDURE StergeCampDificultate
AS
BEGIN
ALTER TABLE Dificultate
DROP CONSTRAINT ck_diff;
ALTER TABLE Dificultate
DROP COLUMN diff;
UPDATE Versiuni SET versiune_curenta = 3;
END;

EXEC AdaugaCampDificultate;
EXEC StergeCampDificultate;

-------------------------------------------------------------------------------------

CREATE PROCEDURE CreazaCheieStraina
AS
BEGIN
ALTER TABLE Minigames
ADD id_d INT
EXEC('ALTER TABLE Minigames
ADD CONSTRAINT fk_Dificultate FOREIGN KEY (id_d) REFERENCES Dificultate(id_d);');
UPDATE Versiuni SET versiune_curenta = 5;
END;

CREATE PROCEDURE StergeCheieStraina
AS
BEGIN
ALTER TABLE Minigames
DROP CONSTRAINT fk_Dificultate;
ALTER TABLE Minigames
DROP COLUMN id_d;
UPDATE Versiuni SET versiune_curenta = 4;
END;

EXEC CreazaCheieStraina;
EXEC StergeCheieStraina;

-------------------------------------------------------------------------------------

CREATE PROCEDURE Version0to1
AS BEGIN EXEC ModificaTipRating; END;

CREATE PROCEDURE Version1to0
AS BEGIN EXEC RevenireTipRating; END;

CREATE PROCEDURE Version1to2
AS BEGIN EXEC AdaugaConstrangereDefault; END;

CREATE PROCEDURE Version2to1
AS BEGIN EXEC StergeConstrangereDefault; END;

CREATE PROCEDURE Version2to3
AS BEGIN EXEC CreazaTabelDificultate; END;

CREATE PROCEDURE Version3to2
AS BEGIN EXEC StergeTabelDificultate; END;

CREATE PROCEDURE Version3to4
AS BEGIN EXEC AdaugaCampDificultate; END;

CREATE PROCEDURE Version4to3
AS BEGIN EXEC StergeCampDificultate; END;

CREATE PROCEDURE Version4to5
AS BEGIN EXEC CreazaCheieStraina; END;

CREATE PROCEDURE Version5to4
AS BEGIN EXEC StergeCheieStraina; END;

-------------------------------------------------------------------------------------

ALTER PROCEDURE SetVersiune @versiune_target INT
AS
BEGIN

IF(@versiune_target < 0 OR @versiune_target > 5)
BEGIN
	RAISERROR('Versiunea nu exista!', 16, 1);
	RETURN;
END;

DECLARE @versiune_curenta INT;
DECLARE @sql VARCHAR(255);
SELECT @versiune_curenta = versiune_curenta FROM Versiuni

IF(@versiune_target > @versiune_curenta)
BEGIN
	WHILE(@versiune_curenta < @versiune_target)
	BEGIN
		SET @versiune_curenta = @versiune_curenta + 1;
		SET @sql = 'EXEC Version' + CAST(@versiune_curenta-1 AS VARCHAR) + 'to' + CAST(@versiune_curenta AS VARCHAR);
		EXEC(@sql);
	END
END
ELSE IF (@versiune_target < @versiune_curenta)
BEGIN
	WHILE(@versiune_curenta > @versiune_target)
	BEGIN
		SET @sql = 'EXEC Version' + CAST(@versiune_curenta AS VARCHAR) + 'to' + CAST(@versiune_curenta-1 AS VARCHAR);
		EXEC(@sql);
		SET @versiune_curenta = @versiune_curenta - 1;
	END
END
END;

EXEC SetVersiune 5;
SELECT * FROM Versiuni;