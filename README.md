
# Лабораторна робота 4

## Завдання 1 

Завданням було розробити програму, яка отримує атрибути заданих файлів, маємо:

- Файл 1 - text1.txt, доступний лише для читання
- Файл 2 - text2.txt, прихований
- Файл 3 - 100mb.txt, файл розміром більше 100мб

### результат виконання 1 програми:

#### Файл 1

- Attributes: 33
- Read-only
- Size: 37 bytes
- Creation Time: 7/12/2024 15:38:17
- Last Access Time: 7/12/2024 15:38:17
- Last Write Time: 7/12/2024 15:33:12
- Owner: BUILTIN\Administrators


#### Файл 2

- Attributes: 34
- Hidden
- Size: 23 bytes
- Creation Time: 7/12/2024 15:38:37
- Last Access Time: 7/12/2024 15:38:37
- Last Write Time: 7/12/2024 15:34:46
- Owner: BUILTIN\Administrators


#### Файл 3
- Attributes: 32
- Size: 104857621 bytes
- Creation Time: 7/12/2024 15:35:51
- Last Access Time: 7/12/2024 15:35:52
- Last Write Time: 7/12/2024 15:35:52
- Owner: BUILTIN\Administrators

## Завдання 2
У другій версії програми потрібно було використовувати небуферизоване введення/виведення Windows API
### результат виконання 2 програми:
- Time taken: 0.023000 seconds

## Завдання 3
У третій версії програми потрібно було реалізувати програму, яка виконує асинхронне введення/виведення для обробки декількох файлів одночасно. 
### результат виконання 3 програми:
- Read 37 bytes from text1.txt
- Read 23 bytes from text2.txt
- Read 1024 bytes from 100mb.txt
