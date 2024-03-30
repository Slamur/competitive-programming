**Freemarker** - язык для автоматизации скрипта генерации тестов, используемый в Polygon.

Ссылка на [полную документацию](https://freemarker.apache.org/docs/index.html).

Ссылка на базовые примеры доступна на вкладке “Tests”.

## Синтаксис

### Команды

- Пишутся в формате тегов в угловых скобках <>;

  - Многострочная команда требует закрывающий тег, начинающийся со слеша.
  
  - Для закрытия однострочной команды слеш опционален.

- Имена команд начинаются с #;

- Внутри команд можно

  - вызывать другие функции, макросы;
  
  - обращаться к значения переменных и производить арифметические вычисления.

- Обращение к переменным / функциям вне команд - через ${} (не путаем с $ - итератором номера теста)

  ```
  gen -n=${maxN} > $
  ```

### Переменные, литералы, базовые операции

- Присваивание командой assign

  ```
  <#assign variable = value/>
  ```

- Строки - в двойных кавычках ```“Hello”```

- Массивы

  - в квадратных скобках ```[1, 5, 100]```
  
  - непрерывный отрезок - через две точки ```10..15```

- Можно обращаться к уже созданным переменным:

  ```
  <#assign print = hello + ", “ + “World!”/>
  ```

### Цикл for

- Итерация командой list

  ```
  <#list values as value>
  	generate -n=${value} > $
  </#list>
  ```

  - values - значение типа “массив”;

  - Можно делать вложенные циклы

- Переменные могут менять состояние в процессе

  ```
  <#assign iteration = iteration + 1/>
  ```

- [Ссылка](https://freemarker.apache.org/docs/ref_directive_list.html) на документацию.

### Условный оператор if

- [Ссылка](https://freemarker.apache.org/docs/ref_directive_if.html) на документацию.

### Функции

- Вычисляют значение на основе параметров

- Описываются командой function

  ```
  <#function name param1 param2>
  	<#return result>
  </#function>

  ${name(first, second)}
  ```

- [Ссылка](https://freemarker.apache.org/docs/ref_directive_function.html) на документацию

### Макросы

- Являются подпрограммой генерации скрипта;

- Описываются командой macro

  ```
  <#macro name param1 param2>
      generate param1 param2 > $
      generate param2 param1 > $
  </#macro>
  
  <@name 
  	param1 = first
      param2 = second
  >
  ```

  (переводы строк при вызове опциональны)

- [Ссылка](https://freemarker.apache.org/docs/ref_directive_macro.html) на документацию

## Удобные функции

Приведены код функции, а также пример использования.

### Целочисленное деление

```
<#function div a b>
    <#return (a / b)?int>
</#function>

generate -n=${div(maxN, 2)} > $
```

### Минимум и максимум

```
<#function min a b>
    <#return [a, b]?sort?first>
</#function>

<#function max a b>
    <#return [a, b]?sort?last>
</#function>

generate -left=${min(a, b)} -right=${max(a, b)} > $
```

### Возведение в степень

```
<#function pow base power>
    <#assign res = 1/>
    <#list 1..power as it>
        <#assign res = res * base/>
    </#list>
    <#return res>
</#function>

<#assign maxN = 2 * pow(10, 5)/>
```

## Пример полного скрипта для задачи

Предполагается, что входными данными является массив из N целых чисел.

```
<#function div a b>
    <#return (a / b)?int>
</#function>

<#function min a b>
    <#return [a, b]?sort?first>
</#function>

<#function max a b>
    <#return [a, b]?sort?last>
</#function>

<#function pow base power>
    <#assign res = 1/>
    <#list 1..power as it>
        <#assign res = res * base/>
    </#list>
    <#return res>
</#function>

<#assign rand = "gen_rand"/>
<#assign sort = "sorted"/>

<#assign minN = 1/>
<#assign maxN = 3 * pow(10, 5)/>

<#assign minA = -pow(10, 9)/>
<#assign maxA = pow(10, 9)/>

<#assign description = "Small tests"/>

<#assign smallN = 10/>
<#assign smallA = pow(10, 2)/>

<#list minN..smallN as n>
	${rand} -n=${n} -minA=${-smallA} -maxA=${smallA} > $
    ${rand} -n=${n} -minA=${minA} -maxA=${maxA} > $
</#list>

<#assign description = "Large tests"/>

${rand} -n=${maxN} -minA=${minA} -maxA=${maxA} > $
${rand} -n=${maxN} -minA=${maxA} -maxA=${maxA} > $
${rand} -n=${maxN} -minA=${maxA - smallA} -maxA=${maxA} > $
${rand} -n=${maxN} -minA=${minA} -maxA=${minA} > $

${rand} -n=${maxN} -minA=${minA} -maxA=${minA + smallA} > $

${rand} -n=${maxN} -minA=${minA} -maxA=${maxA} | ${sort} > $
${rand} -n=${maxN} -minA=${minA} -maxA=${maxA} | ${sort} --desc > $
```
