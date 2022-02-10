#!/bin/sh

docker-compose down
docker system prune -a

echo '127.0.0.1 daekim.42.fr' >> /etc/hosts
echo '127.0.0.1 www.daekim.42.fr' >> /etc/hosts

echo -e "\033[33mdocker cleaning and domain setting \033[0m\n\n"
