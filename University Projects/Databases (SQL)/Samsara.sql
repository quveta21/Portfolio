USE ModelSamsara;

CREATE TABLE Clienti
(
	id_c INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	telefon VARCHAR(50)
);

CREATE TABLE Ingrediente
(
	id_i INT PRIMARY KEY IDENTITY,
	denumire VARCHAR(50),
	calorii INT
);

CREATE TABLE Preparate
(
	id_p INT PRIMARY KEY IDENTITY,
	denumire VARCHAR(50),
	cantitate INT,
	pret INT
);

CREATE TABLE Comenzi
(
	id_co INT PRIMARY KEY IDENTITY,
	adresa_livrare VARCHAR(100),
	data DATE,
	id_c INT FOREIGN KEY REFERENCES Clienti(id_c)
);

CREATE TABLE PreparateIngrediente
(
	id_p INT,
	id_i INT,
	CONSTRAINT fk_Preparate FOREIGN KEY (id_p) REFERENCES Preparate(id_p),
	CONSTRAINT fk_Ingrediente FOREIGN KEY (id_i) REFERENCES Ingrediente(id_i),
	CONSTRAINT pk_PreparateIngrediente PRIMARY KEY (id_p, id_i)
);

CREATE TABLE ComenziPreparate
(
	id INT PRIMARY KEY IDENTITY,
	id_co INT,
	id_p INT,
	CONSTRAINT fk_Comenzi FOREIGN KEY (id_co) REFERENCES Comenzi(id_co),
	CONSTRAINT fk_PreparateCP FOREIGN KEY (id_p) REFERENCES Preparate(id_p),
);

INSERT INTO CLIENTI(NUME, TELEFON) VALUES ('Bogdan Ioan', '0777888999'), 
('Luis Fonsi', '00409975874')

INSERT INTO COMENZI(ADRESA_LIVRARE, DATA, ID_C) VALUES 
('Kogalniceanu 1', '2024-12-24', 1),
('Mihali 3', '2025-01-01', 1),
('Dorobantilor 7', '2024-01-02', 2)

INSERT INTO INGREDIENTE (DENUMIRE, CALORII) VALUES
('Avocado', 200),
('Cartofi', 100)

INSERT INTO PREPARATE (DENUMIRE, CANTITATE, PRET) VALUES
('Piure', 200, 14),
('Avocado', 50, 23),
('Cartofi prajiti', 200, 12)

INSERT INTO PREPARATEINGREDIENTE (ID_P, ID_I) VALUES
(1, 2), (2,1), (3,2)

INSERT INTO COMENZIPREPARATE (ID_CO, ID_P) VALUES 
(1, 1), (1,2), 
(2,1), (2,1), (2,3),
(3,2), (3,2)


CREATE OR ALTER PROCEDURE StergeIngredientInterzis 
@nume_ingredient VARCHAR(50)
AS
BEGIN

DECLARE @id_ingredient INT;
SELECT @id_ingredient = id_i FROM Ingrediente WHERE denumire = @nume_ingredient;

DECLARE @nr_comenzi_sterse INT;

SELECT @nr_comenzi_sterse = COUNT(DISTINCT CP.id_co) FROM ComenziPreparate CP
INNER JOIN Preparate P on CP.id_p = P.id_p
INNER JOIN PreparateIngrediente PRI on PRI.id_p = P.id_p
WHERE PRI.id_p = @id_ingredient;

DELETE FROM ComenziPreparate WHERE id_co IN (SELECT CP.id_co FROM ComenziPreparate CP
INNER JOIN Preparate P on CP.id_p = P.id_p
INNER JOIN PreparateIngrediente PRI on PRI.id_p = P.id_p
WHERE PRI.id_p = @id_ingredient);

DELETE FROM Comenzi WHERE id_co NOT IN (SELECT id_co FROM ComenziPreparate);

RETURN @nr_comenzi_sterse;

END


CREATE OR ALTER VIEW vw_comenzi AS
SELECT C.data AS data_comenzii, SUM(P.pret) AS suma_achitata 
FROM Clienti CL
INNER JOIN Comenzi C ON C.id_c = CL.id_c
INNER JOIN ComenziPreparate CP on CP.id_co = C.id_co
INNER JOIN Preparate P ON P.id_p = CP.id_p
WHERE CL.nume LIKE 'Bogdan Ioan'
GROUP BY C.id_co, C.data;

SELECT * FROM vw_comenzi;

DECLARE @nr_sterse INT;
EXEC @nr_sterse = dbo.StergeIngredientInterzis 'Avocado';
SELECT 'Comenzi sterse' = @nr_sterse;