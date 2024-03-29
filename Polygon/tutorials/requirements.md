## Составные части большинства задач по программированию

- Условие;

- Тесты;

- Эталонное решение;

- Валидатор (программа, проверяющая валидность входных данных);

- Чекер (программа, проверяющая корректность выходных данных).

## Условие задачи

Условие задачи состоит из 5 важных частей:

- Легенда

- Формат входных данных

- Формат выходных данных

- Тестовые примеры

- Пояснения к примерам

### Общая информация (для всех частей условия)

- Доступна **Tex**-разметка;

- Используйте **Tex** для формул, переменных и чисел ($ до и после формулы):

- 10^{15}: $10^{15}$

- a_i: $a_i$

- 1 \le N \le 10^9: $1 \le N \le 10^9$;

- a \ge b: $a \ge b$

- k \cdot 10^5: $k \cdot 10^5$

### Легенда

- Текст без важной для решения задачи информации

Такого текста должно быть не более одного абзаца на 2-3 строки в начале задачи.

Обычно это какой-то вводный абзац для создания “атмосферы”.

- Вся важная информация должна быть четко выделена в условии.

Либо жирный шрифт, либо отдельный абзац, возможно даже капс (если очень нужно обратить внимание).

Также иногда полезно повторить важные детали в конце условия в формальном виде.

- Обязательное наличие формальных описаний

Условие всегда должно содержать описания, по которому можно написать простейшую программу (необязательно эффективную).

**Например**, если описывается какой-то процесс во времени, то фраза “в минуту Т” может означать две вещи:

1. Минуты - целочисленные точки на прямой (по сути в ХХ:00);

1. Минута - это отрезок от ХХ:00 до ХХ:59.

Подобные вещи должны быть прописаны очень четко, а также иметь пример с пояснением.

- Условие не обязано быть формальным, но не надо делать сказку, совсем ничего не приносящую в задачу.

Зачастую в задачах описываются ситуации или процессы, которые легче всего описываются неформально.

Например, можно описать перемещение на плоскости с точки зрения курьера, а не просто материальную точку со странными правилами движения.

В то же время желательно избегать ситуаций, где художественное условие не вносит ничего в постановку задачи, но очень сильно перегружает текст.

- Старайтесь свести необходимость “жизненного опыта” к минимуму.

Не все мыслят так же, как автор(ы) задачи.

Очень частый пример: **индексация**.

В реальной жизни в большинстве ситуаций используется 1-индексация.

В то же время многие языки программирования используют 0-индексацию.

У неопытных участников из-за этого возникает диссонанс и соответствующие вопросы

Зачастую достаточно в одном месте прописать, что индексы от 1 до N (или другой величины), чтобы снять часть вопросов в будущем.

- Любые константы и теоремы из реального мира должны быть четко прописаны

Например, если вы просите вывести названия дня недели, то опишите в условии все возможные варианты.

Лучше в формате, который легко скопировать и вставить в код.

Если описывать долго - должна быть ссылка на соответствующий материал в интернете.

- Примеры в условии опциональны, но зачастую удобны.

Не путать с тестовыми примерами.

Пример зачастую позволяет закрепить формальное (или не очень) описание процесса / формулы.

Стоит рассмотреть возможность использования примера из условия в качестве первого тестового примера.

- Графический контент

Тут все по желанию.

Главное, чтобы изображения не перегрузили основную часть текста.

Можно рассмотреть возможность использования изображений в примечании, указав это явно в условии.

### Формат входных данных

- Описание ввода должно быть максимально формальным и содержать все возможные гарантии на данные.

- Каждый блок данных описывается отдельной строкой или абзацем.

- Хороший формат описания: “в такой-то строке через <разделитель> содержатся (находятся/т.д.)  <данные такие-то> (<ограничения на данные>) <длинное тире> <краткое определение данных>”.

- Краткое определение данных может повторять информацию из легенды - в этом нет ничего страшного.

**Примеры** хороших описаний:

- “В первой строке содержатся два целых числа через пробел $N$ и $K$ $(1 \le N \le 3 \cdot 10^5; N - 1 \le K \le 2 \cdot N)$ - количество перекрестков и дорог в городе”.

- “i-ая дорога задается двумя целыми числами и строкой $F_i$, $T_i$, $S_i$ $(1 \le F, T \le N, F \neq T; 1 \le |S| \le 10)$ - номера перекрестков, которые соединяются дорогой, а также имя дороги.”

- “Гарантируется, что все $S_i$ состоят только из латинских строчных символов”.

- “Гарантируется, что из любого перекрестка можно добраться до любого по заданным дорогам”.

### Формат выходных данных (результата)

- В целом всё аналогично формату входных данных.

- Если есть какие-то строгие правила проверки, то их стоит описать отдельно: “Текст сравнивается с учетом пробелов и переводов строк”.

- Для **вещественного ответа** всегда должна быть указана абсолютная и/или относительная погрешность: “Ответ будет засчитан, если абсолютная и/или относительная погрешность не превышает $10^{-6}$”

- Все варианты результата должны быть прописаны.

**Пример**: если в задаче требуется построить ответ и можно доказать, что он всегда существует.

Есть два способа, как это описать:

1. Прямо так и написать: “Гарантируется / можно показать, что (при заданных ограничениях) ответ всегда существует / единственный / не превышает Х / т.д.”

1. Предложить вариант вывода для отсутствия результата: “Если ответа не существует, то в единственной строке выведите -1.”

### Тестовые примеры

- Тестовые примеры ВСЕГДА должны являться первыми тестами в проверяющей системе.

- Тестовые примеры всегда делаются вручную.

- Все примеры из условия должны быть включены в тестовые примеры (если они соответствуют ограничениям задачи).

- Тестовые примеры являются частью условия, поэтому часть разрешения неопределенностей / крайних случаев может быть возложена на них (но не вся).

- Тестовые примеры должны в большинстве случаев считаться “на бумажке” - не надо делать в примерах массивы размером 20 или строки длиной 50.

- Большие числа тестовые примеры возможны в качестве последних примеров для проверки итогового решения (но они не должны заменять базовые примеры).

### Пояснения к примерам

- Для всех тестов должно быть хотя бы какое-то пояснение.

- Минимум два теста должны иметь очень детальное пояснение со всеми вычислениями и вариантами ответов.

- Пояснения не должны быть единственным источником каких-то важных сведений (но могут дублировать сказанное выше).

## Тесты

### Стандартный порядок тестов

1. Ручные примеры для условия;

1. Ручные мелкие тесты (опционально);

1. Сгенерированные мелкие тесты;

1. Сгенерированные тесты на крайние случаи;

1. Сгенерированные максимальные тесты;

1. Сгенерированные специфичные тесты.

### Общие требования

- (Очень желательно) Используется только латиница.

- Все строки завершаются символом перевода строки (даже последняя).

- В конце строк нет лишних пробелов (если в задаче не требуется обратное).

- Для всех массивов / многострочных текстов обязательно даны количество элементов / строк.

### Тесты в условии

- Должен быть хотя бы один тест (если это позволяет формат задачи).

### Ручные мелкие тесты

- (Очень желательно) Данные тесты не должны содержать тестов на крайние значения;

- Не следует делать руками любые тесты, которые невозможно посчитать “на бумажке”.

- Всегда идут после тестов в условии до всех сгенерированных.

### Генераторы тестов

- Подавляющее большинство тестов должно быть создано с помощью генераторов.

- **Генератор** - программа, выводящая в стандартный поток вывода ровно один тест по набору параметров.

- (Очень желательно) Генератор запускается в системе подготовки задачи (НЕ локально).

- (Очень желательно) Генераторы пишутся на C++ с использованием [testlib.h](https://codeforces.com/testlib).

- Параметры в генератор передаются через командную строку.

- Генераторы могут работать в цепочках; каждый следующий генератор читает и модифицирует вывод предыдущего.

- (Очень желательно) Вместо одного многофункционального генератора лучше делать множество мелких / локализованных и запускать в цепочке.

- Все ограничения задачи должны передаваться в качестве параметров (не должны быть константами в файле).

- В генератор не передается номер теста ни в каком виде.

### Testlib для генерации тестов

- Рандом инициализируется от всей строки параметров.

- Есть методы именования параметров командной строки (opt).

- Есть методы генерации перемешивания, разбиений, перестановок и т.д.

- Есть методы генерации строк по простому регэкспу.

- Есть методы вывода массивов без завершающего пробела.

### Общие рекомендации по генерации

- Случайные генераторы должны принимать все возможные ограничения на область генерации.

- Крайние случаи (минимальные/максимальные значения того или иного ограничения) часто можно сделать через случайные генераторы с правильными параметрами.

- Желательно делать крайние случаи на все ограничения (по возможности).

- Первыми полезно ставить несколько малых тестов различных размеров.

- После малых тестов желательно как можно раньше поставить максимальные тесты, приводящие к TL / ML.

- Для специальных тестов лучше писать отдельные генераторы.

- (Очень желательно) Не следует делать несколько запусков генератора с одинаковыми параметрами, отличающихся только сидом рандома.

### Скрипт генерации (опционально)

- Скрипт генерации - псевдопрограмма, описывающая порядок вызова генераторов.

- По скрипту генерации должно быть возможно понять намерения при создании того или иного теста.

- Чем обобщеннее скрипт для создания группы тестов - тем лучше.

## Эталонное решение и ограничения по времени/памяти

### Эталонное решение

- По сути представляет собой видение того, каким должно быть ожидаемое решение участника.

- Реализуется на одном из ЯП, доступных для участников.

- Используется для генерации ответов на тесты.

- Может использовать следующие оптимизации:

  - буферизованный ввод/вывод;

  - использование примитивных типов вместо ссылочных (объектных);

  - другие оптимизации, являющиеся “обычными” для используемого языка.

- (Очень желательно) Реализуется без применения излишних оптимизаций:

  - прагмы в C++;

  - реализация коллекций на примитивах в Java;

  - посимвольный/побайтовый ввод;

  - дополнительные условные операторы на обход специфичных случаев (если это не влияет на общую асимптотику);

  - другие локальные оптимизации, не являющиеся важными для основной идеи решения.

### Дополнительные решения

- Корректные решения, использующие другой подход (полностью или частично);

  - В том числе решения с другой асимптотикой, но ожидаемым вердиктом ОК.

- Корректные решения на ЯП, отличных от языка эталонного решения.

- Решения с неправильным ответом:

  - неверный подход;

  - ошибка в $\pm 1$;

  - пропуск одного из аспектов решения;

- Решения с превышением ограничений по времени / памяти;

  - “запрещенная” асимптотика с применением излишних оптимизаций;

  - “запрещенная” асимптотика с применением условий на специфичные виды тестов;

  - ввод/вывод без ускорения;

### Ограничения по времени и памяти

- Выставляются независимо по каждому доступному компилятору.

  - Если для языка доступно несколько компиляторов, то можно выбрать один оптимальный и указать это в примечаниях.

- Корректные решения должны заходить **максимум за 0.75** от выставленных ограничений.

  - Эталонное должно заходить максимум за 0.5 от ограничений.

- Неэффективные решения должны заходить **минимум за 2.0** от выставленных ограничений.

  - То есть в идеальном мире отношение неэффективного к эталонному - не менее 4.0.

- (Очень желательно) Ограничения по времени выставляются в целочисленных секундах.

  - При необходимости выставляются дополнительные 0.5 секунд.

- (Очень желательно) Ограничения по памяти выставляются кратно 256 Мб.

  - При необходимости - кратно 2^k Мб (в идеале кратно 32 / 64 / 128)

## Валидатор

- **Валидатор** - программа, проверяющая корректность формата входных данных.

- Все гарантии, указанные в условии, должны обязательно проверяться в валидаторе.

  - Обязательно ограничения на минимальные/максимальные значения (задаются константами в валидаторе).
  
  - Все дополнительные гарантии в формульных ограничениях.
  
  - Все фразы со словами “гарантируется” и аналогами.
  
  - Все гарантии, обусловленные определениями (например, если в задаче даётся дерево, то оно связное по определению).

- Валидатор также проверяет пробельные символы.

  - Отсутствие пробелов в конце строки.
  
  - Перевод после каждой строки.
  
  - Отсутствие лишних данных в конце ввода.

- (Очень желательно) Валидаторы пишутся на C++ с использованием [testlib.h](https://codeforces.com/testlib).

### [Testlib](https://codeforces.com/blog/entry/18426) для валидации тестов

- Входной поток представлен объектом InStream inf.

- inf.readSpace / readEoln / readEof: проверка наличия пробела / перевода строки / конца файла.

- ensuref: проверка условий с форматированным выводом в случае ошибки.

- inf.readInt / readLong: ввод чисел в заданных границах.

- inf.readLine / readWord: ввод строк с проверкой по паттерну.

- inf.readInts / readLongs / readWords: ввод массива данных в одной строке через пробел.

- Для всех операций ввода данных необходимо указывать “имя переменной”.

- setTestCase: указание номера теста для мультитестов.

## Чекер

- **Чекер** - программа, проверяющая корректность ответа участника.

- Чекер принимает через командную строку

  - имя входного файла;
  
  - имя файла с ответом жюри (ожидаемым);
  
  - имя файла с ответом участника (полученным).

- В случае ошибки выбрасывается вердикт:

  - “WA / PE” для ответа участника;
  
  - “CRASH” для ответа жюри.

- (Очень желательно) Чекер пишется по концепции “[readAndCheck](https://codeforces.com/blog/entry/18431)”:

  - Ответ считывается функцией, параметризуемой потоком ввода ответа (жюри / участника).
  
  - Данные ответа вводятся и валидируются (см. про валидаторы).
  
    - Валидация на пробельные символы НЕ используется (если это не является частью задачи).
  
  - Данные проверяются на корректность и соответствие требованиям (подмножество валидации).
  
  - Участник может вывести неверно любую часть ответа - лучше проверять в режиме максимального недоверия.
  
  - Функция возвращает информацию, достаточную для сравнения ответов между собой.
  
  - Функция НЕ проверяет оптимальность ответа.

- Если оба ответа являются валидными и корректными, то они сравниваются между собой.

- В случае несоответствия выбрасывается соответствующий вердикт ошибки.

- При корректном ответе выбрасывается вердикт OK.

- (Очень желательно) Чекеры пишутся на C++ с использованием [testlib.h](https://codeforces.com/testlib).

### [Testlib](https://codeforces.com/blog/entry/18431) для чекеров

- Доступно множество стандартных чекеров.

- Потоки ввода: Instream inf, ans и ouf для ввода, ответа жюри и ответа участника.

- Методы ввода аналогичны используемым в валидаторе.

- Не надо вызывать проверку на пробельные символы.

- quitf: метод потока ввода, завершающий выполнение с заданным вердиктом и форматированным сообщением.

- quitif: аналогично quitf, только завершает при невыполнении условия в первом аргументе.

- ans.quitf/quitif: преобразуют вердикты _wa / _pe в вердикт _fail “под капотом”.
