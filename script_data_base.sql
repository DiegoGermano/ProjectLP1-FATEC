-- Geração de Modelo físico
-- Sql ANSI 2003 - brModelo.

CREATE TABLE Word (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
Level INTEGER,
Back VARCHAR(250),
Front VARCHAR(500),
CreatedOn DATETIME,
Activated INTEGER,
ModifiedOn DATETIME,
Deck_Id INTEGER
)

CREATE TABLE Deck (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
Description VARCHAR(250),
ModifiedOn DATETIME,
CreatedOn DATETIME,
Activated INTEGER,
Level INTEGER,
Language_Id INTEGER
)

CREATE TABLE HistoryDeck (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
PercentYield DECIMAL(10),
CreatedOn DATETIME,
Deck_Id INTEGER,
User_Id INTEGER,
FOREIGN KEY(Deck_Id) REFERENCES Deck (Id)
)

CREATE TABLE HistoryWord (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
CreatedOn DATETIME,
PrecentYield DECIMAL(10),
Frase_Id INTEGER,
User_Id INTEGER,
FOREIGN KEY(Frase_Id) REFERENCES Word (Id)
)

CREATE TABLE Language (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
Language VARCHAR(250)
)

CREATE TABLE User (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
LastAccess DATETIME,
CreatedOn DATETIME,
Password VARCHAR(250),
Email VARCHAR(250),
Name VARCHAR(250)
)

CREATE TABLE Contact (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
Description VARCHAR(250),
CreatedOn DATETIME,
ModifielOn DATETIME,
Value VARCHAR(250),
Activated INTEGER,
User_Id INTEGER,
FOREIGN KEY(User_Id) REFERENCES User (Id)
)

CREATE TABLE AccessUser (
Id INTEGER PRIMARY KEY AUTO_INCREMENT,
Token VARCHAR(500),
ExpiresOn DATETIME,
CreatedOn DATETIME,
User_Id INTEGER,
FOREIGN KEY(User_Id) REFERENCES User (Id)
)

ALTER TABLE Word ADD FOREIGN KEY(Deck_Id) REFERENCES Deck (Id)
ALTER TABLE Deck ADD FOREIGN KEY(Language_Id) REFERENCES Language (Id)
ALTER TABLE HistoryDeck ADD FOREIGN KEY(User_Id) REFERENCES User (Id)
ALTER TABLE HistoryWord ADD FOREIGN KEY(User_Id) REFERENCES User (Id)



ALTER TABLE `User` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `User` MODIFY COLUMN `LastAccess` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `accessuser` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `Contact` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `Contact` MODIFY COLUMN `ModifielOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `deck` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `deck` MODIFY COLUMN `ModifiedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `word` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `word` MODIFY COLUMN `ModifiedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `historydeck` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `historyword` MODIFY COLUMN `CreatedOn` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;


ALTER TABLE user ADD UNIQUE (email)
alter table deck add user_id integer not null


alter view view_deck as
select 
	deck.user_id,
	CONCAT("{\"id\":",deck.Id) as Id, 
	CONCAT(",\"description\":\"", deck.Description, "\"") as Deck,
	CONCAT(",\"language\":\"", language.language, "\"") as language,
    CONCAT(",\"amountWord\":",IFNULL( (select Count(*) as AmountWord from word where deck_id = deck.id),0) ) as AmountWord,
    CONCAT(",\"amountStudy\":",IFNULL( (select Count(*) as AmountStudy from historydeck where deck_id = deck.id),0) ) as AmountStudy,
	CONCAT(",\"daysLastStudy\":",
    
    DATEDIFF(IFNULL((select CreatedOn from historydeck where deck_id = deck.id order by CreatedOn desc),NOW()), NOW())
    
    , "") as daysLastStudy,
	CONCAT(",\"PercentYield\":",IFNULL((select PercentYield from historydeck where deck_id = deck.id order by CreatedOn desc),0), "}") as PercentYield

from deck 
INNER JOIN Language on deck.Language_Id = language.id


CREATE VIEW view_word 
AS
	select
		CONCAT('{"id":', Id) as Id,
		CONCAT(',"Back":"', Back, '"') as Back,
		CONCAT(',"Front":"', Front, '"}') as Front,
		deck_id
	from word

