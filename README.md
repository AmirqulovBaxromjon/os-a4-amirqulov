# Operatsion tizimlar — 4-topshiriq

Talaba: Amirqulov Bahromjon  
Guruh: SRM002-2  
Yo'nalish: Dasturiy injiniring (Software Engineering), 3-kurs  
Mavzu: Mini Shell (Sodda buyruqlar interpretatori)  

## Tavsif
Ushbu loyiha Operatsion tizimlar fani doirasida C tilida yozilgan sodda buyruqlar interpretatori (Mini Shell) hisoblanadi.

Dastur quyidagi asosiy operatsion tizim tushunchalarini amalda ko'rsatib beradi:
- Jarayonlarni yaratish: fork() tizim chaqiruvi orqali yangi bola jarayon (child process) hosil qilinadi.
- Dasturni yuklash va bajarish: execvp() funksiyasi orqali ko'rsatilgan tizim buyrug'i ishga tushiriladi.
- Jarayonni kutish: waitpid() chaqiruvi orqali ota jarayon bola jarayon o'z ishini yakunlashini kutadi.

Dasturda ichki (built-in) buyruqlar ham mavjud:
- cd <katalog> - joriy katalogni almashtirish (chdir tizim chaqiruvi yordamida)
- help - qisqa yordam ko'rsatish
- exit - dasturni yakunlash

## Kompilyatsiya qilish
Dasturni kompilyatsiya qilish uchun loyiha papkasida quyidagi buyruqni bering:

make

Agar tozalash kerak bo'lsa:

make clean

## Ishga tushirish
Kompilyatsiyadan so'ng dasturni quyidagicha ishga tushiring:

./main

## Ishlashidan namuna

$ ./main
Mini Shell ishga tushdi. Chiqish uchun 'exit' deb yozing.
myshell> ls
Makefile  README.md  main  main.c
myshell> pwd
/home/user/os-a4-amirqulov
myshell> help
Sodda Mini Shell dasturi.
Ichki buyruqlar: cd, help, exit
Boshqa buyruqlar tizim orqali (fork va execvp) bajariladi.
myshell> cd ..
myshell> pwd
/home/user
myshell> exit
Shell dasturi yakunlandi.
