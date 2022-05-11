DROP TABLE user;
DROP TABLE userSession;
DROP TABLE sell;

CREATE TABLE user(
    id int auto_increment,
    firstName varchar(100),
    lastName varchar(100),
    email varchar(100),
    userPassword varchar(100),
    createdAt timestamp default current_timestamp,
    primary key(id)
);

CREATE TABLE userSession(
    id int auto_increment,
    ip varchar(10),
    userId int,
    userLogin varchar(100),
    createdAt timestamp default current_timestamp,
    primary key(id)
);

CREATE TABLE sell(
    id int auto_increment,
    nameArticle varchar(100),
    valueArticle int,
    DescriptionArticle varchar(5000),
    Img varchar(1000),
    createdAt timestamp default current_timestamp,
    primary key(id)
);