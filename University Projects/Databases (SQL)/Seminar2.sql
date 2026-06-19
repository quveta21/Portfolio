CREATE DATABASE Seminar2;
GO
USE Seminar2;

CREATE TABLE Sectiuni
(cod_s INT PRIMARY KEY IDENTITY,
nume NVARCHAR(50) NOT NULL,
descriere NVARCHAR(200)
);

CREATE TABLE Atractii
(cod_a INT PRIMARY KEY IDENTITY,
nume NVARCHAR(50) NOT NULL,
descriere NVARCHAR(200),
varsta_min INT CHECK(varsta_min > 0),
cod_s INT,
CONSTRAINT fk_SectiuniAtractii FOREIGN KEY (cod_s) REFERENCES Sectiuni(cod_s)
);

CREATE TABLE Categorii
(cod_c INT PRIMARY KEY IDENTITY,
nume NVARCHAR(50)
);

CREATE TABLE Vizitatori
(cod_v INT PRIMARY KEY IDENTITY,
nume NVARCHAR(50) NOT NULL,
email VARCHAR(50) NOT NULL,
cod_c INT,
CONSTRAINT fk_CategoriiVizitatori FOREIGN KEY (cod_c) REFERENCES Categorii(cod_c)
);

CREATE TABLE Note
(cod_a INT,
cod_v INT,
nota INT CHECK(nota >= 1 AND nota <= 10),
CONSTRAINT fk_AtractiiNote FOREIGN KEY (cod_a) REFERENCES Atractii(cod_a),
CONSTRAINT fk_VizitatoriNote FOREIGN KEY (cod_v) REFERENCES Vizitatori(cod_v),
CONSTRAINT pk_Note PRIMARY KEY (cod_a, cod_v)
);

INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 1', 'o sectiune faina');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 2', 'o sectiune ok');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 3', 'o sectiune draguta');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 4', 'o sectiune smechera');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 5', 'o sectiune decenta');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 6', 'o sectiune naspa');
INSERT INTO Sectiuni (nume, descriere) VALUES ('sectiunea 7', 'o sectiune acceptabila');


INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('rollercoaster', 'un rollercoaster frumos', 16, 1);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('bungee jumping', 'tare rau', 12, 2);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('bicicleta', 'pt sportivi', 8, 2);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('ciocan', 'doar nebunii se dau', 18, 2);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('banca rotativa', 'ti se face rau', 10, 4);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('nimica', 'absolut nimic', 1, 6);
INSERT INTO Atractii (nume, descriere, varsta_min, cod_s) VALUES
('madalin horror', 'ii ft scary', 25, 1);

INSERT INTO Categorii (nume) VALUES
('Batrani'),
('Copii'),
('Adolescenti'),
('Adulti'),
('Caini'),
('Pisici'),
('Xenomorphi')

INSERT INTO Vizitatori (nume, email, cod_c) VALUES
('Alex', 'alex_gayu@gmail.com', 1),
('Madalin', 'madalincurufin@gmail.com', 7),
('Alexandra', 'ale1234@gmail.com', 2),
('Marc', 'marcsmecherul@gmail.com', 1),
('Denis', 'denisluca@gmail.com', 5),
('Ion', 'ionutpevaldemare@gmail.com', 6),
('Calina', 'calinagainusa@gmail.com', 6)

INSERT INTO Note (cod_a, cod_v, nota) VALUES
(3, 5, 8),
(1, 1, 10),
(7, 5, 5),
(2, 1, 9),
(6, 2, 7),
(5, 3, 9),
(4, 2, 4)

UPDATE Sectiuni SET descriere='madalin horror' WHERE nume='sectiunea 1';
UPDATE Atractii SET nume='rollercoaster gigantic' WHERE nume='rollercoaster';
UPDATE Categorii SET nume='eXtraterestrii' WHERE nume='Xenomorphi';
UPDATE Vizitatori SET email='marc.mrs21@gmail.com' WHERE nume='Marc';
UPDATE Note SET nota = 9 WHERE (cod_a=3 AND cod_v=5);