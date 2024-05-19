# Metin İşleyici

## Proje Ekibi

- [Moataz Armash] [https://github.com/moataz-armash]
- [Enes Samet Aydı] [https://github.com/ESA19]

## Amaç

Bu proje, libfdr kütüphanesini kullanarak C dilinde metin dosyalarını işleme yeteneğini göstermeyi amaçlamaktadır. Program, giriş dosyasından komutları okur ve bu komutları işleyerek metin verilerini manipüle eder ve belirli bir çıkış dosyası üretir.

## İçerik

- Kaynak dosyalar: `odev.c`, `jval.c`, `dllist.c`, `fields.c`
- Kütüphaneler: `libfdr.a`
- Makefile
- README.md
- Örnek giriş ve çıkış dosyaları: `giris.dat`, `cikis.dat`

## Derleme Talimatları

Programı derlemek için terminalde aşağıdaki komutu çalıştırın:

```bash
make
```

## Çalıştırma Talimatları

```bash
./odev.c giris.dat
```
