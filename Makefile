#Makefile Servidor
prueba: database user userService main exe2

#EXE
exe: services/userService/main.cc services/userService/UserService.cc models/userModel/User.cc
	g++ services/userService/main.cc services/userService/UserService.cc models/userModel/User.cc -o prueba -L/usr/lib/mysql -lmysqlclient

exe2: main.o Database.o User.o UserService.o
	g++ main.o Database.o User.o UserService.o -o programa -L/usr/lib/mysql -lmysqlclient
#MAIN PRUEBA
main: services/userService/main.cc services/userService/UserService.h models/userModel/User.h
	g++ -c services/userService/main.cc services/userService/UserService.h models/userModel/User.h -L/usr/lib/mysql -lmysqlclient

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
deletePublicCGI:
	sudo rm -rf /var/www/html/public

copyPublicCGI:
	sudo cp -r public /var/www/html

refreshPublicCGI:
	sudo rm -rf /var/www/html/public
	sudo cp -r public /var/www/html

#PRUEBA LOGIN VIEW (IGNORAR)
parser: services/parserService/ParserService.cc services/parserService/ParserService.h
	g++ -c services/parserService/ParserService.cc services/parserService/ParserService.h

login: views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h
	g++ -c views/loginView/LoginView.cc views/loginView/LoginView.h services/parserService/ParserService.h

loginCompleto: LoginView.o ParserService.o
	sudo g++ -o /usr/lib/cgi-bin/login LoginView.o ParserService.o