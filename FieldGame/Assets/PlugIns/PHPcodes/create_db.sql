-- > mysql -uroot -pbitnami mysql < create_db.sql

use mysql;

delete from user where User='graduate' and Host='localhost';
insert into user(User, Host, Password) values ('graduate', 'localhost', password('bitnami'));
flush privileges; -- please don't forget to add the following command

drop database if exists my_game;
create database my_game;

grant all on my_game.* to 'graduate'@'localhost' identified by 'bitnami';
flush privileges;