# Mars Kolonisi Yaşam Destek Simülatörü

C programlama dilinin temel kontrol yapıları (`if-else`, `switch-case`, `for`, `do-while`) kullanılarak geliştirilmiş metin tabanlı hayatta kalma simülasyonudur.

## Projenin Amacı
Oyuncu, Mars'taki bir araştırma istasyonunda tek başına kalan bir mühendisi yöneterek kurtarma ekibi gelene kadar **15 gün** boyunca hayatta kalmaya çalışır. Simülasyon boyunca sağlık, enerji, oksijen, su, yedek parça ve modül hasarı gibi kaynakların dengeli bir şekilde yönetilmesi gerekir.

## Zorluk Seviyeleri
Program başlangıcında üç farklı zorluk seviyesinden biri seçilir:
* **K (Kolay):** Yüksek başlangıç kaynakları, kısa süren kum fırtınaları ve yüksek keşif şansı.
* **N (Normal):** Standart başlangıç kaynakları ve dengeli oyun koşulları.
* **Z (Zor):** Düşük başlangıç kaynakları, uzun ve yüksek hasarlı kum fırtınaları, düşük keşif şansı.

## Komut Listesi
Tüm komutlar büyük/küçük harf duyarsız olarak çalışır:
* **`G` (Keşif):** Enerji ve oksijen harcayarak su veya yedek parça arar; yaralanma riski taşır.
* **`O` (Oksijen Üret):** Mevcut sudan (`2 birim su -> 3 birim oksijen`) oksijen üretir.
* **`T` (Tamir):** Yedek parça kullanarak modül hasarını hasar seviyesine göre kademeli olarak onarır.
* **`D` (Durum Raporu):** Mevcut kaynakları ve kritik uyarıları gösterir (tur harcamaz).
* **`U` (Uyu / Dinlen):** Enerji ve sağlığı yeniler, oksijen tüketir.
* **`K` (Kum Fırtınası):** Zorluk seviyesine bağlı tur sayısı boyunca süren kum fırtınasını simüle eder.
* **`H` (Hava Kilidi Şifresi):** Güne bağlı olarak üretilen harf şifresini 3 deneme hakkı içinde çözerek hava kilidini mühürler.
* **`Q` (Çıkış):** Simülasyonu sonlandırır ve sonuç raporunu ekrana yazdırır.

## Derleme ve Çalıştırma
Projeyi yerel bilgisayarınızda GCC derleyicisi ile derleyip çalıştırmak için:

```bash
gcc main.c -o mars_simulatoru
./mars_simulatoru
```
