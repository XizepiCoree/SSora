# Sora Kick — VST3 плагин для бочки (FL Studio)

Вешается в слот микшера на дорожку с кик-сэмплом и переделывает звук:
от индустриальных кик-ударов до хард-техно / rawstyle.

## Как получить готовый плагин БЕЗ Visual Studio (через GitHub)

Сборку делает бесплатный облачный Windows-компьютер GitHub, вам нужен только аккаунт.

1. Зарегистрируйтесь на github.com (если ещё нет аккаунта).
2. Создайте новый репозиторий: **New repository**, имя любое (например `sora-kick`), **Create repository**.
3. Нажмите **uploading an existing file** и перетащите в окно ВСЁ содержимое
   распакованной папки `SoraKick` (папки `Source`, `.github`, файлы `CMakeLists.txt`, `README.md`).
   Если папка `.github` не загрузилась (она скрытая) — нажмите **Add file → Create new file**,
   в имени файла введите `.github/workflows/build.yml` и вставьте туда содержимое файла `build.yml`.
4. Нажмите **Commit changes**.
5. Откройте вкладку **Actions** — запустится сборка «Build VST3» (около 5–10 минут).
   Если она не запустилась сама: выберите её слева и нажмите **Run workflow**.
6. Когда появится зелёная галочка, откройте запуск и внизу, в разделе **Artifacts**,
   скачайте `SoraKick-VST3`. Распакуйте архив: внутри будет `Sora Kick.vst3`.
7. Скопируйте `Sora Kick.vst3` в `C:\Program Files\Common Files\VST3\`.

## Подключение в FL Studio

1. `Options → Manage plugins → Find installed plugins`.
2. Микшер → дорожка с кик-сэмплом → слот эффекта (▼) → `Sora Kick`.
3. Выберите Character и крутите ручки.

## Что внутри

| Блок | Параметры | Что делает |
|---|---|---|
| Character | список | Выставляет все ручки: Sky Punch, Hard Stomp, Rawstyle, Rumble Wall, Pitch Bender, Crushed 96, Rusty Cannon, Short Click. Custom — ничего не трогает |
| Transient | Attack, Sustain | Усиливает/приглушает удар и хвост |
| Length | Length | Обрезает хвост бочки через заданное время (1000 ms = выкл.) — короткие «stomp»-кики |
| Tone | Sub, Click, Low Cut, High Cut | Сабовый буст (60 Гц), клик (4 кГц), срезы |
| Drive | Drive, Drive Type | Дисторшн с 4x oversampling: Soft / Hard / Fold / Asym |
| Crush | Bits, Rate | Лоу-фай: битовая глубина и понижение частоты дискретизации |
| Screech | Screech, Screech Hz | Резонансный подъём после дисторшна — «визг» хард-киков |
| Sub Layer | Sub Layer, Layer Hz, Layer Decay, Layer Wave | Синтезированный слой (Sine / Triangle / Saw / Square), стартующий от атаки бочки |
| Pitch Drop | Pitch Drop, Drop Time | Падение высоты слоя вниз, до 5 октав — «лазерные» и «пинающие» кики |
| Rumble | Rumble, Rumble Hz | Параллельный сильно перегруженный низ под бочкой |
| Out | Trigger, Mix, Output | Trigger — порог срабатывания слоя и Length (ниже пика бочки); Mix; громкость |

## Своя картинка героини (необязательно)

В интерфейсе нарисована оригинальная героиня. Если хотите свою картинку — положите PNG
с именем `heroine.png` в папку `Resources` (создайте её рядом с `Source`) до загрузки на GitHub.
Лучше вертикальная картинка примерно 240×630 пикселей.

## Заметки

- Задержка плагина (oversampling) сообщается хосту, FL Studio компенсирует её сама.
- Rumble и Pitch Drop работают как синтез/параллельная обработка поверх вашего сэмпла,
  это не питч-шифтинг самого сэмпла.
- JUCE распространяется под AGPLv3 / коммерческой лицензией — для личного использования всё в порядке.
