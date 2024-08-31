<div>
<a href="https://github.com/iikrllx/notes">
    <img src="https://img.shields.io/badge/Knowledge%20Base--RUS-blue?style=flat&label=%D0%91%D0%B0%D0%B7%D0%B0%20%D0%B7%D0%BD%D0%B0%D0%BD%D0%B8%D0%B9&labelColor=008000">
</a>
<img src="https://img.shields.io/github/repo-size/iikrllx/notes.svg?label=Repo%20size&style=flat">
<a href="https://github.com/iikrllx/notes/blob/master/CONTRIBUTING.md">
    <img src="https://img.shields.io/badge/Welcome-black?style=flat&label=Contributions&labelColor=gray">
</a>
</div>

# Notes
Здесь хранятся мои заметки, которые я составляю многие годы. Мне лень постоянно обращаться к
документации/мануалам, поэтому я делаю короткие записи на будущее. Информация в файлах взята из
книг/статей/документаций, либо я что-то исследовал и решил это записать. Данный репозиторий может
быть полезен русскоязычным **Linux** инженерам. Автор использует последний стабильный выпуск Linux
Debian с x86_64 архитектурой.

Эти заметки я часто перечитываю перед собеседованием, для того чтобы освежить память. В данном
репозитории я не заморачиваюсь с оформлением коммитов (просто ставлю дату), информация здесь
обновляется/добавляется регулярно. В файлах можно увидеть не только русский язык, но и немного
английского.

У меня есть Telegram-[канал](https://t.me/krxnotes), в котором публикуются выборочно некоторые
заметки из данного репозитория (в более современном формате).

## Структура
Языки, Примеры кода и разборы, Теория:
```
languages/bash/
languages/c/
```

GNU, Debian, Linux, Ядро, Операционная система, Память, Сети, Информатика, Система:
```
gnu-and-linux/
```

Шпаргалки, инструменты, утилиты, горячие клавиши, сопровождение пакетов (deb, rpm) и т.д: 
```
cheat-sheets/
```

Смотреть дерево файлов: [README](https://github.com/iikrllx/notes/blob/master/README).

## Оглавление
Оглавление указано в ```текстовых``` файлах (в самом начале файла), пример шаблона:
```
Темы:
* FHS стандарт
* Устройства
* Процесс
* Журналирование
* Разное
```
Затем можно использовать поиск в текстовом редакторе для перехода к самому описанию темы. Обычно в
```vim``` я делаю:
```
/--- FHS стандарт
```
и перехожу к описанию темы.

Можно вывести все оглавления, которые описаны в данных заметках. Это позволит лучше ориентироваться
в файлах:
```
./print-all-topics.sh
```
если в выводе нет какого-то ```txt``` файла, значит в нем ```нет``` подобного оглавления/шаблона и
информация в файле не структурирована.

## Участие
Пожалуйста, ознакомьтесь с
[CONTRIBUTING.md](https://github.com/iikrllx/notes/blob/master/CONTRIBUTING.md) для получения
подробностей о норме поведения проекта и процессе отправки запросов на включение (pull requests).

## Лицензия
Этот проект лицензирован в соответствии с GPLv3 - подробности смотрите в файле
[LICENSE](https://github.com/iikrllx/notes/blob/master/LICENSE).
