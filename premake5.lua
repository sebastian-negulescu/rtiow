workspace 'raytracer'
    configurations { 'Debug', 'Release' }

project 'raytracer'
    kind 'ConsoleApp' -- could change to WindowedApp in the future
    language 'C++'
    targetdir 'bin/%{ cfg.buildcfg }'

    files { '*.hpp', '*.cpp' }

    filter 'configurations:Debug'
        defines { 'DEBUG' }
        symbols 'On'

    filter 'configurations:Release'
        defines { 'NDEBUG' }
        optimize 'On'