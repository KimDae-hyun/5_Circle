FROM debian:buster

RUN apt-get update 
RUN apt-get upgrade -y
RUN apt-get -y install vim mariadb-client php7.3-fpm php-mysql\
   wget curl php-xml php-cli php-mbstring

RUN	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN	chmod +x wp-cli.phar
RUN	mv wp-cli.phar /usr/local/bin/wp

RUN sed -i 's/\/run\/php\/php7.3-fpm.sock/0.0.0.0:9000/g' /etc/php/7.3/fpm/pool.d/www.conf

RUN mkdir -p /var/www/wordpress 
RUN chown -R  www-data:www-data /var/www/wordpress/
RUN chmod 777 /var/www/wordpress/
RUN mkdir -p /run/php/

COPY ./tools/wordpress.sh /
RUN chmod 777 /wordpress.sh
WORKDIR /var/www/wordpress

ENTRYPOINT ["/bin/bash", "/wordpress.sh"]