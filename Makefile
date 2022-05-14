#Makefile Servidor
#CREATE LOGIN cgi-bin/login
login: refreshPublicCGI database user sell userService SellService parserService footerView headerView loginView SellView loginCompleto SellCompleto registerCompleto

#VIEWS
loginView: views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h services/userService/UserService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

SellView: views/SellView/SellView.cc views/SellView/SellView.h services/parserService/ParserService.h services/SellService/SellService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/SellView/SellView.cc views/SellView/SellView.h services/parserService/ParserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

registerView: views/registerView/RegisterView.cc views/registerView/RegisterView.h services/parserService/ParserService.h services/userService/UserService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/registerView/RegisterView.cc views/registerView/RegisterView.h services/parserService/ParserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

footerView: views/footerView/FooterView.cc views/footerView/FooterView.h
	g++ -c views/footerView/FooterView.cc views/footerView/FooterView.h

headerView: views/headerView/HeaderView.cc views/headerView/HeaderView.h
	g++ -c views/headerView/HeaderView.cc views/headerView/HeaderView.h

#MODELS
user: models/userModel/User.cc models/userModel/User.h
	g++ -c models/userModel/User.cc models/userModel/User.h

sell: models/SellModel/Sell.cc models/SellModel/Sell.h
	g++ -c models/SellModel/Sell.cc models/SellModel/Sell.h

#SERVICES
userService: services/userService/UserService.cc services/userService/UserService.h
	g++ -c services/userService/UserService.cc services/userService/UserService.h -L/usr/lib/mysql -lmysqlclient

SellService: services/SellService/SellService.cc services/SellService/SellService.h
	g++ -c services/SellService/SellService.cc services/SellService/SellService.h -L/usr/lib/mysql -lmysqlclient

parserService: services/parserService/ParserService.cc services/parserService/ParserService.h
	g++ -c services/parserService/ParserService.cc services/parserService/ParserService.h

#DATABASE
database: services/Database.cc services/Database.h
	g++ -c services/Database.cc services/Database.h -L/usr/lib/mysql -lmysqlclient

#PUBLIC FILES ON CGI DIRECTION
refreshPublicCGI:
	sudo rm -rf /var/www/html/public
	sudo cp -r public /var/www/html

#PRUEBA LOGIN VIEW (IGNORAR)
loginCompleto: LoginView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/login LoginView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient

SellCompleto: SellView.o ParserService.o SellService.o Sell.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/Sell SellView.o ParserService.o SellService.o Sell.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient

registerCompleto: RegisterView.o ParserService.o UserService.o Sell.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/register RegisterView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient