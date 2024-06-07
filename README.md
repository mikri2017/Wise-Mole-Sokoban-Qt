# Wise Mole Sokoban Qt
Игра типа сокобан с возможностью редактирования уровней и обмена ими по сети
друг с другом (версия под Qt)

Проект по мотивам игры "Мудрый крот" для Роботландия-98.

### Роли:
* Сервер - хранит уровни игры, позволяет скачивать их по сети другими игроками,
а также, принимает готовые уровни от других.
* Клиент - позволяет играть в скачанный уровень, просматривать и качать новые
уровни с сервера, созданные другими игроками, а также, создавать свои и
отправлять на сервер.

### Используемые технологии
* qtcreator
* qt6-base-dev
* qt6-httpserver-dev
* qt6-websockets-dev
* libqt6sql6-mysql
* [mariadb-server](https://mariadb.org/download/?t=repo-config&d=Debian+12+%22Bookworm%22&v=11.4&r_m=truenetwork)
