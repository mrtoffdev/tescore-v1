# Tescore

A terminal based grading sheet inspector

# [ Structure ]

## Prerequisites

* AES128 (Bundled): https://github.com/kokke/tiny-AES-c

## Structure

```
Tescore
   |
   |--- ./include/
   |      |--- ./sort/
   |      |     |--- ./ranker/ (jovic)
   |      |            |--- ./...
   |      |
   |      |     |--- ./masterlist/ (jerome)
   |      |            |--- ./...
   |      |
   |      |--- ./render/ (toff)
   |      |     |--- ./frame/
   |      |     |--- ./navigation/
   |      |
   |      |--- ./io/ (toff)
   |      |     |--- ./encrypt/
   |      |     |--- ./crud/
   |
   |--- ./tescore.c
```
