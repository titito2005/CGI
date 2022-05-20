INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Luis', 'Rojas', 'luiscorreo', 'password');
INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Eduardo', 'Carrillo', 'eduardocorreo', 'password2');
INSERT INTO user (firstName, lastName, email, userPassword) VALUES ('Daniela', 'Rojas', 'danielacorreo', 'password3');
INSERT INTO user (firstName, lastName, email, userPassword, phoneNumber, direction) VALUES ('Daniela', 'Rojas', 'prueba@prueba.com', 'prueba', '8888', 'hola');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Skyrim', '20000', 'La historia de Skyrim se centra en los esfuerzos del personaje, dovahkiin (sangre de dragón), para derrotar a Alduin, un dragón/dovah que, según la profecía, destruirá el mundo. ','http://localhost/public/img/indice.jpeg');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Valorant', '1000', 'Valorant es un videojuego de disparos en primera persona multijugador gratuito desarrollado y publicado por Riot Games.','http://localhost/public/img/indice.jpeg');
INSERT INTO sell (nameArticle, valueArticle, descriptionArticle, img) VALUES ('Witcher', '20000', 'The Witcher tiene lugar en un mundo fantástico medieval y relata la historia de Geralt de Rivia, uno de los pocos brujos restantes (cazadores de monstruos a sueldo, quienes cuentan con poderes sobrenaturales).','http://localhost/public/img/indice.jpeg');

INSERT INTO shoppingCart (userId, sellId) VALUES ('1', '1');
INSERT INTO shoppingCart (userId, sellId) VALUES ('1', '2');