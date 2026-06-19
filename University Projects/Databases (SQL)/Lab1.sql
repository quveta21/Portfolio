CREATE DATABASE Lab1;
GO
USE Lab1;

CREATE TABLE Players
(id_p INT PRIMARY KEY IDENTITY,
username VARCHAR(50) NOT NULL UNIQUE,
parola VARCHAR(50) NOT NULL,
nume_display NVARCHAR(50) DEFAULT 'Anonim',
puncte INT DEFAULT 0
);

CREATE TABLE Levels
(id_l INT PRIMARY KEY IDENTITY,
nivel INT DEFAULT 1,
CONSTRAINT ck_nivel CHECK (nivel >= 1)
);

ALTER TABLE Players
ADD id_l INT

ALTER TABLE Players
ADD CONSTRAINT fk_PlayerLevel FOREIGN KEY (id_l) REFERENCES Levels(id_l);

CREATE TABLE Minigames
(id_m INT PRIMARY KEY IDENTITY,
titlu NVARCHAR(50) NOT NULL,
descriere NVARCHAR(200),
puncte_completare INT,
rating INT,
CONSTRAINT ck_rating CHECK (rating >= 1 AND rating <= 5)
);

CREATE TABLE JocuriPreferate
(id_p INT,
id_m INT,
CONSTRAINT fk_PlayersJocuriPreferate FOREIGN KEY (id_p) REFERENCES Players(id_p),
CONSTRAINT fk_MinigamesJocuriPreferate FOREIGN KEY (id_m) REFERENCES Minigames(id_m),
CONSTRAINT pk_JocuriPreferate PRIMARY KEY (id_p)
);

CREATE TABLE Rating
(id_p INT,
id_m INT,
valoare INT CHECK (valoare >= 1 AND valoare <= 5),
CONSTRAINT fk_PlayersRating FOREIGN KEY (id_p) REFERENCES Players(id_p),
CONSTRAINT fk_MinigamesRating FOREIGN KEY (id_m) REFERENCES Minigames(id_m),
CONSTRAINT pk_Rating PRIMARY KEY (id_p, id_m)
);

CREATE TABLE Categorii
(id_c INT PRIMARY KEY IDENTITY,
nume_categorie VARCHAR(50) NOT NULL
);

CREATE TABLE MinigamesCategorii
(id_m INT,
id_c INT,
CONSTRAINT fk_Minigames FOREIGN KEY (id_m) REFERENCES Minigames(id_m),
CONSTRAINT fk_Categorii FOREIGN KEY (id_c) REFERENCES Categorii(id_c),
CONSTRAINT pk_MinigamesCategorii PRIMARY KEY (id_m, id_c)
);

CREATE TABLE Accesorii
(id_a INT PRIMARY KEY IDENTITY,
nume_accesoriu NVARCHAR(50) NOT NULL,
pret INT CHECK (pret > 0),
);

CREATE TABLE Achizitii
(id_a INT,
id_p INT,
pret INT CHECK (pret > 0),
data_achizitiei DATE DEFAULT GETDATE(),
CONSTRAINT fk_AccesoriiAchizitii FOREIGN KEY (id_a) REFERENCES Accesorii(id_a),
CONSTRAINT fk_PlayersAchizitii FOREIGN KEY (id_p) REFERENCES Players(id_p),
CONSTRAINT pk_Achizitii PRIMARY KEY (id_a, id_p)
);

CREATE TABLE Prieteni
(id_p1 INT,
id_p2 INT,
status_curent VARCHAR(50),
CONSTRAINT fk_Player1 FOREIGN KEY (id_p1) REFERENCES Players(id_p),
CONSTRAINT fk_Player2 FOREIGN KEY (id_p2) REFERENCES Players(id_p),
CONSTRAINT pk_Prieteni PRIMARY KEY (id_p1, id_p2),
CONSTRAINT ck_status_curent CHECK (status_curent = 'pending' OR status_curent = 'accepted' OR status_curent = 'blocked')
);

--INSERAM VALORI IN TABELE

INSERT INTO Levels (nivel) VALUES
(1), (2), (3), (4), (5), (6), (7), (8), (9), (10);

INSERT INTO Players (username, parola, nume_display, puncte, id_l) VALUES
('doamneferestema', 'dmnfrst2005', 'marc21', 1000, 10),
('denislucawbfan', 'westbrookfan', 'deniSs', 550, 5),
('calinagainusa', 'florina2006', 'florinaGaina', 310, 3),
('alexmnt', '1278940', 'alexMuntean', 0, 1),
('playboi_marti', 'neformoldovean69', 'destroy_mario', 690, 6),
('lobo_frt', 'mobtrap2187', 'loboo_no1', 840, 8),
('mar_aprilya', 'HelloKittyfan2006', 'mar_april', 210, 2),
('nandrean_power', 'ocnaBigBOss', 'SmurduVTM', 990, 9),
('yoko_koko23', 'cj23YEN', 'angelo.real', 630, 6),
('nicole1star', 'parola12345', 'medee_kole', 150, 1);

INSERT INTO Minigames (titlu, descriere, puncte_completare, rating) VALUES
('Bloodlines', 'Lupte cu animeuri nush', 50, 3),
('Rivals', 'Impuscaturi 1v1 tare rau', 120, 5),
('Steal a Brainrot', 'Nu trebuie sa explic nimica', 70, 4),
('Blade Ball', 'Dai cu sabia in minge', 200, 5),
('Guess the MEME', 'Exact ce zice titlul', 100, 3),
('Skateboard Obby', 'E mai greu decat pare', 300, 4),
('MMA Legends', 'Lupti in arte martiale mixte', 350, 2),
('Barber Simulator', 'Tunde clienti si castiga bani', 250, 4),
('FORTBLOX', 'Fortnite ripoff', 90, 1),
('Survive99Nights', 'Supravietuieste in padure', 400, 5);

INSERT INTO Categorii (nume_categorie) VALUES
('Horror'),
('Family'),
('Anime'),
('Shooter'),
('Arcade'),
('Indie'),
('Simulator'),
('Roleplay'),
('Action'),
('Kids');

INSERT INTO MinigamesCategorii (id_m, id_c) VALUES
(1,3),
(2,4),
(3,10),
(4,5),
(5,10),
(6,7),
(7,9),
(8,7),
(9,4),
(10,1);

INSERT INTO Rating (id_p, id_m, valoare) VALUES
(1, 4, 3),
(1, 7, 5),
(5, 5, 2),
(2, 3, 4),
(4, 3, 5),
(6, 7, 2),
(9, 10, 5),
(8, 1, 1),
(8, 4, 2),
(2, 2, 5);

INSERT INTO JocuriPreferate (id_p, id_m) VALUES
(1, 10), (2, 5), (3, 10), (4, 9), (5, 8), (6, 2), (7, 2), (8, 4), (9, 7), (10, 5);

INSERT INTO Prieteni (id_p1, id_p2, status_curent) VALUES
(1, 3, 'accepted'),
(2, 4, 'pending'),
(1, 6, 'blocked'),
(5, 6, 'accepted'),
(4, 1, 'accepted'),
(3, 2, 'accepted'),
(3, 8, 'pending'),
(1, 10, 'accepted'),
(8, 5, 'blocked'),
(10, 4, 'blocked');

INSERT INTO Accesorii (nume_accesoriu, pret) VALUES
('Spongebob Hat', 100),
('Black TShirt', 50),
('White Jeans', 150),
('Blue Shirt', 70),
('Gold Chain', 500),
('Converse Sneakers', 200),
('Gucci Belt', 700),
('Basic Hat', 10),
('Adidas Trening', 180),
('Diamond Chain', 1500);

INSERT INTO Achizitii (id_a, id_p, pret, data_achizitiei) VALUES
(1, 1, 100, '2025-07-10'),
(3, 1, 150, '2025-10-04'),
(7, 3, 700, '2025-03-21'),
(9, 4, 180, '2025-05-05'),
(2, 5, 50, '2025-01-01'),
(6, 5, 200, '2025-07-30'),
(10, 1, 1500, '2025-10-16'),
(4, 9, 70, '2025-09-29'),
(8, 8, 10, '2025-02-08'),
(5, 3, 500, '2025-09-09');

-- INTEROGARI 

-- accesoriile cumparate luna aceasta
SELECT * FROM Achizitii WHERE MONTH(data_achizitiei) = MONTH(GETDATE()) 
							AND YEAR(data_achizitiei) = YEAR(GETDATE());

-- jocurile care fac parte din categoriile ('Shooter', 'Action')
SELECT M.titlu AS joc, C.nume_categorie AS categorie FROM Minigames M
	INNER JOIN MinigamesCategorii MC ON M.id_m=MC.id_m
	INNER JOIN Categorii C ON C.id_c=MC.id_c
	WHERE C.nume_categorie IN ('Shooter', 'Action');

-- jocurile Horror care dau mai mult de 100 de puncte la completare
SELECT M.titlu AS joc, C.nume_categorie AS categorie, M.puncte_completare AS puncte FROM Minigames M
	INNER JOIN MinigamesCategorii MC ON M.id_m=MC.id_m
	INNER JOIN Categorii C ON C.id_c=MC.id_c
	WHERE C.nume_categorie='Horror' AND M.puncte_completare > 100;

-- jucatorii care au minim 2 prieteni si nivelul cel putin 3
SELECT L.nivel AS nivel, P.nume_display AS jucator, COUNT(id_p2) nr_prieteni FROM Players P
	INNER JOIN Prieteni Pr ON P.id_p IN (Pr.id_p1, Pr.id_p2) AND Pr.status_curent='accepted'
	INNER JOIN Levels L ON L.id_l=P.id_l
	WHERE L.nivel>=3
	GROUP BY L.nivel, P.id_p, P.nume_display
	HAVING COUNT(id_p2) >= 2;

-- jucatorii care au minim 2 accesorii
SELECT L.nivel AS nivel, P.nume_display AS jucator, COUNT(id_a) nr_accesorii FROM Players P
	INNER JOIN Achizitii A ON P.id_p=A.id_p
	INNER JOIN Levels L ON L.id_l=P.id_l
	GROUP BY L.nivel, P.nume_display
	HAVING COUNT(id_a) >= 2;

-- jocurile ('Shooter', 'Action') care au rating minim 2
SELECT M.titlu AS joc, C.nume_categorie AS categorie, M.rating AS rating FROM Minigames M
	INNER JOIN MinigamesCategorii MC ON M.id_m=MC.id_m
	INNER JOIN Categorii C ON C.id_c=MC.id_c
	WHERE C.nume_categorie IN ('Shooter', 'Action') AND M.rating >= 2;

-- afiseaza rating-ul average pentru jocuri si categoria din care fac parte
SELECT M.titlu AS titlu, C.nume_categorie AS categorie, AVG(valoare) rating FROM Minigames M
	INNER JOIN Rating R ON M.id_m=R.id_m
	INNER JOIN MinigamesCategorii MC ON M.id_m=MC.id_m
	INNER JOIN Categorii C ON C.id_c=MC.id_c
	GROUP BY M.titlu, C.nume_categorie;

-- afiseaza jocul preferat pentru fiecare jucator
SELECT P.nume_display AS jucator, M.titlu AS joc_preferat FROM Players P
	INNER JOIN JocuriPreferate JP ON P.id_p=JP.id_p
	INNER JOIN Minigames M ON M.id_m=JP.id_m;

-- afiseaza toate prieteniile jucatorului 'marc21'
SELECT DISTINCT P1.nume_display AS p1, P2.nume_display AS p2 FROM Prieteni Pr
	INNER JOIN Players P1 ON P1.id_p = Pr.id_p1
	INNER JOIN Players P2 ON P2.id_p = Pr.id_p2
	WHERE P1.nume_display='marc21' OR P2.nume_display='marc21';

-- accesoriile care au fost cumparate de maxim 2 jucatori
SELECT DISTINCT Acc.nume_accesoriu AS accesoriu, COUNT(DISTINCT Ach.id_p) nr_achizitii FROM Accesorii Acc
	INNER JOIN Achizitii Ach ON Acc.id_a=Ach.id_a
	GROUP BY Acc.nume_accesoriu
	HAVING COUNT(DISTINCT Ach.id_p) <= 2;