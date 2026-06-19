CREATE DATABASE ModelOSER;
GO
USE ModelOSER;
GO

-- Produse N:1 Categorii
-- Categorii N:M Tarabe
-- Tarabe N:1 Hale

CREATE TABLE Produse
(
	id INT PRIMARY KEY IDENTITY,
	denumire VARCHAR(50),
	pret INT,
	id_categorie INT FOREIGN KEY REFERENCES Categorii(id)
);

CREATE TABLE Categorii
(
	id INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50)
);

CREATE TABLE Hale
(
	id INT PRIMARY KEY IDENTITY,
	litera CHAR(1),
	suprafata INT
);

CREATE TABLE Tarabe
(
	id INT PRIMARY KEY IDENTITY,
	suprafata INT,
	numar INT,
	id_hala INT FOREIGN KEY REFERENCES Hale(id)
);

CREATE TABLE TarabeCategorii
(
	id_t INT FOREIGN KEY REFERENCES Tarabe(id),
	id_c INT FOREIGN KEY REFERENCES Categorii(id),
	CONSTRAINT pk_TarabeCategorii PRIMARY KEY (id_t, id_c)
);


CREATE OR ALTER PROCEDURE ActualizarePret @id_taraba INT
AS
BEGIN
-- update 2, 3, 1 pt evitarea update-ului dublu
-- a doua conditie
UPDATE Produse SET pret = pret + 50 WHERE id IN 
(SELECT P.id FROM Produse P
INNER JOIN TarabeCategorii TC ON TC.id_c = P.id_categorie
WHERE TC.id_t = @id_taraba AND P.pret > 200);

-- a treia conditie
UPDATE Produse SET pret = pret * 1.1 WHERE id IN 
(SELECT P.id FROM Produse P
INNER JOIN TarabeCategorii TC ON TC.id_c = P.id_categorie
WHERE TC.id_t = @id_taraba AND P.pret BETWEEN 100 AND 200);

-- prima conditie
UPDATE Produse SET pret = pret + 10 WHERE id IN 
(SELECT P.id FROM Produse P
INNER JOIN TarabeCategorii TC ON TC.id_c = P.id_categorie
WHERE TC.id_t = @id_taraba AND P.pret < 100);

END;


CREATE OR ALTER VIEW vw_produse AS
SELECT P.denumire AS Denumire, P.pret * 0.4 AS Pret FROM Produse P
INNER JOIN Categorii C ON C.id = P.id_categorie
INNER JOIN TarabeCategorii TC ON TC.id_c = C.id
INNER JOIN Tarabe T ON T.id = TC.id_t
INNER JOIN Hale H ON H.id = T.id_hala
WHERE H.litera IN ('A', 'F', 'X')
AND C.nume IN ('HAINE', 'VESELA');


INSERT INTO HALE (LITERA, SUPRAFATA) VALUES 
('A', 100), ('B',200)

INSERT INTO TARABE (ID_HALA, NUMAR, SUPRAFATA) VALUES 
(1, 1, 5), (2,2,10)

INSERT INTO CATEGORII (NUME) VALUES
('VESELA'), ('HAINE'), ('GRADINA')

INSERT INTO TARABECATEGORII (ID_C, ID_T) VALUES
(1, 1), (3,1), (2, 2)

INSERT INTO PRODUSE (PRET, DENUMIRE, ID_CATEGORIE) VALUES
(10,'FARFURIE', 1), (2, 'CUTIT', 1),
(500, 'GEACA', 2), (150, 'BLUGI', 2),
(150, 'FURTUN', 3), (700, 'GARD', 3)

SELECT * FROM vw_produse;

SELECT * FROM Produse;
EXEC ActualizarePret 1;