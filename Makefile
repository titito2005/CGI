#Makefile Servidor
#VIEWS
loginView: views/loginView/LoginView.cc views/loginView/LoginView.h
	sudo g++ -o /usr/lib/cgi-bin/login views/loginView/LoginView.cc views/loginView/LoginView.h

#MODELS
user: models/userModel/User.cc models/userModel/User.h
	g++ -c models/userModel/User.cc models/userModel/User.h

#SERVICES
userService: services/userService/UserService.cc services/userService/UserService.h
	g++ -c services/userService/UserService.cc services/userService/UserService.h -L/usr/lib/mysql -lmysqlclient

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
parser: services/parserService/ParserService.cc services/parserService/ParserService.h
	g++ -c services/parserService/ParserService.cc services/parserService/ParserService.h

login: views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h services/userService/UserService.h views/headerView/HeaderView.h views/footerView/FooterView.h
	g++ -c views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h views/headerView/HeaderView.h views/footerView/FooterView.h

loginCompleto: LoginView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o
	sudo g++ -o /usr/lib/cgi-bin/login LoginView.o ParserService.o UserService.o User.o Database.o HeaderView.o FooterView.o -L/usr/lib/mysql -lmysqlclient

footer: views/footerView/FooterView.cc views/footerView/FooterView.h
	g++ -c views/footerView/FooterView.cc views/footerView/FooterView.h

header: views/headerView/HeaderView.cc views/headerView/HeaderView.h
	g++ -c views/headerView/HeaderView.cc views/headerView/HeaderView.h