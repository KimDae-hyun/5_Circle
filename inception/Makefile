COMPOSE = docker-compose -f srcs/docker-compose.yml
DOCKER = -f srcs/requirements/tools/set_docker.sh
SET_WORK = -f srcs/requirements/tools/set_work.sh

all: setup up

install_doc:
	sudo sh $(DOCKER)

setup:
	sudo sh $(SET_WORK)

up:
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

vrm:
	docker volume rm srcs_mariadb
	docker volume rm srcs_wordpress

clean: down
	docker system prune -a

fclean: clean
	rm -rf ~/data

re: fclean all

.PHONY: all install_doc setup up down vrm clean fclean re
