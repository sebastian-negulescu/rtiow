workspace 'raytracer'
    configurations { 'Debug', 'Release' }

project 'raytracer'
    kind 'ConsoleApp' -- could change to WindowedApp in the future
    language 'C++'
    includedirs{ '/usr/bin/include' }
    links{ 'gsl', 'gslcblas' }
    targetdir 'bin/%{ cfg.buildcfg }'

    files { '*.h', '*.cc' }
    cppdialect 'C++11'

    filter 'configurations:Debug'
        defines { 'DEBUG' }
        symbols 'On'

    filter 'configurations:Release'
        defines { 'NDEBUG' }
        optimize 'On'