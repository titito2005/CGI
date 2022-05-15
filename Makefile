#Makefile Servidor
#CREATE LOGIN cgi-bin/login
login: refreshPublicCGI database user sell session sessionService userService sellService parserService footerView headerView loginView sellView logoutView loginCompleto sellCompleto logoutCompleto

#VIEWS
loginView: views/loginView/LoginView.cc views/loginView/LoginView.h services/sessionService/SessionService.h services/parserService/ParserService.h services/userService/UserService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/loginView/LoginView.cc views/loginView/LoginView.h services/sessionService/SessionService.h services/parserService/ParserService.h services/userService/UserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

sellView: views/sellView/SellView.cc views/sellView/SellView.h services/parserService/ParserService.h services/sellService/SellService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/sellView/SellView.cc views/sellView/SellView.h services/parserService/ParserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

footerView: views/footerView/FooterView.cc views/footerView/FooterView.h
	g++ -c views/footerView/FooterView.cc views/footerView/FooterView.h

headerView: views/headerView/HeaderView.cc views/headerView/HeaderView.h
	g++ -c views/headerView/HeaderView.cc views/headerView/HeaderView.h

logoutView: views/logoutView/LogoutView.cc views/logoutView/LogoutView.h services/sessionService/SessionService.h services/parserService/ParserService.h
	g++ -c views/logoutView/LogoutView.cc views/logoutView/LogoutView.h services/sessionService/SessionService.h services/parserService/ParserService.h

shoppingCartView: views/shoppingCartView/ShoppingCartView.cc views/shoppingCartView/ShoppingCartView.h services/sessionService/SessionService.h services/parserService/ParserService.h services/sellService/SellService.h services/shoppingCartService/ShoppingCartService.h models/sellModel/Sell.h models/shoppingCartModel/ShoppingCart.h
	g++ -c views/shoppingCartView/ShoppingCartView.cc views/shoppingCartView/ShoppingCartView.h services/sessionService/SessionService.h services/parserService/ParserService.h services/sellService/SellService.h services/shoppingCartService/ShoppingCartService.h models/sellModel/Sell.h models/shoppingCartModel/ShoppingCart.h
#MODELS
user: models/userModel/User.cc models/userModel/User.h
	g++ -c models/userModel/User.cc models/userModel/User.h

sell: models/sellModel/Sell.cc models/sellModel/Sell.h
	g++ -c models/sellModel/Sell.cc models/sellModel/Sell.h

session: models/sessionModel/Session.cc models/sessionModel/Session.h
	g++ -c models/sessionModel/Session.cc models/sessionModel/Session.h

shoppingCart: models/shoppingCartModel/ShoppingCart.cc models/shoppingCartModel/ShoppingCart.h
	g++ -c models/shoppingCartModel/ShoppingCart.cc models/shoppingCartModel/ShoppingCart.h
 
#SERVICES
userService: services/userService/UserService.cc services/userService/UserService.h
	g++ -c services/userService/UserService.cc services/userService/UserService.h -L/usr/lib/mysql -lmysqlclient

sellService: services/sellService/SellService.cc services/sellService/SellService.h
	g++ -c services/sellService/SellService.cc services/sellService/SellService.h -L/usr/lib/mysql -lmysqlclient

parserService: services/parserService/ParserService.cc services/parserService/ParserService.h
	g++ -c services/parserService/ParserService.cc services/parserService/ParserService.h

sessionService: services/sessionService/SessionService.cc services/sessionService/SessionService.h
	g++ -c services/sessionService/SessionService.cc services/sessionService/SessionService.h

shoppingCartService: services/shoppingCartService/ShoppingCartService.cc services/shoppingCartService/ShoppingCartService.h
	g++ -c services/shoppingCartService/ShoppingCartService.cc services/shoppingCartService/ShoppingCartService.h

#DATABASE
database: services/Database.cc services/Database.h
	g++ -c services/Database.cc services/Database.h -L/usr/lib/mysql -lmysqlclient

#PUBLIC FILES ON CGI DIRECTION
refreshPublicCGI:
	sudo rm -rf /var/www/html/public
	sudo cp -r public /var/www/html

#PRUEBA LOGIN VIEW (IGNORAR)
loginCompleto: LoginView.o ParserService.o SessionService.o Session.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/login LoginView.o ParserService.o Session.o SessionService.o UserService.o User.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient

sellCompleto: SellView.o ParserService.o SellService.o Sell.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/home SellView.o ParserService.o SellService.o Sell.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient

logoutCompleto: LogoutView.o ParserService.o SessionService.o Session.o Database.o
	sudo g++ -o /usr/lib/cgi-bin/logout LogoutView.o ParserService.o SessionService.o Session.o Database.o -L/usr/lib/mysql -lmysqlclient

shoppingCartCompleto: ShoppingCartView.o SellService.o ParserService.o ShoppingCartService.o SessionService.o Session.o Sell.o ShoppingCart.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/cart ShoppingCartView.o SellService.o ParserService.o ShoppingCartService.o SessionService.o Session.o Sell.o ShoppingCart.o UserService.o User.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient