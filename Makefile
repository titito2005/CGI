#Makefile Servidor
#CREATE LOGIN cgi-bin/login
program: clean refreshPublicCGI database user sell session shoppingCart userComment userCommentService sessionService userService sellService parserService shoppingCartService footerView headerView loginView sellView addView logoutView shoppingCartView userCommentView registerView loginCompleto userCommentCompleto sellCompleto logoutCompleto shoppingCartCompleto registerCompleto addCompleto

#VIEWS
loginView: views/loginView/LoginView.cc
	g++ -c views/loginView/LoginView.cc

sellView: views/sellView/SellView.cc
	g++ -c views/sellView/SellView.cc

addView: views/addView/AddView.cc
	g++ -c views/addView/AddView.cc

registerView: views/registerView/RegisterView.cc
	g++ -c views/registerView/RegisterView.cc

footerView: views/footerView/FooterView.cc
	g++ -c views/footerView/FooterView.cc

headerView: views/headerView/HeaderView.cc
	g++ -c views/headerView/HeaderView.cc

logoutView: views/logoutView/LogoutView.cc
	g++ -c views/logoutView/LogoutView.cc

shoppingCartView: views/shoppingCartView/ShoppingCartView.cc
	g++ -c views/shoppingCartView/ShoppingCartView.cc

userCommentView: views/userCommentView/UserCommentView.cc
	g++ -c views/userCommentView/UserCommentView.cc
#MODELS
user: models/userModel/User.cc
	g++ -c models/userModel/User.cc

sell: models/sellModel/Sell.cc
	g++ -c models/sellModel/Sell.cc

session: models/sessionModel/Session.cc
	g++ -c models/sessionModel/Session.cc

shoppingCart: models/shoppingCartModel/ShoppingCart.cc
	g++ -c models/shoppingCartModel/ShoppingCart.cc

userComment: models/userCommentModel/UserComment.cc
	g++ -c models/userCommentModel/UserComment.cc
 
#SERVICES
userService: services/userService/UserService.cc
	g++ -c services/userService/UserService.cc

sellService: services/sellService/SellService.cc
	g++ -std=c++0x -c services/sellService/SellService.cc

parserService: services/parserService/ParserService.cc
	g++ -c services/parserService/ParserService.cc

sessionService: services/sessionService/SessionService.cc
	g++ -c services/sessionService/SessionService.cc

shoppingCartService: services/shoppingCartService/ShoppingCartService.cc
	g++ -c services/shoppingCartService/ShoppingCartService.cc

userCommentService: services/userCommentService/UserCommentService.cc
	g++ -c services/userCommentService/UserCommentService.cc

#DATABASE
database: services/Database.cc
	g++ -c services/Database.cc -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -ldl -lssl -lcrypto

#PUBLIC FILES ON CGI DIRECTION
refreshPublicCGI:
	sudo rm -rf /var/www/html/public
	sudo cp -r public /var/www/html

#PRUEBA LOGIN VIEW (IGNORAR)
loginCompleto: LoginView.o ParserService.o SessionService.o Session.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/login -I/usr/include/mysql LoginView.o ParserService.o Session.o SessionService.o UserService.o User.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -ldl -lssl -lcrypto

sellCompleto: SellView.o ParserService.o SessionService.o Session.o ShoppingCartService.o SellService.o Sell.o ShoppingCart.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/home SellView.o ParserService.o Session.o ShoppingCartService.o SessionService.o SellService.o Sell.o ShoppingCart.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql

addCompleto: AddView.o ParserService.o SessionService.o Session.o  SellService.o Sell.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/addSell AddView.o ParserService.o Session.o SessionService.o SellService.o Sell.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql

registerCompleto: RegisterView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/userRegister RegisterView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql

logoutCompleto: LogoutView.o ParserService.o SessionService.o Session.o Database.o
	sudo g++ -o /var/www/cgi-bin/logout LogoutView.o ParserService.o SessionService.o Session.o Database.o -I/usr/include/mysql -L/usr/lib64/mysql

shoppingCartCompleto: ShoppingCartView.o SellService.o ParserService.o ShoppingCartService.o SessionService.o Session.o Sell.o ShoppingCart.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/cart ShoppingCartView.o SellService.o ParserService.o ShoppingCartService.o SessionService.o Session.o Sell.o ShoppingCart.o UserService.o User.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql

userCommentCompleto: UserCommentView.o UserCommentService.o ParserService.o SessionService.o Session.o UserComment.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /var/www/cgi-bin/comments UserCommentView.o UserCommentService.o ParserService.o  SessionService.o Session.o UserComment.o Database.o HeaderView.o FooterView.o -I/usr/include/mysql -L/usr/lib64/mysql

clean:
	rm -f *.o *.gch