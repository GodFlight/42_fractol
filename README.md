# 42_fractol

![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandelbrot.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Julia.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandelbrot%2BJulia.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandl%2BJulia%2BBurningship.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Burningship.png)
Многопоточный рендеринг фракталов с использованием фреймворка **"OpenCL"** и библиотеки для работы с OpenGL **"mlx"**.

## Что есть
Рендеринг фракталов: mandelbrot, julia, burning ship, mandelbrot + julia, mandelbrot + julia + burning ship.  
Гладкий градиент цвета.  
Подсчет значений при помощи фреймвока **"OpenCL"**.  

## Компиляция и запуск
Запускается только на **OSX**.  
Скомпилировать исполняемый файл при помощи `make`.  
Запустить его с `./fractol [target_name]`. Возможные фракталы: `mandelbrot`, `julia`, `manjulia`, `mandjuliaburn`, `burningship`.  

## Управление
`ESC` - закрыть программу.  
`NUM`+`1`-`6` - Смена цветов.  
`NUM`+`+`/`-`/`Вращение колеса мыши` - приближение/отдаление.  
`UP` - перемещние фрактала вверх.  
`DOWN` - перемещние фрактала вниз.  
`RIGHT` - перемещение фрактала вправо.  
`LEFT` - перемещение фрактала влево.  
`PAGE UP` - смена фрактала.  
`PAGE DOWN` - смена фрактала.  
`SPACE` - включить/выключить вращение мыши *(только для julia, mandelbrot+julia, mandelbrot+julia+burningship)*.  
`R` - перезапустить фрактал.
