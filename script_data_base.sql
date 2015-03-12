-- Geração de Modelo físico
-- Sql ANSI 2003 - brModelo.



CREATE TABLE Usuario (
Usuario_Id INTEGER PRIMARY KEY,
Nome VARCHAR(250),
Email VARCHAR(250),
Senha VARCHAR(250),
CreatedOn DATETIME,
LastAccess DATETIME
)

CREATE TABLE Contato (
Contato_Id INTEGER PRIMARY KEY,
Descricao VARCHAR(250),
CreatedOn DATETIME,
Valor VARCHAR(250),
Ativado INTEGER,
ModifielOn DATETIME,
Usuario_Id INTEGER,
FOREIGN KEY(Usuario_Id) REFERENCES Usuario (Usuario_Id)
)

CREATE TABLE HistoricoFrase (
HistoricoFrase_Id INTEGER PRIMARY KEY,
PercentualRendimento DECIMAL(10,4),
CreatedOn DATETIME,
Frase_Id INTEGER,
Usuario_Id INTEGER,
FOREIGN KEY(Usuario_Id) REFERENCES Usuario (Usuario_Id)
)

CREATE TABLE Deck (
Dificuldade INTEGER,
ModifiedOn DATETIME,
CreatedOn DATETIME,
Deck_Id INTEGER PRIMARY KEY,
Ativado INTEGER,
Descricao VARCHAR(250)
)

CREATE TABLE Frase (
Ativado INTEGER,
Back VARCHAR(250),
Frase_Id INTEGER PRIMARY KEY,
ModifiedOn DATETIME,
CreatedOn DATETIME,
Nivel INTEGER,
Front VARCHAR(500),
Deck_Id INTEGER,
FOREIGN KEY(Deck_Id) REFERENCES Deck (Deck_Id)
)

CREATE TABLE HistoricoDeck (
HistoricoDeck_Id INTEGER PRIMARY KEY,
PercentualRendimento DECIMAL(10,4),
CreatedOn VARCHAR(10),
Deck_Id INTEGER,
Usuario_Id INTEGER,
FOREIGN KEY(Deck_Id) REFERENCES Deck (Deck_Id),
FOREIGN KEY(Usuario_Id) REFERENCES Usuario (Usuario_Id)
)

CREATE TABLE Idioma (
Idioma_Id INTEGER PRIMARY KEY,
Idioma VARCHAR(250)
)

CREATE TABLE Possui (
Idioma_Id INTEGER,
Deck_Id INTEGER,
FOREIGN KEY(Idioma_Id) REFERENCES Idioma (Idioma_Id),
FOREIGN KEY(Deck_Id) REFERENCES Deck (Deck_Id)
)

ALTER TABLE HistoricoFrase ADD FOREIGN KEY(Frase_Id) REFERENCES Frase (Frase_Id)
