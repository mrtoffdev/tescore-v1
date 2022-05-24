cmake_minimum_required(VERSION 3.10)
project(Tescore C)

set(CMAKE_C_STANDARD 99)

add_executable(
        Tescore main.c

        # Struct Models
        include/model/index.h
        include/model/models.h

        # IO
        include/io/io.h
        include/io/crud.c
        include/io/safeguard/safeguard.c
        include/io/lib/aes.c
        include/io/lib/aes.h

        # Navigation
        include/render/navigation/navigation.c
        include/render/navigation/navigation.h

        # ====== Sorting Modules ======

        # Sorting Modules
        include/proc/proc.h
        include/proc/ranker/ranker.c
        include/proc/masterlist/alphaMergeSort.c


        # Rendering
        include/model/renderctx.h
        include/render/view/auth.c
        include/render/view/render.c

        include/utils/cmdlog.c
        include/utils/cmdlog.h

        # File Operations
        include/model/Sheetctx.h
        include/io/safeguard/safeguard.h
)
