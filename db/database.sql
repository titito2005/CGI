CREATE TABLE user(
    id int auto_increment,
    firstName varchar(100),
    lastName varchar(100),
    email varchar(100),
    userPassword varchar(100),
    createdAt timestamp default current_timestamp,
    primary key(id)
);