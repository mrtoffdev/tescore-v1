cmake_minimum_required(VERSION 3.22)
project(Tescore C)

set(CMAKE_C_STANDARD 99)

add_executable(
        Tescore main.c

        # Struct Models
        include/model/index.h
        include/model/sheet.h
        include/model/subsheet.h include/model/datamodel.h

        # IO
        include/io/io.h
        include/io/crud.c
        include/io/fileops.c
        include/io/lib/aes.c
        include/io/lib/aes.h

        # Navigation
        include/render/navigation/navigation.c
        include/render/navigation/navigation.h

        # ====== Sorting Modules ======

        # Ranker
        include/sort/ranker/module.c

        # Masterlist
        include/sort/masterlist/alphabeticallySort.h
        include/sort/masterlist/alphabeticallySort.c
        include/sort/masterlist/alphaMergeSort.h
        include/sort/masterlist/alphaMergeSort.c

        # Rendering
        include/render/view/auth.c
        include/render/view/render.c
        include/render/view/typeface.c include/sort/ranker/rankerModule.h include/render/view/typeface.h include/utils/cmdlog.c include/utils/cmdlog.h include/model/renderctx.h include/model/safeguard.h)
