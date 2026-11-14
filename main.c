#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Temel durum degiskenleri
    int saglik = 100, enerji = 100, oksijen = 100;
    int su = 10, yedekParca = 3, modulHasari = 0;
    int kilitMuhurlu = 0; // 0: Acik, 1: Muhurlu
    int gun = 1, tur = 0;

    // Zorluk ayarlari icin degiskenler
    int firtinaTuru = 5;
    int hasarCarpani = 1;
    int kesifFarki = 0;

    // Dongu, zar ve kullanici girisi degiskenleri
    char zorluk, komut, sifre, tahmin;
    int gecerliSecim = 0;
    int oyunDevam = 1;
    int turArttir = 0;
    int zar, esik, miktar, kalanSu, uretilenOksijen;
    int i, hak, sifreDogru;
    int hasarTuruSayisi, kayipSaglik, kayipOksijen, zarar;
    int puan;

    // Rastgele sayi uretimi icin baslangic
    srand(time(NULL));

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU ===\n");
    printf("Kurtarma ekibi gelene kadar 15 gun hayatta kalmalisin!\n\n");

    // 1. ZORLUK SEVIYESI SECIMI
    do {
        printf("Zorluk Secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);

        switch (zorluk) {
            case 'k':
            case 'K':
                su = 15;
                yedekParca = 5;
                firtinaTuru = 3;
                hasarCarpani = 1;
                kesifFarki = 10; // Esigi arttirir, bulma sansi yukselir
                gecerliSecim = 1;
                printf("Kolay seviye secildi.\n");
                break;

            case 'n':
            case 'N':
                su = 10;
                yedekParca = 3;
                firtinaTuru = 5;
                hasarCarpani = 1;
                kesifFarki = 0;
                gecerliSecim = 1;
                printf("Normal seviye secildi.\n");
                break;

            case 'z':
            case 'Z':
                su = 6;
                yedekParca = 2;
                firtinaTuru = 7;
                hasarCarpani = 2; // Hasarlar iki katina cikar
                kesifFarki = -15; // Esigi dusurur, bulma sansi azalir
                gecerliSecim = 1;
                printf("Zor seviye secildi.\n");
                break;

            default:
                printf("Hatali giris! Lutfen sadece K, N veya Z giriniz.\n");
                break;
        }
    } while (gecerliSecim == 0);

    // 2. ANA OYUN DONGUSU
    do {
        turArttir = 0;

        printf("\n--------------------------------------------------\n");
        printf("GUN: %d | TUR: %d | SAGLIK: %d | ENERJI: %d | OKSIJEN: %d\n", gun, tur, saglik, enerji, oksijen);
        printf("SU: %d | PARCA: %d | HASAR: %d | HAVA KILIDI: %d\n", su, yedekParca, modulHasari, kilitMuhurlu);
        printf("Komutlar: [G]esif, [O]ksijen, [T]amir, [D]urum, [U]yu, [K]um Firtinasi, [H]ava Kilidi, [Q]Cikis\n");
        printf("Komut girin: ");
        scanf(" %c", &komut);

        // 3. KOMUT SISTEMI
        switch (komut) {

            // KESIF GOREVI
            case 'g':
            case 'G':
                if (enerji < 15) {
                    printf("Yetersiz enerji! Kesif icin en az 15 enerji lazim.\n");
                    break;
                }
                if (oksijen < 10) {
                    printf("Yetersiz oksijen! Kesif icin en az 10 oksijen lazim.\n");
                    break;
                }

                enerji = enerji - 15;
                oksijen = oksijen - 10;

                // Enerji ve oksijen durumuna gore esik belirleme
                if (enerji > 40 && oksijen > 30) {
                    esik = 60 + kesifFarki;
                } else {
                    esik = 35 + kesifFarki;
                }

                zar = rand() % 100;
                printf("Zar: %d / Esik: %d -> ", zar, esik);

                // En az 3 farkli sonuc: Yedek parca, Su veya Eli bos donme
                if (zar < esik / 2) {
                    printf("BASARILI\n");
                    yedekParca = yedekParca + 2;
                    printf("Kesifte 2 adet yedek parca buldunuz!\n");
                } else if (zar < esik) {
                    printf("BASARILI\n");
                    su = su + 4;
                    printf("Kesifte 4 birim su buldunuz!\n");
                } else {
                    printf("BASARISIZ\n");
                    printf("Hicbir sey bulamadan eli bos dondunuz.\n");
                }

                // Yaralanma kontrolu (zar < 10 || modulHasari > 70)
                zar = rand() % 100;
                printf("Yaralanma Zari: %d / Esik: 10 (veya Hasar > 70) -> ", zar);
                if (zar < 10 || modulHasari > 70) {
                    printf("YARALANDINIZ\n");
                    saglik = saglik - 10;
                    printf("Kesif sirasinda yaralandiniz! Saglik 10 azaldi.\n");
                } else {
                    printf("GUVENLI\n");
                }

                turArttir = 1;
                break;

            // OKSIJEN URETIMI
            case 'o':
            case 'O':
                if (enerji < 10) {
                    printf("Yetersiz enerji! Oksijen uretmek icin en az 10 enerji lazim.\n");
                    break;
                }
                if (su < 2) {
                    printf("Yetersiz su! En az 2 birim su olmali.\n");
                    break;
                }

                printf("Mevcut su: %d. Kullanilacak su miktarini girin: ", su);
                scanf("%d", &miktar);

                if (miktar > su || miktar < 2) {
                    printf("Gecersiz miktar! Mevcut sudan fazla veya 2'den az giremezsiniz.\n");
                    break;
                }

                // Mod operatoru ile tek/cift kontrolu
                kalanSu = miktar % 2;
                miktar = miktar - kalanSu;
                uretilenOksijen = (miktar / 2) * 3;

                su = su - miktar;
                oksijen = oksijen + uretilenOksijen;
                enerji = enerji - 10;

                if (kalanSu == 1) {
                    printf("Girilen miktar tek oldugu icin 1 birim su depoda artik olarak kaldi.\n");
                }
                printf("%d birim su kullanildi, %d birim oksijen uretildi.\n", miktar, uretilenOksijen);

                turArttir = 1;
                break;

            // TAMIR
            case 't':
            case 'T':
                if (enerji < 10) {
                    printf("Yetersiz enerji! Tamir icin en az 10 enerji lazim.\n");
                    break;
                }
                if (yedekParca <= 0) {
                    printf("Yedek parca yok! Tamir yapilamaz.\n");
                    break;
                }
                if (modulHasari == 0) {
                    printf("Modulde hic hasar yok.\n");
                    break;
                }

                // 3 kademeli hasar tamiri
                if (modulHasari <= 30) {
                    yedekParca = yedekParca - 1;
                    modulHasari = modulHasari - 15;
                    enerji = enerji - 10;
                    printf("Hafif hasar tamir edildi (1 parca harcandi, 15 hasar onarildi).\n");
                } else if (modulHasari <= 70) {
                    if (yedekParca < 2) {
                        printf("Orta hasar tamiri icin en az 2 yedek parca lazim!\n");
                        break;
                    }
                    yedekParca = yedekParca - 2;
                    modulHasari = modulHasari - 30;
                    enerji = enerji - 10;
                    printf("Orta hasar tamir edildi (2 parca harcandi, 30 hasar onarildi).\n");
                } else {
                    if (yedekParca < 3) {
                        printf("Agir hasar tamiri icin en az 3 yedek parca lazim!\n");
                        break;
                    }
                    yedekParca = yedekParca - 3;
                    modulHasari = modulHasari - 45;
                    enerji = enerji - 10;
                    printf("Agir hasar tamir edildi (3 parca harcandi, 45 hasar onarildi).\n");
                }

                turArttir = 1;
                break;

            // DURUM RAPORU (Tur arttirmaz)
            case 'd':
            case 'D':
                printf("\n--- DURUM RAPORU ---\n");
                printf("Gun: %d | Tur: %d\n", gun, tur);
                printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
                printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", su, yedekParca, modulHasari);
                printf("Hava Kilidi Durumu: %d (1: Muhurlu, 0: Acik)\n", kilitMuhurlu);

                if (oksijen < 25) {
                    printf("UYARI: Oksijen kritik seviyede (< 25)!\n");
                }
                if (saglik < 30) {
                    printf("UYARI: Saglik kritik seviyede (< 30)!\n");
                }
                if (modulHasari > 70) {
                    printf("UYARI: Modul hasari kritik seviyede (> 70)!\n");
                }

                // Tum degerler guvenli aralikta ise tek kosulla kontrol
                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                break;

            // UYU - DINLEN
            case 'u':
            case 'U':
                enerji = enerji + 25;
                oksijen = oksijen - 10;

                // Ic ice IF: Oksijen 20'nin altindaysa saglik artmaz, azalir
                if (oksijen < 20) {
                    saglik = saglik - 10;
                    printf("Oksijen 20'nin altinda! Uyurken oksijensizlikten 10 saglik kaybettiniz.\n");
                } else {
                    if (saglik < 100) {
                        saglik = saglik + 15;
                        printf("Uyudunuz: Enerji +25, Saglik +15 artti, Oksijen -10 azaldi.\n");
                    } else {
                        printf("Uyudunuz: Enerji +25 artti, Oksijen -10 azaldi.\n");
                    }
                }

                turArttir = 1;
                break;

            // KUM FIRTINASI (FOR DONGUSU ZORUNLU)
            case 'k':
            case 'K':
                if (enerji < 10) {
                    printf("Yetersiz enerji! Firtina onlemleri icin en az 10 enerji lazim.\n");
                    break;
                }
                enerji = enerji - 10;

                hasarTuruSayisi = 0;
                kayipSaglik = 0;
                kayipOksijen = 0;

                printf("\n>>> KUM FIRTINASI BASLADI (%d Tur Surecek) <<<\n", firtinaTuru);

                for (i = 1; i <= firtinaTuru; i++) {
                    zar = rand() % 100;
                    esik = 65;
                    printf("Tur %d - Zar: %d / Esik: %d -> ", i, zar, esik);

                    // Cift turlarda ruzgar siddetlenir, hasar iki katina cikar
                    if (i % 2 == 0) {
                        zarar = 10 * hasarCarpani;
                    } else {
                        zarar = 5 * hasarCarpani;
                    }

                    if (zar < 20) {
                        // Hava kilidi muhurluyse oksijen sizintisi continue ile atlanir
                        if (kilitMuhurlu == 1) {
                            printf("Hava kilidi muhurlu, oksijen sizintisi engellendi!\n");
                            continue;
                        }
                        oksijen = oksijen - zarar;
                        kayipOksijen = kayipOksijen + zarar;
                        hasarTuruSayisi++;
                        printf("Oksijen sizintisi! -%d Oksijen\n", zarar);
                    } else if (zar < 45) {
                        saglik = saglik - zarar;
                        kayipSaglik = kayipSaglik + zarar;
                        hasarTuruSayisi++;
                        printf("Firtina yaralanmasi! -%d Saglik\n", zarar);
                    } else if (zar < esik) {
                        modulHasari = modulHasari + zarar;
                        hasarTuruSayisi++;
                        printf("Modul hasar aldi! +%d Hasar\n", zarar);
                    } else {
                        printf("Firtinadan zararsiz korundunuz.\n");
                    }

                    // Saglik veya oksijen 0'a duserse dongu break ile biter
                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Yasam degerleri tukendi, firtina erken kesildi!\n");
                        break;
                    }
                }

                printf("Firtina Ozeti -> Hasar Alinan Tur: %d | Kayip Saglik: %d | Kayip Oksijen: %d\n",
                       hasarTuruSayisi, kayipSaglik, kayipOksijen);

                turArttir = 1;
                break;

            // HAVA KILIDI SIFRESI (DO-WHILE DONGUSU ZORUNLU)
            case 'h':
            case 'H':
                if (kilitMuhurlu == 1) {
                    printf("Hava kilidi zaten muhurlu!\n");
                    break;
                }
                if (enerji < 15) {
                    printf("Yetersiz enerji! Sifre denemeleri icin en az 15 enerji lazim.\n");
                    break;
                }

                // Gun sayisindan aritmetik olarak sifre uretme
                sifre = 'A' + (gun % 26);
                hak = 3;
                sifreDogru = 0;

                printf("\n--- HAVA KILIDI SIFRE EKRANI ---\n");
                printf("Ipucu: Sifre, alfabede 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);

                do {
                    printf("Kalan hak: %d | Sifre harfini girin (A-Z): ", hak);
                    scanf(" %c", &tahmin);

                    // Kucuk harf girilirse buyuk harfe cevirme
                    if (tahmin >= 'a' && tahmin <= 'z') {
                        tahmin = tahmin - 32;
                    }

                    if (tahmin == sifre) {
                        sifreDogru = 1;
                        kilitMuhurlu = 1;
                        printf("Dogru sifre! Hava kilidi muhurlendi.\n");
                    } else {
                        hak--;
                        enerji = enerji - 5;
                        if (tahmin < sifre) {
                            printf("Yanlis! Enerji 5 azaldi. Ipucu: ileri git.\n");
                        } else {
                            printf("Yanlis! Enerji 5 azaldi. Ipucu: geri git.\n");
                        }
                    }
                } while (sifreDogru == 0 && hak > 0);

                if (sifreDogru == 0) {
                    modulHasari = modulHasari + 20;
                    printf("3 deneme basarisiz! Modul hasari 20 artti.\n");
                }

                turArttir = 1;
                break;

            // CIKIS
            case 'q':
            case 'Q':
                printf("Oyundan cikiliyor...\n");
                oyunDevam = 0;
                break;

            // TANIMSIZ KOMUT
            default:
                printf("Tanimsiz komut!\n");
                break;
        }

        // 4. ZAMAN AKISI VE GUN DEGISIMI
        if (turArttir == 1 && oyunDevam == 1) {
            tur++;
            if (tur % 3 == 0) {
                gun++;
                oksijen = oksijen - 8;
                printf("\n*** YENI GUN (%d. Gun) *** Oksijen 8 azaldi.\n", gun);

                if (modulHasari > 70) {
                    saglik = saglik - 5;
                    printf("*** MODUL HASARI YUKSEK (>70) *** Ek olarak 5 saglik kaybettiniz!\n");
                }
            }
        }

        // 5. SINIRLANDIRMA KONTROLLERI (0 - 100 ARASI)
        if (saglik < 0) saglik = 0;
        if (saglik > 100) saglik = 100;

        if (enerji < 0) enerji = 0;
        if (enerji > 100) enerji = 100;

        if (oksijen < 0) oksijen = 0;
        if (oksijen > 100) oksijen = 100;

        if (modulHasari < 0) modulHasari = 0;
        if (modulHasari > 100) modulHasari = 100;

        // 6. OYUN SONU KONTROLU
        if (oyunDevam == 1) {
            if (saglik <= 0 || oksijen <= 0) {
                printf("\nOYUN KAYBEDILDI! Saglik veya oksijen tukendi.\n");
                oyunDevam = 0;
            } else if (gun > 15) {
                gun = 15;
                printf("\nTEBRIKLER! 15. gunu tamamladiniz ve kurtarma ekibi geldi!\n");
                oyunDevam = 0;
            }
        }

    } while (oyunDevam == 1);

    // 7. SONUC RAPORU VE PUAN
    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n=========== SONUC RAPORU ===========\n");
    printf("Hayatta Kalinan Gun: %d\n", gun);
    printf("Toplam Tur: %d\n", tur);
    printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", su, yedekParca, modulHasari);
    printf("Toplam Puan: %d\n", puan);
    printf("====================================\n");

    return 0;
}
