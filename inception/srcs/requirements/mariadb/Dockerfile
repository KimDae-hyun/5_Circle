FROM debian:buster

RUN apt-get update 
RUN apt-get upgrade -y
RUN apt-get -y install vim mariadb-server procps

COPY ./tools/maria.sh /

RUN chmod 777 /maria.sh 

RUN sed -i 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf

CMD ["/bin/bash", "/maria.sh"]