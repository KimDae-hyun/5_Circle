#!bin/bash

if  [ ! -f /var/www/wordpress/wp-config.php ]; then 

    wp core --allow-root download --locale=ko_KR --force 
    wp core config --allow-root --dbname=wordpress --dbuser=${DB_USER} --dbpass=${DB_USER_PW} --dbhost=mariadb:3306
    wp core install --allow-root --url=${DOMAIN_NAME} --title='WordPress daekim Inception! Have a Nice Day!!' --admin_user=${WP_ID} --admin_password=${WP_PW}  --admin_email="daekim@student.42seoul.kr" --path='/var/www/wordpress';
    wp user create --allow-root ${WP_USER_ID} usrdaekim@student.42seoul.kr --user_pass=${WP_USER_PW} --role=author 
    
fi

php-fpm7.3 --nodaemonize