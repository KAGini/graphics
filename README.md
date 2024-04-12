# Простая 3D-графика
![photo](https://github.com/KAGini/graphics/assets/105926821/86c60701-046a-4f6d-a35a-f1028fb49362)
# Начало работы
1 Клонирование репозитория <br />
```git clone https://github.com/KAGini/graphics.git; cd graphics``` <br />
```git switch 3d-graphics```<br />
2 Создайте файла config.txt `touch config.txt`<br />
3 Конфигурация<br />
**Цвета задаются в формате RGB и значениями от 0 до 1**<br />
`bgr bgg bgb` - 1 строчка файла, цвет фона, например `0.5 0.5 0` - желтый<br />
Далее идет создание объектов<br />
`sphere` - ключевое слово для создания сферы<br />
`x y z` - координаты центра<br />
`r` - радиус<br />
`r g b` - цвет<br />
или <br />
`light` - ключевое слово для создания источника света<br />
`x y z` - его координаты<br />
4. Запуск<br />
`chmod +x run.sh`<br />
`./run.sh`
