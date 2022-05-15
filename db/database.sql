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
    ip varchar(10) NOT NULL,
    userId int NOT NULL,
    loginCookie varchar(100) NOT NULL,
    createdAt timestamp default current_timestamp,
    active boolean NOT NULL,
    primary key(id),
    foreign key(userId) references user(id)
);

CREATE TABLE sell(
    id int auto_increment,
    nameArticle varchar(100),
    valueArticle int,
    descriptionArticle varchar(5000),
    img varchar(1000),
    createdAt timestamp default current_timestamp,
    primary key(id)
);