FROM debian:buster

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get -y install curl nginx openssl vim

RUN openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/ST=Gyeonggi/L=Seongnam/O=42Seoul/OU=Gun/CN=localhost" -keyout /etc/ssl/private/inception.key -out /etc/ssl/certs/inception.crt
RUN chmod 777 -R /var/www
RUN chown -R www-data:www-data /var/www/

RUN rm /etc/nginx/sites-available/default
RUN rm /etc/nginx/sites-enabled/default
COPY conf/default /etc/nginx/sites-available/
RUN ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default

ENTRYPOINT ["nginx", "-g", "daemon off;"]
