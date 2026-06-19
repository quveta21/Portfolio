USE Lab1;

-- vom lua tabelele Players si Minigames (M:N prin JocuriPreferate)

-- CREATE
--------------------------------------------------------------------------------------------------
CREATE OR ALTER FUNCTION ValidatePlayers(@username VARCHAR(50), @parola VARCHAR(50), @nume_display NVARCHAR(50))
RETURNS BIT AS
BEGIN
	IF(LEN(@username) < 3)	-- username >= 3
		RETURN 0;
	IF(LEN(@parola) < 6)	-- parola >= 6
		RETURN 0;
	IF(LEN(@nume_display) < 4)	-- nume_display >= 4
		RETURN 0;
	RETURN 1;
END;

CREATE OR ALTER PROCEDURE CreatePlayers
	@username VARCHAR(50),
	@parola VARCHAR(50),
	@nume_display NVARCHAR(50)
AS
BEGIN
	BEGIN TRY
		IF EXISTS(SELECT 1 FROM Players WHERE username=@username)		-- username trebuie sa fie unic
		BEGIN
			RAISERROR('Username-ul exista deja!', 16, 1);
			RETURN;
		END

		IF dbo.ValidatePlayers(@username, @parola, @nume_display) = 0
		BEGIN
			RAISERROR('Datele pentru player nu sunt valide!', 16, 1);
			RETURN;
		END

		INSERT INTO Players(username, parola, nume_display, puncte, id_l)
		VALUES (@username, @parola, @nume_display, 0, 1);	-- default puncte 0, level 1

	END TRY
	BEGIN CATCH
		DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
	END CATCH
END;

EXEC CreatePlayers 'userCreat2', 'parolaRandom', 'createdTwo';

SELECT * FROM Players;

--------------------------------------------------------------------------------------------------
CREATE OR ALTER FUNCTION ValidateMinigames(@titlu NVARCHAR(50), @descriere NVARCHAR(200), @puncte_completare INT,
						@rating INT, @dificultate VARCHAR(50), @categorie VARCHAR(50))
RETURNS BIT AS
BEGIN
	IF(LEN(@titlu) < 4)
		RETURN 0;
	IF(LEN(@descriere) < 4)
		RETURN 0;
	IF(@puncte_completare <= 0)
		RETURN 0;
	IF(@rating < 1 OR @rating > 5)
		RETURN 0;
	IF(@dificultate NOT IN ('easy', 'normal', 'hard'))
		RETURN 0;
	IF NOT EXISTS(SELECT 1 FROM Categorii WHERE nume_categorie=@categorie)
		RETURN 0;
	RETURN 1;
END;


CREATE OR ALTER PROCEDURE CreateMinigames 
	@titlu NVARCHAR(50), 
	@descriere NVARCHAR(200), 
	@puncte_completare INT,
	@rating INT, 
	@dificultate VARCHAR(10), 
	@categorie VARCHAR(50)
AS
BEGIN
	BEGIN TRY
		IF(EXISTS(SELECT 1 FROM Minigames WHERE titlu=@titlu))
		BEGIN
			RAISERROR('Titlul exista deja!', 16, 1);
			RETURN;
		END

		IF dbo.ValidateMinigames(@titlu, @descriere, @puncte_completare, @rating, @dificultate, @categorie) = 0
		BEGIN
			RAISERROR('Datele despre minigame nu sunt valide!', 16, 1);
			RETURN;
		END
	
		-- setam manual id_d
		DECLARE @id_dificultate INT;
		IF @dificultate = 'easy'
			SET @id_dificultate = 2;
		IF @dificultate = 'normal'
			SET @id_dificultate = 3;
		IF @dificultate = 'hard'
			SET @id_dificultate = 4;

		-- setam manual id_c
		DECLARE @id_categorie INT;
		SET @id_categorie = (SELECT id_c FROM Categorii WHERE nume_categorie = @categorie);

		INSERT INTO Minigames(titlu, descriere, puncte_completare, rating, id_d, id_c)
		VALUES (@titlu, @descriere, @puncte_completare, @rating, @id_dificultate, @id_categorie);

	END TRY
	BEGIN CATCH
		DECLARE @errormsg NVARCHAR(4000) = ERROR_MESSAGE();
		RAISERROR(@errormsg, 16, 1);
	END CATCH
END;

EXEC CreateMinigames 'Sl', 'palmuiesti oameni si urci turnul', 75, 3, 'easy', 'Kids';

SELECT * FROM Minigames;
--------------------------------------------------------------------------------------------------
-- READ

CREATE OR ALTER FUNCTION ValidateIdPlayers(@id_p INT)
RETURNS BIT AS
BEGIN
	IF NOT EXISTS (SELECT 1 FROM Players WHERE id_p=@id_p)
		RETURN 0;
	RETURN 1;
END;

CREATE OR ALTER PROCEDURE ReadPlayers @id_p INT
AS
BEGIN
	IF dbo.ValidateIdPlayers(@id_p) = 0
	BEGIN
		RAISERROR('Nu s-a gasit player cu acel id!', 16, 1);
		RETURN;
	END

	SELECT username FROM Players WHERE id_p=@id_p;
END;

EXEC ReadPlayers 20;
--------------------------------------------------------------------------------------------------
CREATE OR ALTER FUNCTION ValidateIdMinigames(@id_m INT)
RETURNS BIT AS
BEGIN
	IF NOT EXISTS (SELECT 1 FROM Minigames WHERE id_m=@id_m)
		RETURN 0;
	RETURN 1;
END;


CREATE OR ALTER PROCEDURE ReadMinigames @id_m INT
AS
BEGIN
	IF dbo.ValidateIdMinigames(@id_m) = 0
	BEGIN
		RAISERROR('Nu s-a gasit minigame cu acel id!', 16, 1);
		RETURN;
	END

	SELECT titlu FROM Minigames WHERE id_m=@id_m;
END;

EXEC ReadMinigames 3;
--------------------------------------------------------------------------------------------------
-- crearea tabelelor de logging

CREATE TABLE LoggingPlayers(
	id_log INT PRIMARY KEY IDENTITY,
	id_p INT,
	username VARCHAR(50),
	parola VARCHAR(50),
	nume_display NVARCHAR(50),
	puncte INT,
	id_l INT,
	id_m INT,
	data_si_ora DATETIME,
	login_name VARCHAR(50),
	tip_operatie VARCHAR(10)
);
--------------------------------------------------------------------------------------------------
CREATE TABLE LoggingMinigames(
	id_log INT PRIMARY KEY IDENTITY,
	id_m INT,
	titlu VARCHAR(50),
	descriere VARCHAR(200),
	puncte_completare INT,
	rating INT,
	id_d INT,
	id_c INT,
	data_si_ora DATETIME,
	login_name VARCHAR(50),
	tip_operatie VARCHAR(10)
);

--------------------------------------------------------------------------------------------------
-- TRIGGERE

CREATE OR ALTER TRIGGER UpdatePlayersTrigger ON Players
AFTER UPDATE
AS
BEGIN
	INSERT INTO LoggingPlayers(id_p, username, parola, nume_display, puncte, id_l, id_m, data_si_ora, login_name, tip_operatie)
	SELECT d.id_p, d.username, d.parola, d.nume_display, d.puncte, d.id_l, d.id_m, GETDATE(), SYSTEM_USER, 'update' 
	FROM deleted d;
END;
--------------------------------------------------------------------------------------------------
CREATE OR ALTER TRIGGER DeletePlayersTrigger ON Players
AFTER DELETE
AS
BEGIN
	INSERT INTO LoggingPlayers(id_p, username, parola, nume_display, puncte, id_l, id_m, data_si_ora, login_name, tip_operatie)
	SELECT d.id_p, d.username, d.parola, d.nume_display, d.puncte, d.id_l, d.id_m, GETDATE(), SYSTEM_USER, 'delete' 
	FROM deleted d;
END;
--------------------------------------------------------------------------------------------------
CREATE OR ALTER TRIGGER UpdateMinigamesTrigger ON Minigames
AFTER UPDATE
AS 
BEGIN
	INSERT INTO LoggingMinigames(id_m, titlu, descriere, puncte_completare, rating, id_d, id_c, data_si_ora, login_name, tip_operatie)
	SELECT d.id_m, d.titlu, d.descriere, d.puncte_completare, d.rating, d.id_d, d.id_c, GETDATE(), SYSTEM_USER, 'update'
	FROM deleted d;
END;
--------------------------------------------------------------------------------------------------
CREATE OR ALTER TRIGGER DeleteMinigamesTrigger ON Minigames
AFTER DELETE
AS 
BEGIN
	INSERT INTO LoggingMinigames(id_m, titlu, descriere, puncte_completare, rating, id_d, id_c, data_si_ora, login_name, tip_operatie)
	SELECT d.id_m, d.titlu, d.descriere, d.puncte_completare, d.rating, d.id_d, d.id_c, GETDATE(), SYSTEM_USER, 'delete'
	FROM deleted d;
END;
--------------------------------------------------------------------------------------------------
-- UPDATE

CREATE OR ALTER PROCEDURE UpdatePlayers
	@id_p INT,
	@username VARCHAR(50),
	@parola VARCHAR(50),
	@nume_display NVARCHAR(50)
AS
BEGIN
	BEGIN TRY
		IF dbo.ValidateIdPlayers(@id_p) = 0
		BEGIN
			RAISERROR('Nu exista player cu id-ul specificat!', 16, 1);
			RETURN;
		END

		DECLARE @oldUsername VARCHAR(50);
		DECLARE @oldParola VARCHAR(50);
		DECLARE @oldNumeDisplay NVARCHAR(50);

		-- retinem vechile valori
		SELECT @oldUsername = username, @oldParola = parola, @oldNumeDisplay = nume_display
		FROM Players
		WHERE id_p = @id_p;

		DECLARE @newUsername VARCHAR(50) = ISNULL(@username, @oldUsername);
		DECLARE @newParola VARCHAR(50) = ISNULL(@parola, @oldParola);
		DECLARE @newNumeDisplay NVARCHAR(50) = ISNULL(@nume_display, @oldNumeDisplay);

		IF dbo.ValidatePlayers(@newUsername, @newParola, @newNumeDisplay) = 0
		BEGIN
			RAISERROR('Datele noi pentru player nu sunt valide!', 16, 1);
			RETURN;
		END

		UPDATE Players
		SET	username = @newUsername, parola = @newParola, nume_display = @newNumeDisplay
		WHERE id_p = @id_p;
	END TRY
	BEGIN CATCH
		DECLARE @errorMsg NVARCHAR(4000) = ERROR_MESSAGE();
		RAISERROR(@errorMsg, 16, 1);
	END CATCH
END;


EXEC UpdatePlayers 10, 'marius', NULL, NULL;

SELECT * FROM Players;
SELECT * FROM LoggingPlayers;
--------------------------------------------------------------------------------------------------
CREATE OR ALTER PROCEDURE UpdateMinigames
	@id_m INT,
	@titlu NVARCHAR(50),
	@descriere NVARCHAR(200),
	@puncte_completare INT,
	@rating INT,
	@dificultate VARCHAR(10),
	@categorie VARCHAR(50)
AS
BEGIN
	BEGIN TRY
		IF dbo.ValidateIdMinigames(@id_m) = 0
		BEGIN
			RAISERROR('Nu exista minigame cu id-ul specificat!', 16, 1);
			RETURN;
		END

		DECLARE @oldTitlu NVARCHAR(50);
		DECLARE @oldDescriere NVARCHAR(200);
		DECLARE @oldPuncteCompletare INT;
		DECLARE @oldRating INT;
		DECLARE @oldDificultateId INT;
		DECLARE @oldCategorieId INT;

		-- retinem vechile valori
		SELECT @oldTitlu = titlu, @oldDescriere = descriere, @oldPuncteCompletare = puncte_completare,
			   @oldRating = rating, @oldDificultateId = id_d, @oldCategorieId = id_c
		FROM Minigames
		WHERE id_m = @id_m;

		DECLARE @newTitlu NVARCHAR(50) = ISNULL(@titlu, @oldTitlu);
		DECLARE @newDescriere NVARCHAR(200) = ISNULL(@descriere, @oldDescriere);
		DECLARE @newPuncteCompletare INT = ISNULL(@puncte_completare, @oldPuncteCompletare);
		DECLARE @newRating INT = ISNULL(@rating, @oldRating);

		DECLARE @oldDificultateNume VARCHAR(50);
		SELECT @oldDificultateNume = diff FROM Dificultate WHERE id_d = @oldDificultateId;
		DECLARE @newDificultateNume VARCHAR(50) = ISNULL(@dificultate, @oldDificultateNume);

		DECLARE @oldCategorieNume VARCHAR(50);
		SELECT @oldCategorieNume = nume_categorie FROM Categorii WHERE id_c = @oldCategorieId;
		DECLARE @newCategorieNume VARCHAR(50) = ISNULL(@categorie, @oldCategorieNume);

		IF dbo.ValidateMinigames(@newTitlu, @newDescriere, @newPuncteCompletare, @newRating, @newDificultateNume, @newCategorieNume) = 0
		BEGIN
			RAISERROR('Datele noi pentru minigame nu sunt valide!', 16, 1);
			RETURN;
		END

		DECLARE @newDificultateId INT;
		SELECT @newDificultateId = id_d FROM Dificultate WHERE diff = @newDificultateNume;

		DECLARE @newCategorieId INT;
		SELECT @newCategorieId = id_c FROM Categorii WHERE nume_categorie = @newCategorieNume;

		UPDATE Minigames
		SET	titlu = @newTitlu, descriere = @newDescriere, puncte_completare = @newPuncteCompletare,
			rating = @newRating, id_d = @newDificultateId, id_c = @newCategorieId
		WHERE id_m = @id_m;
	END TRY
	BEGIN CATCH
		DECLARE @errorMsg NVARCHAR(4000) = ERROR_MESSAGE();
		RAISERROR(@errorMsg, 16, 1);
	END CATCH
END;

EXEC UpdateMinigames 2, 'Marius', 'Furi brainrot-urile oamenilor', 100, NULL, 'normal', 'Kids';

SELECT * FROM Minigames;
SELECT * FROM LoggingMinigames;

--------------------------------------------------------------------------------------------------
-- DELETE

CREATE OR ALTER PROCEDURE DeletePlayers
	@id_p INT
AS
BEGIN
	BEGIN TRY
		IF dbo.ValidateIdPlayers(@id_p) = 0
		BEGIN
			RAISERROR('Nu exista player cu id-ul specificat!', 16, 1);
			RETURN;
		END

		DELETE FROM Prieteni WHERE id_p1 = @id_p OR id_p2 = @id_p;

		DELETE FROM JocuriPreferate WHERE id_p = @id_p;

		DELETE FROM Achizitii WHERE id_p = @id_p;

		DELETE FROM Players WHERE id_p = @id_p;

	END TRY
	BEGIN CATCH
		DECLARE @errorMsg NVARCHAR(4000) = ERROR_MESSAGE();
		RAISERROR(@errorMsg, 16, 1);
	END CATCH
END;


ALTER TABLE Prieteni DROP CONSTRAINT fk_Player1;
ALTER TABLE Prieteni DROP CONSTRAINT fk_Player2;

ALTER TABLE Prieteni
ADD CONSTRAINT fk_Player1 FOREIGN KEY (id_p1) REFERENCES Players(id_p);

ALTER TABLE Prieteni
ADD CONSTRAINT fk_Player2 FOREIGN KEY (id_p2) REFERENCES Players(id_p);

EXEC DeletePlayers 10;

SELECT * FROM Players;
SELECT * FROM LoggingPlayers;

--------------------------------------------------------------------------------------------------
CREATE OR ALTER PROCEDURE DeleteMinigames
	@id_m INT
AS
BEGIN
	BEGIN TRY
		IF dbo.ValidateIdMinigames(@id_m) = 0
		BEGIN
			RAISERROR('Nu exista minigame cu id-ul specificat!', 16, 1);
			RETURN;
		END

		DELETE FROM Rating WHERE id_m = @id_m;

		DELETE FROM JocuriPreferate WHERE id_m = @id_m;

		DELETE FROM Minigames WHERE id_m = @id_m;

	END TRY
	BEGIN CATCH
		DECLARE @errorMsg NVARCHAR(4000) = ERROR_MESSAGE();
		RAISERROR(@errorMsg, 16, 1);
	END CATCH
END;

EXEC DeleteMinigames 6;

SELECT * FROM Minigames;
SELECT * FROM LoggingMinigames;

--------------------------------------------------------------------------------------------------
-- VIEW-URI

-- arata playerii care au jocuri preferate cu un rating <= 3
CREATE OR ALTER VIEW vw_PlayersMinigamesRating
AS
SELECT P.username AS player, M.titlu AS joc, M.descriere AS descriere, M.rating AS rating
FROM Players P
INNER JOIN JocuriPreferate JP ON JP.id_p = P.id_p
INNER JOIN Minigames M ON JP.id_m = M.id_m
WHERE M.rating <= 3;


-- arata playerii care au jocuri preferate cu puncte pentru completare < 100
CREATE OR ALTER VIEW vw_PlayersMinigamesPuncte
AS
SELECT P.username AS player, M.titlu AS joc, M.descriere AS descriere, M.puncte_completare AS puncte_completare
FROM Players P
INNER JOIN JocuriPreferate JP ON JP.id_p = P.id_p
INNER JOIN Minigames M ON JP.id_m = M.id_m
WHERE M.puncte_completare < 100;


--------------------------------------------------------------------------------------------------
-- INDECSI

-- index pentru optimizarea JOIN-ului pe tabela de legatura (foreign key)
CREATE NONCLUSTERED INDEX ix_JocuriPreferate 
ON JocuriPreferate(id_m);

-- index "covering" pentru filtrarea dupa rating
CREATE NONCLUSTERED INDEX ix_MinigamesRating
ON Minigames(rating)
INCLUDE (titlu, descriere)
WHERE rating <= 3;

--index "covering" pentru filtrarea dupa puncte_completare
CREATE NONCLUSTERED INDEX ix_MinigamesPuncte
ON Minigames(puncte_completare)
INCLUDE (titlu, descriere)
WHERE puncte_completare < 100;


SELECT * FROM vw_PlayersMinigamesRating;
SELECT * FROM vw_PlayersMinigamesPuncte;
