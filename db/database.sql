DROP TABLE userSession;
DROP TABLE shoppingCart;
DROP TABLE shoppingCheckout;
DROP TABLE sell;
DROP TABLE user;
DROP TABLE userComment;

CREATE TABLE user(
    id int auto_increment,
    firstName varchar(30),
    lastName varchar(30),
    email varchar(50),
    userPassword varchar(100),
    createdAt timestamp default current_timestamp,
    phoneNumber int,
    direction varchar(100),
    primary key(id)
);

CREATE TABLE userSession(
    id int auto_increment,
    ip varchar(20) NOT NULL,
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
    descriptionArticle varchar(1000),
    createdAt timestamp default current_timestamp,
    primary key(id)
);

CREATE TABLE shoppingCart(
    id int auto_increment,
    userId int NOT NULL,
    sellId int NOT NULL,
    sellCant int DEFAULT 1,
    createdAt timestamp default current_timestamp,
    primary key(id),
    foreign key(userId) references user(id),
    foreign key(sellId) references sell(id)
);

CREATE TABLE shoppingCheckout(
    id int auto_increment,
    userId int NOT NULL,
    cardName varchar(50),
    cardNumber int,
    cardExpireMonth varchar(20),
    cardExpireYear int,
    cardCVV int,
    createdAt timestamp default current_timestamp,
    primary key(id),
    foreign key(userId) references user(id)
);

CREATE TABLE userComment(
    id int auto_increment,
    comment varchar(1000),
    createdAt timestamp default current_timestamp,
    primary key(id)
)
