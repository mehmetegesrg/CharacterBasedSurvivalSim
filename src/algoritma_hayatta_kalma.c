#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // toupper ve isdigit fonksiyonları için

// --- DURUM YÖNETİMİ DEĞİŞKENLERİ ---
int saglik;
int enerji;
int yemek;
int siginak;

// Ekranı temizlemek için yardımcı fonksiyon
void ekrani_temizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char komut;
    char cevap; // Yeniden başlama cevabı için

    // Rastgele sayılar için çekirdek
    srand(time(NULL));

    // --- ANA PROGRAM DÖNGÜSÜ (RESTART İÇİN) ---
    // Bu döngü, kullanıcı "Hayır" diyene kadar oyunu tekrar tekrar başlatır.
    while (1) {

        // 1. OYUN DEĞERLERİNİ SIFIRLAMA (BAŞLANGIÇ AYARLARI)
        saglik = 100;
        enerji = 100;
        yemek = 0;
        siginak = 0;
        komut = ' '; // Komutu temizle

        ekrani_temizle(); // Yeni oyun başlarken ekranı temizle
        printf("\n");
        printf("############################################################\n");
        printf("#          KARAKTER TABANLI HAYATTA KALMA OYUNU            #\n");
        printf("############################################################\n");
        printf("#  Vahsi dogadasiniz. Kaynaklariniz sinirli.               #\n");
        printf("#  Amaciniz hayatta kalmak. Basarilar!                     #\n");
        printf("############################################################\n\n");
        printf("Komutlar:\n");
        printf("[A]vlan   : Enerji harcar, yemek bulma sansi vardir.\n");
        printf("[S]iginak : Guvenli yer arar. (Enerjiniz yoksa siginak aranmaz)\n");
        printf("[R]Dinlen : Enerji ve sagligi artirir.\n");
        printf("[E]nvanter: Mevcut durumunuzu gosterir.\n");
        printf("[F]Tehlike: Tehlike dalgasini gosterir. (Saglik ve enerji kaybi yasanir)\n");
        printf("[P]Sifre  : Kilitli sandiklari acmak icin. (Hatali girisler enerji tuketir)\n");
        printf("[Y]emek Ye: Envanterdeki yemegi tuketir (+Enerji).\n");
        printf("[X]Cikis  : Oyunu sonlandirir.\n");

        // --- OYUN TUR DÖNGÜSÜ ---
        do {
            printf("\n--------------------------------\n");
            printf("Saglik: %d | Enerji: %d | Yemek: %d | Siginak: %s\n",
                   saglik, enerji, yemek, siginak ? "VAR" : "YOK");
            printf("Ne yapmak istiyorsunuz? (A/S/R/E/F/P/Y/X): ");

            scanf(" %c", &komut);
            komut = toupper(komut);

            // --- ENERJİ TÜKENME KONTROLÜ ---
            // Enerji 0 ise sadece Dinlen (R), Envanter (E), Çıkış (X) VE Yemek Ye (Y) çalışır.
            if (enerji <= 0 && komut != 'R' && komut != 'E' && komut != 'X' && komut != 'Y') {
                printf("\n>> !!! DIKKAT !!! Enerjiniz tamamen bitti!\n");
                printf(">> Hareket edecek gucunuz yok. Sadece [R] ile dinlenebilir veya [Y] ile yemek yiyebilirsiniz.\n");
                continue; // Döngünün başına dön, switch'e girme
            }

            // --- KOMUT SİSTEMİ ---
            switch (komut) {

                case 'A': // AVLANMA
                    printf(">> Avlanmaya ciktiniz...\n");
                    if (enerji >= 20) {
                        enerji -= 20;
                        int sans = rand() % 100;
                        if (sans < 60) {
                            yemek++;
                            printf(">> BASARILI! Tavsan yakaladiniz. (+1 Yemek)\n");
                        } else {
                            if (rand() % 2 == 0) {
                                saglik -= 10;
                                printf(">> BASARISIZ! Avlanirken ayaginiz kaydi. (-10 Saglik)\n");
                            } else {
                                printf(">> BASARISIZ! Hicbir sey bulamadiniz.\n");
                            }
                        }
                    } else {
                        printf(">> UYARI: Avlanmak icin cok yorgunsunuz! (Gereken Enerji: 20)\n");
                    }
                    break;

                case 'S': // SIĞINAK ARAMA
                    if (siginak == 1) {
                        printf(">> Zaten guvenli bir siginaginiz var.\n");
                    } else if (enerji >= 15) {
                        enerji -= 15;
                        printf(">> Siginak araniliyor...\n");
                        int bulmaSansi = rand() % 2;
                        if (bulmaSansi == 1 && siginak == 0) {
                            siginak = 1;
                            printf(">> MUKEMMEL! Bir magara buldunuz ve yerlestiniz.\n");
                        } else {
                            printf(">> Maalesef uygun bir yer bulamadiniz.\n");
                        }
                    } else {
                        printf(">> UYARI: Aramak icin enerjiniz yetersiz.\n");
                    }
                    break;

                case 'E': // ENVANTER
                    ekrani_temizle();
                    printf("\n");
                    printf("============================================================\n");
                    printf("                 KARAKTER DURUM RAPORU                      \n");
                    printf("============================================================\n");
                    printf(" SAGLIK DURUMU   : [ %3d / 100 ]\n", saglik);
                    printf(" ENERJI SEVIYESI : [ %3d / 100 ]\n", enerji);
                    printf(" YEMEK STOGU     : [ %3d Adet  ]\n", yemek);
                    printf(" BARINMA DURUMU  : [ %s ]\n", siginak ? "GUVENLI SIGINAK" : "ACIK ARAZI (Tehlikeli)");
                    printf("============================================================\n");
                    printf("\nDevam etmek icin bir komut giriniz...\n");
                    break;

                case 'R': // DİNLENME
                    printf(">> Dinlenmeye cekildiniz...\n");
                    if (siginak == 1) {
                        enerji += 30;
                        saglik += 20;
                        printf(">> Siginakta güvenli bir sekilde uyudunuz. (Enerji+++, Saglik++)\n");
                    } else {
                        enerji += 15;
                        saglik += 5;
                        printf(">> Disarida, tetikte uyudunuz. (Enerji+, Saglik+)\n");
                    }
                    if (enerji > 100) enerji = 100;
                    if (saglik > 100) saglik = 100;
                    break;

                case 'F': // TEHLİKE (FOR DÖNGÜSÜ)
                    printf("\n!!! TEHLIKE DALGASI YAKLASIYOR !!!\n");
                    int toplamHasar = 0;
                    for (int i = 1; i <= 3; i++) {
                        int anlikHasar = rand() % 15;
                        if (siginak == 1 && anlikHasar > 5) anlikHasar -= 5;

                        toplamHasar += anlikHasar;
                        saglik -= anlikHasar;
                        enerji -= 5; // Yorulma etkisi
                        if (enerji < 0) enerji = 0;

                        printf("Dalga %d: Saldiri geldi! %d hasar. (-5 Enerji)\n", i, anlikHasar);

                        if (saglik <= 0) break; // Ölürse döngüden çık
                    }
                    printf(">> Tehlike gecti. Toplam hasar: %d\n", toplamHasar);
                    break;

                case 'P': // ŞİFRE (DO-WHILE)
                    {
                        char tampon[20]; // Girdiyi önce string olarak alacağız
                        int girilenSifre = 0;
                        int dogruSifre = 1881;
                        int vazgecildi = 0; // İptal durumu kontrolü

                        printf("\n>> Kilitli bir sandik buldunuz.\n");
                        do {
                            printf("Sifreyi girin (4 haneli) veya [G] ile ana menuye donun: ");
                            scanf("%s", tampon); // Girdiyi string olarak oku

                            // 'G' veya 'g' kontrolü
                            if (tampon[0] == 'G' || tampon[0] == 'g') {
                                printf(">> Sifre girisi iptal edildi. Ana menuye donuluyor.\n");
                                vazgecildi = 1;
                                break; // Döngüden çık
                            }

                            // Girilen string sayı mı kontrol et
                            int sayiMi = 1;
                            for(int k=0; tampon[k] != '\0'; k++) {
                                if(!isdigit(tampon[k])) {
                                    sayiMi = 0;
                                    break;
                                }
                            }

                            if(sayiMi == 0) {
                                printf(">> HATA: Sadece rakam girebilir veya 'G' ile iptal edebilirsiniz!\n");
                                continue;
                            }

                            girilenSifre = atoi(tampon);

                            if (girilenSifre != dogruSifre) {
                                if (enerji > 0) {
                                    enerji -= 5;
                                    if (enerji < 0) enerji = 0; // Eksiye düşmeyi engelle
                                    printf(">> HATALI SIFRE! Enerjiniz Azaldi, Yeni enerjiniz: %d/100\n", enerji);
                                }

                                // Enerji 0 ise döngüden at
                                if (enerji <= 0) {
                                     printf(">> Enerjiniz tamamen tukendi! Kilit denemeye gucunuz kalmadi.\n");
                                     break;
                                }
                            }

                        } while (girilenSifre != dogruSifre);

                        if (!vazgecildi && girilenSifre == dogruSifre) {
                            printf(">> SIFRE DOGRU! +3 Yemek kazandiniz!\n");
                            yemek += 3;
                        } else if (!vazgecildi && enerji <= 0) {
                             printf(">> Sandik acilamadi.\n");
                        }
                    }
                    break;

                case 'Y': // YEMEK YE
                    if (yemek > 0) {
                        yemek--;
                        enerji += 25;
                        if (enerji > 100) enerji = 100;
                        printf(">> Yemek yediniz. (-1 Yemek, +25 Enerji)\n");
                    } else {
                        printf(">> UYARI: Cantanizda hic yiyecek yok!\n");
                    }
                    break;

                case 'X': // ÇIKIŞ
                    printf(">> Oyundan cikis yapiliyor...\n");
                    return 0; // Programı direkt kapat

                default:
                    printf(">> Gecersiz komut!\n");
            }

            // --- ÖLÜM KONTROLÜ VE YENİDEN BAŞLATMA ---
            if (saglik <= 0) {
                printf("############################################################\n");
                printf("#                   OYUN BITTI - HAYATTA KALAMADINIZ       #\n");
                printf("############################################################\n");

                // Kullanıcıya sor
                printf("Oyuna tekrar bastan baslamak ister misiniz? (E/H): ");
                scanf(" %c", &cevap);

                if (toupper(cevap) == 'E') {
                    printf(">> Oyun yeniden baslatiliyor...\n");
                    break; // İçteki oyun döngüsünü kır -> En dıştaki while(1) döngüsünün başına atar
                } else {
                    printf(">> Oyun kapatiliyor. Gorusmek uzere!\n");
                    return 0; // Programı sonlandır
                }
            }

        } while (komut != 'X');
    }

    return 0;
}
