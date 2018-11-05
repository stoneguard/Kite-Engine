# Kite-Engine
OpenGL 3D C++ Engine

# Install
Download and unzip [__resource__](https://www.dropbox.com/s/ml4oic4xped4zce/resource.zip?dl=0) and 3d party library [__sdk__](https://www.dropbox.com/s/mw9m1jvhl9v9h6p/sdk.zip?dl=0) package(includes debug and release libraries) to root directory. It should looks like this:
* app
* resource
* sdk
* .gitignore
* LICENSE
* README.md

## Supported compilers
* Visual Studio 2015

Launch __app/configure.bat__ in order to configure project. Make sure your configuration proccess completed successfully.

![sdk_found](https://www.dropbox.com/s/saffk7zcb7qgo8e/sdk_found.png?raw=1)

Change directory to __app/build__ directory. It contains all necessary generated files. Launch __app/build/kite.bat__. It sets up essential variables, paths and run Visual Studio IDE with generated solution(_x64_). 
Now you are able to work with project in _Debug_/_Release_ mode by switching corresponding setting.

## Atmospheric scattering

![atm_sctr](https://www.dropbox.com/s/a05c2ogi1g576p5/atmospheric_scattering.png?raw=1)

## Static water mesh

![static_water_mesh](https://www.dropbox.com/s/rhfhvg0h5bax28g/static_water_mesh.png?raw=1)

## Dynamic water mesh

![dynamic_water_mesh](https://www.dropbox.com/s/e8w0mwd36nm43eo/dynamic_water_mesh.png?raw=1)

## Dynamic water lighting

![dynamic_water_lighting](https://www.dropbox.com/s/8bgdma5mttift70/dynamic_water_lighting.png?raw=1)

# Credits
* [OpenGL#1](https://learnopengl.com/Introduction)
* [OpenGL#2](http://ogldev.atspace.co.uk/index.html)
* [Terrain rendering](https://blogs.igalia.com/itoral/2016/10/13/opengl-terrain-renderer-rendering-the-terrain-mesh/)
* [Oreon-Engine](https://github.com/fynnfluegge/oreon-engine)
* [Atmospheric scattering GPU GEMS](https://developer.nvidia.com/gpugems/GPUGems2/gpugems2_chapter16.html)
