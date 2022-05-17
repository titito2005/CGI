INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Luis', 'Rojas', 'luiscorreo', 'password');
INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Eduardo', 'Carrillo', 'eduardocorreo', 'password2');
INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Daniela', 'Rojas', 'danielacorreo', 'password3');
INSERT INTO user (firstName, lastName, email, userPassword, phoneNumber, direction) VALUES ('Daniela', 'Rojas', 'prueba@prueba.com', 'prueba', '8888', 'hola');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Zapatos', '1000', 'estos son unos zapatos talla 44','/home/elvis/proyecto/CGI/public/img/index.jpeg');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Zapatos2', '1000', 'estos son unos zapatos talla 45','/home/elvis/proyecto/CGI/public/img/index.jpeg');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Zapatos3', '1000', 'estos son unos zapatos talla 41','/home/elvis/proyecto/CGI/public/img/index.jpeg');

INSERT INTO shoppingCart (userId, sellId) VALUES ('1', '1');
INSERT INTO shoppingCart (userId, sellId) VALUES ('1', '2');