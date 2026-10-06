#pragma once

// 音階の周波数(Hz)。数字はオクターブ、S は半音上(シャープ)
#define NOTE_REST 0   // 休符

#define NOTE_C3  131
#define NOTE_D3  147
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

// オクターブ3の黒鍵(上のオクターブ3の定義を補う)
#define NOTE_CS3 139
#define NOTE_DS3 156
#define NOTE_FS3 185
#define NOTE_GS3 208
#define NOTE_AS3 233

// ---- ドレミ名の別名 ----
// 書き方: DO4 = 4オクターブ目のド(中央のド)、_S = シャープ、_F = フラット
// 例: ファ# = FA_S4、シ♭ = SI_F4。楽譜の五線の位置は、ト音記号で
//   下の加線のド = DO4、第1線のミ = MI4、第5線のファ = FA5
#define DO3 NOTE_C3
#define RE3 NOTE_D3
#define MI3 NOTE_E3
#define FA3 NOTE_F3
#define SO3 NOTE_G3
#define RA3 NOTE_A3
#define SI3 NOTE_B3

#define DO4 NOTE_C4
#define RE4 NOTE_D4
#define MI4 NOTE_E4
#define FA4 NOTE_F4
#define SO4 NOTE_G4
#define RA4 NOTE_A4
#define SI4 NOTE_B4

#define DO5 NOTE_C5
#define RE5 NOTE_D5
#define MI5 NOTE_E5
#define FA5 NOTE_F5
#define SO5 NOTE_G5
#define RA5 NOTE_A5
#define SI5 NOTE_B5

#define DO6 NOTE_C6
#define RE6 NOTE_D6
#define MI6 NOTE_E6
#define FA6 NOTE_F6
#define SO6 NOTE_G6
#define RA6 NOTE_A6
#define SI6 NOTE_B6

// シャープ(半音上)
#define DO_S3 NOTE_CS3
#define RE_S3 NOTE_DS3
#define FA_S3 NOTE_FS3
#define SO_S3 NOTE_GS3
#define RA_S3 NOTE_AS3

#define DO_S4 NOTE_CS4
#define RE_S4 NOTE_DS4
#define FA_S4 NOTE_FS4
#define SO_S4 NOTE_GS4
#define RA_S4 NOTE_AS4

#define DO_S5 NOTE_CS5
#define RE_S5 NOTE_DS5
#define FA_S5 NOTE_FS5
#define SO_S5 NOTE_GS5
#define RA_S5 NOTE_AS5

#define DO_S6 NOTE_CS6
#define RE_S6 NOTE_DS6
#define FA_S6 NOTE_FS6
#define SO_S6 NOTE_GS6
#define RA_S6 NOTE_AS6

// フラット(半音下)。黒鍵は同じ音なのでシャープの別名
#define RE_F3 NOTE_CS3
#define MI_F3 NOTE_DS3
#define SO_F3 NOTE_FS3
#define RA_F3 NOTE_GS3
#define SI_F3 NOTE_AS3

#define RE_F4 NOTE_CS4
#define MI_F4 NOTE_DS4
#define SO_F4 NOTE_FS4
#define RA_F4 NOTE_GS4
#define SI_F4 NOTE_AS4

#define RE_F5 NOTE_CS5
#define MI_F5 NOTE_DS5
#define SO_F5 NOTE_FS5
#define RA_F5 NOTE_GS5
#define SI_F5 NOTE_AS5

#define RE_F6 NOTE_CS6
#define MI_F6 NOTE_DS6
#define SO_F6 NOTE_FS6
#define RA_F6 NOTE_GS6
#define SI_F6 NOTE_AS6

// 休符のドレミ名はなし。NOTE_REST をそのまま使う
