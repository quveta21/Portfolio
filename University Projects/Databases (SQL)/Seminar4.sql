USE Seminar2;

-- functii 1)
CREATE FUNCTION CodulCategoriei(@nume NVARCHAR(50))
RETURNS INT AS
BEGIN
DECLARE @cod INT;
SELECT @cod=cod_c FROM Categorii WHERE nume=@nume
RETURN @cod;
END;

GO
-- Apelul functiei
PRINT dbo.CodulCategoriei('Adolescenti')

-- functii 2)
CREATE FUNCTION SectiuniLiteraFinala(@litera CHAR(1))
RETURNS TABLE
AS
RETURN SELECT * FROM Sectiuni WHERE LEN(nume) >= 2 AND RIGHT(nume, 1) = @litera;

GO
-- Apelul functiei
SELECT * FROM dbo.SectiuniLiteraFinala(5);

-- view 1)
ALTER VIEW vw_CategoriiPensionariCopii
AS
SELECT * FROM Categorii C
WHERE C.nume IN ('Batrani', 'Copii');

GO
SELECT * FROM vw_CategoriiPensionariCopii

