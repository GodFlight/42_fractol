# 42_fractol

![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandelbrot.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Julia.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandelbrot%2BJulia.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Mandl%2BJulia%2BBurningship.png)
![Image alt](https://github.com/GodFlight/42_fractol/raw/master/image/Burningship.png)
Multithreaded rendering of fractals with using the framework **"OpenCL"** and libraries for working with OpenGL **"mlx"**.

## Features
 * Fractal rendering: mandelbrot, julia, burning ship, mandelbrot + julia, mandelbrot + julia + burning ship.  
 * Smooth color gradient.  
 * Counting Values with the framework **"OpenCL"**.  

## Compilling and Launch
Runs only on **OSX**.  
Compile the executable with `make`.  
Run it with `./fractol [target_name]`. Possible fractals: `mandelbrot`, `julia`, `manjulia`, `mandjuliaburn`, `burningship`.  

## Controls
`ESC` - Close the program.  
`NUM`+`1`-`6` - Color change.  
`NUM`+`+`/`-`/`Mouse wheel rotation` - zoom into/zoom out.  
`UP` - Fractal movement up.  
`DOWN` - Fractal movement down.  
`RIGHT` - Fractal movement right.  
`LEFT` - Fractal movement left.  
`PAGE UP` - Fractal change.  
`PAGE DOWN` - Fractal change.  
`SPACE` - Turn on/off mouse rotation *(only for julia, mandelbrot+julia, mandelbrot+julia+burningship)*.  
`R` - Restart fractal.
