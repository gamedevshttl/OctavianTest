# OctavianTest

Для сборки проекта нужны библиотеки SDL http://libsdl.org/download-2.0.php (SDL2, SDL2_image, SDL2_ttf)

## Система виджетов
![](https://github.com/gamedevshttl/OctavianTest/blob/master/Description/Widget%20Class%20Diagramm.JPG)\

SDL helpers
Класс Text - создает текст средствами SDL\
Класс Texture - создает текстуру средствами SDL

Базовый класс виджет (Widget). Содержит контейнер указателей на дочерние виджеты, и содержит данные о позиции.\
В функциях update, render и touch в цикле проходит все дочерние виджеты и вызывает у них эти же фунции.\
\
Класс Label. Наследник виджета. в функции render отрисовывает объект класса Text\
Класс Image. Наследник виджета. в функции render отрисовывает объект класса Texture\
Класс Button. Наследник виджета.\
Содержит текстуры для отображения кнопки в зависимости от состояния. (Нажата, не нажата). Так же текстура мигания.\
Содержит callback для вызова логики.\
\
Класс System. поддержка интерактивности - захват и освобождение активного виджета. Перенаправление touch вызовов к захваченному виджету.\
\
класс ResourceManager. Загрузка json и шрифтов.

## Игровая логика
Главный класс (GamblingMachine). Наследник виджета.\
Содержит объект класса барабана, кнопку и label для отображения fps

Класс Барабана (Drum). Наследник виджета.\
Содержит контейнер слотов барабанов. В функции старт запускает вращение слотов барабанов и 
запускает таймер для поочередной остановки слотов барабанов. 
В функции старт каждому слоту барабана присваивается скорость. 
При выполнении таймера, вызов функции стоп. Для первого слота барабана запускается функция остановки.

Класс Слота Барабана (SlotDrum). Наследник виджета.\
Содержит контейнер слотов. В функции start() запускает вертикальную прокрутку слотов. 
Для всеч слотов присваивается скорость родительского барабана.
При выполнении функции стоп, выполняется поиск длижайшего слота к уровню и при достижении данного уровня, скорость обнуляется. 
Далее запускается таймер, по истечении которого аналогично запскается стоп для следующего слота барабана. 

Класс Слот (Slot). Наследник виджета.\
Содержит объект класса Label. В функции update выполняется вертиакльное перемещение слота в соответствии со скоростью. 
При достижении нижний границы барабана, слот перемещается на верхнюю границу. 
\
\
Классы в описании барабана\
![](https://github.com/gamedevshttl/OctavianTest/blob/master/Description/Drum%20description.JPG)
\
Диаграмма класов\
![](https://github.com/gamedevshttl/OctavianTest/blob/master/Description/Drum%20class%20diagramm.JPG)
\
Диаграмма последовательности\
![](https://github.com/gamedevshttl/OctavianTest/blob/master/Description/Process%20diagram.JPG)
