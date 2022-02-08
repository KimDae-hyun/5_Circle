#!bin/bash

if [ ! -d "/var/lib/mysql/wordpress" ]; then

	mysql_install_db

	service mysql start
	mysql -e "CREATE DATABASE IF NOT EXISTS wordpress;\
		CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_USER_PW}';\
		GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';\
		ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PW}';\
		FLUSH PRIVILEGES;"
	#End MariaDB : service stop은 안되는것으로 확인
	mysqladmin -uroot -p${DB_ROOT_PW} shutdown

fi
exec mysqld_safe
