
# 📜 So_Long Projesi - İşleyiş Analizi

**So_Long**, 42 okullarında geliştirilen 2D oyun projesidir. Oyuncu, harita üzerinde karakteri kontrol ederek tüm toplanabilir öğeleri toplar ve çıkışa ulaşmaya çalışır. Grafik arayüzü için **MiniLibX (MLX)** kullanılır.

---

## 🧠 Genel Program Akışı

1. ✅ Program başlatılır, argümanlar kontrol edilir  
2. 📂 Harita dosyası yüklenir  
3. 🧪 Harita geçerliliği kontrol edilir  
4. 🧱 Oyun yapısı başlatılır, grafikler yüklenir  
5. 🪟 Oyun penceresi oluşturulur  
6. 🎮 Girdi olayları dinlenir  
7. 🚶 Oyuncu hareket eder, nesnelerle etkileşime girer  
8. 🏁 Oyun biter, kaynaklar temizlenir  

---

## 🔍 Detaylı Analiz

### `main.c` - Program Başlangıcı

```c
int main(int argc, char **argv)
{
    // Başlangıç kontrolleri ve oyun başlatma süreci
}
```

**Görevleri:**

- Argüman doğrulama
- Harita dosyasını kontrol etme
- Haritayı yükleyip oyun yapısını başlatma
- Girdi ve pencere olaylarını dinleme
- Grafik döngüsünü başlatma (`mlx_loop()`)

---

### 📄 `read_map()` - Harita Yükleme

```c
char **read_map(char *filename, t_game *game) { ... }
```

**Görevleri:**

- Harita yüksekliği belirlenir (`get_map_size`)
- Bellek tahsisi yapılır
- Harita dosyası açılıp okunur
- Harita genişliği hesaplanır

---

### 🔐 `init_game()` - Harita Doğrulama

```c
void init_game(t_game *game) { ... }
```

**Kontroller:**

- Harita dikdörtgen mi?  
- Duvarlarla çevrili mi?  
- Geçersiz karakter var mı?  
- Toplanabilir, çıkış, oyuncu mevcut mu?  
- **Flood-fill** algoritması ile tüm alanlara erişilebiliyor mu?

---

### 🌊 `flood_fill_recursive()` - Yol Doğrulama

```c
int check_path_validity(t_game *game) { ... }
```

**Amaç:** Oyuncunun tüm toplanabilirleri ve çıkışı erişebildiğini doğrulamak

---

### 🪟 `mlx_init()` ve `mlx_new_window()` - Grafiksel Başlatma

```c
void init_game(t_tame *game) {
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(...);
}
```

- MLX başlatılır
- Harita boyutuna uygun pencere açılır
- Textures yüklenir

---

### 🎨 `load_textures()` - Grafik Yükleme

```c
void load_textures(t_game *game) { ... }
```

XPM dosyaları `mlx_xpm_file_to_image()` ile yüklenir.

---

### 🕹️ `handle_input()` - Klavye Girdisi

```c
int handle_input(int keycode, t_game *game) { ... }
```

- W, A, S, D / ok tuşları ile hareket  
- ESC tuşu ile çıkış  

---

### 🧍 `move_player()` - Oyuncu Hareketi

```c
void move_player(t_game *game, int new_x, int new_y) { ... }
```

- Duvar kontrolü
- Toplanabilir kontrolü
- Çıkış kontrolü
- Harita güncellemesi

---

### 🗺️ `draw_map()` - Harita Çizimi

```c
void draw_map(t_game *game) { ... }
```

- Harita temizlenip tekrar çizilir  
- Oyuncu ve UI elementi eklenir

---

### ❌ `exit_game()` ve `check_exit()` - Oyun Bitişi

- Oyuncu çıkışa ulaştıysa veya pencere kapatıldıysa
- Bellek temizliği yapılır

---

## 💠 Kullanılan MLX Fonksiyonları

| Fonksiyon | Açıklama |
|----------|----------|
| `mlx_init()` | MLX başlatılır |
| `mlx_new_window()` | Yeni pencere oluşturur |
| `mlx_xpm_file_to_image()` | XPM dosyasını imaja çevirir |
| `mlx_put_image_to_window()` | İmajı pencereye çizer |
| `mlx_clear_window()` | Pencereyi temizler |
| `mlx_string_put()` | Yazı çizer |
| `mlx_hook()` | Olay işleyici tanımlar |
| `mlx_loop()` | MLX ana döngüsünü başlatır |
| `mlx_destroy_image()` | İmajı serbest bırakır |
| `mlx_destroy_window()` | Pencereyi yok eder |
| `mlx_destroy_display()` | Bağlamı temizler |

---

## 🧭 İşleyiş Akışı (Flowchart)

<details>
<summary>▶️ Görseli göster</summary>

<img src="so-long-flowchart.svg" alt="So_Long Flowchart" width="100%" />

</details>
