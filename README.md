# Есть пробитие (Team3)

В этом репозитории содержится проект выполняемый во время курсов от компании Wargaming

# Участники

Егор Быченок ([github.com/egorix2000](https://github.com/egorix2000))

Елизавета Тесля ([github.com/benninoda](https://github.com/benninoda))

Майя Шевко ([github.com/mshevko](https://github.com/mshevko))

# Язык

C++

# Менеджер зависимостей

В проекте используется менеджер зависимостей [Conan](https://docs.conan.io/en/latest/).

Для корректной подрузки зависимостей надо также добавить [Bincrafters repo](https://bincrafters.github.io)

```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

Перед сборкой проекта необходимо из папки cmake-build-debug выполнить

```
conan install ..
```

Для получения большей информации перейдите в [Conan getting started](https://docs.conan.io/en/latest/getting_started.html)

