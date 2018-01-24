drop database if exists my_game;
create database my_game;

use my_game;

create table UserAccount (
		userid    varchar(40) not null,
		passwd    varchar(64) not null,
 		name      varchar(40),
  		score     int,
  		primary key (userid)
);

-- Populate

-- INSERT INTO UserAccount VALUES('bseo', 'asd', 'Beomjoo Seo', 0, 1);
 INSERT INTO UserAccount VALUES('jun', sha2('lee', 224), 'Ron', 999);
 INSERT INTO UserAccount VALUES('Lewdif', sha2('ljy', 224), 'jy Lee', 999);


-- select * from UserAccount where userid='bseo' and passwd=sha2('test',224);
