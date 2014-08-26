#pragma once
#include "SDL_scancode.h"

enum TipoBotaoMouse
{
	BOTAO_ESQ,
	BOTAO_MEIO,
	BOTAO_DIR,
	NUMERO_DE_BOTOES_MOUSE
};

enum TipoToque
{
	TOQUE_PRESSIONOU,
	TOQUE_SOLTOU,
	TOQUE_MOVEU
};

enum TipoBotaoJoystick
{
	BOTAO_1,
	BOTAO_2,
	BOTAO_3,
	BOTAO_4,
	BOTAO_5,
	BOTAO_6,
	BOTAO_7,
	BOTAO_8,
	BOTAO_9,
	BOTAO_10,
	BOTAO_11,
	BOTAO_12,
	NUMERO_DE_BOTOES_JOYSTICK
};

enum TipoTecla
{
    TECLA_DESCONHECIDA = SDL_SCANCODE_UNKNOWN,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /*@{*/

    TECLA_A = SDL_SCANCODE_A,
    TECLA_B = SDL_SCANCODE_B,
    TECLA_C = SDL_SCANCODE_C,
    TECLA_D = SDL_SCANCODE_D,
    TECLA_E = SDL_SCANCODE_E,
    TECLA_F = SDL_SCANCODE_F,
    TECLA_G = SDL_SCANCODE_G,
    TECLA_H = SDL_SCANCODE_H,
    TECLA_I = SDL_SCANCODE_I,
    TECLA_J = SDL_SCANCODE_J,
    TECLA_K = SDL_SCANCODE_K,
    TECLA_L = SDL_SCANCODE_L,
    TECLA_M = SDL_SCANCODE_M,
    TECLA_N = SDL_SCANCODE_N,
    TECLA_O = SDL_SCANCODE_O,
    TECLA_P = SDL_SCANCODE_P,
    TECLA_Q = SDL_SCANCODE_Q,
    TECLA_R = SDL_SCANCODE_R,
    TECLA_S= SDL_SCANCODE_S,
	TECLA_T = SDL_SCANCODE_T,
    TECLA_U = SDL_SCANCODE_U,
    TECLA_V = SDL_SCANCODE_V,
    TECLA_W = SDL_SCANCODE_W,
    TECLA_X = SDL_SCANCODE_X,
    TECLA_Y = SDL_SCANCODE_Y,
    TECLA_Z = SDL_SCANCODE_Z,

    TECLA_1 = SDL_SCANCODE_1,
    TECLA_2 = SDL_SCANCODE_2,
    TECLA_3 = SDL_SCANCODE_3,
    TECLA_4 = SDL_SCANCODE_4,
    TECLA_5 = SDL_SCANCODE_5,
    TECLA_6 = SDL_SCANCODE_6,
    TECLA_7 = SDL_SCANCODE_7,
    TECLA_8 = SDL_SCANCODE_8,
    TECLA_9 = SDL_SCANCODE_9,
    TECLA_0 = SDL_SCANCODE_0,

    TECLA_ENTER = SDL_SCANCODE_RETURN,
    TECLA_ESC = SDL_SCANCODE_ESCAPE,
    TECLA_VOLTAR = SDL_SCANCODE_BACKSPACE,
    TECLA_TAB = SDL_SCANCODE_TAB,
    TECLA_ESPACO = SDL_SCANCODE_SPACE,
	
    TECLA_MENOS = SDL_SCANCODE_MINUS,
    TECLA_IGUAL = SDL_SCANCODE_EQUALS,
    TECLA_COLCHETE_ESQ = SDL_SCANCODE_LEFTBRACKET,
    TECLA_COLCHETE_DIR = SDL_SCANCODE_RIGHTBRACKET,
    TECLA_BARRA_INVERTIDA = SDL_SCANCODE_BACKSLASH, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    TECLA_NONUSHASH = SDL_SCANCODE_NONUSHASH, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate SDL_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    TECLA_PONTO_E_VIRGULA = SDL_SCANCODE_SEMICOLON,
    TECLA_APOSTROFO = SDL_SCANCODE_APOSTROPHE,
    TECLA_CRASE = SDL_SCANCODE_GRAVE, /**< Located in the top left corner (on both ANSI
                              *
							  and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    TECLA_VIRGULA = SDL_SCANCODE_COMMA,
    TECLA_PONTO = SDL_SCANCODE_PERIOD,
    TECLA_BARRA = SDL_SCANCODE_SLASH,

    TECLA_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,

    TECLA_F1 = SDL_SCANCODE_F1,
    TECLA_F2 = SDL_SCANCODE_F2,
    TECLA_F3 = SDL_SCANCODE_F3,
    TECLA_F4 = SDL_SCANCODE_F4,
    TECLA_F5 = SDL_SCANCODE_F5,
    TECLA_F6 = SDL_SCANCODE_F6,
    TECLA_F7 = SDL_SCANCODE_F7,
    TECLA_F8 = SDL_SCANCODE_F8,
    TECLA_F9 = SDL_SCANCODE_F9,
    TECLA_F10 = SDL_SCANCODE_F10,
    TECLA_F11 = SDL_SCANCODE_F11,
    TECLA_F12 = SDL_SCANCODE_F12,

    TECLA_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
    TECLA_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
    TECLA_PAUSE = SDL_SCANCODE_PAUSE,
    TECLA_INSERT = SDL_SCANCODE_INSERT, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    TECLA_HOME = SDL_SCANCODE_HOME,
    TECLA_PAGEUP = SDL_SCANCODE_PAGEUP,
    TECLA_DELETE = SDL_SCANCODE_DELETE,
    TECLA_END = SDL_SCANCODE_END,
    TECLA_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
    TECLA_DIR = SDL_SCANCODE_RIGHT,
    TECLA_ESQ = SDL_SCANCODE_LEFT,
    TECLA_BAIXO = SDL_SCANCODE_DOWN,
    TECLA_CIMA = SDL_SCANCODE_UP,

    TECLA_NUMLOCK_OR_CLEAR = SDL_SCANCODE_NUMLOCKCLEAR, /**< num lock on PC, clear on Mac keyboards
                                     */
    TECLA_KP_DIVIDIR = SDL_SCANCODE_KP_DIVIDE,
    TECLA_KP_MULTIPLICAR = SDL_SCANCODE_KP_MULTIPLY,
    TECLA_KP_MENOS = SDL_SCANCODE_KP_MINUS,
    TECLA_KP_MAIS = SDL_SCANCODE_KP_PLUS,
    TECLA_KP_ENTER = SDL_SCANCODE_KP_ENTER,
    TECLA_KP_1 = SDL_SCANCODE_KP_1,
    TECLA_KP_2 = SDL_SCANCODE_KP_2,
    TECLA_KP_3 = SDL_SCANCODE_KP_3,
    TECLA_KP_4 = SDL_SCANCODE_KP_4,
    TECLA_KP_5 = SDL_SCANCODE_KP_5,
    TECLA_KP_6 = SDL_SCANCODE_KP_6,
    TECLA_KP_7 = SDL_SCANCODE_KP_7,
    TECLA_KP_8 = SDL_SCANCODE_KP_8,
    TECLA_KP_9 = SDL_SCANCODE_KP_9,
    TECLA_KP_0 = SDL_SCANCODE_KP_0,
    TECLA_KP_PONTO = SDL_SCANCODE_KP_PERIOD,

    TECLA_NONUS_BARRA_INVERTIDA = SDL_SCANCODE_NONUSBACKSLASH, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    TECLA_APLICACAO = SDL_SCANCODE_APPLICATION, /**< windows contextual menu, compose */
    TECLA_POWER = SDL_SCANCODE_POWER, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    TECLA_KP_IGUAL = SDL_SCANCODE_KP_EQUALS,
    TECLA_F13 = SDL_SCANCODE_F13,
    TECLA_F14 = SDL_SCANCODE_F14,
    TECLA_F15 = SDL_SCANCODE_F15,
    TECLA_F16 = SDL_SCANCODE_F16,
    TECLA_F17 = SDL_SCANCODE_F17,
    TECLA_F18 = SDL_SCANCODE_F18,
    TECLA_F19 = SDL_SCANCODE_F19,
    TECLA_F20 = SDL_SCANCODE_F20,
    TECLA_F21 = SDL_SCANCODE_F21,
    TECLA_F22 = SDL_SCANCODE_F22,
    TECLA_F23 = SDL_SCANCODE_F23,
    TECLA_F24 = SDL_SCANCODE_F24,
    TECLA_EXECUTAR = SDL_SCANCODE_EXECUTE,
    TECLA_AJUDA = SDL_SCANCODE_HELP,
    TECLA_MENU = SDL_SCANCODE_MENU,
    TECLA_SELECIONAR = SDL_SCANCODE_SELECT,
    TECLA_PARAR = SDL_SCANCODE_STOP,
    TECLA_REPETIR = SDL_SCANCODE_AGAIN,   /**< redo */
    TECLA_DESFAZER = SDL_SCANCODE_UNDO,
    TECLA_RECORTAR = SDL_SCANCODE_CUT,
    TECLA_COPIAR = SDL_SCANCODE_COPY,
    TECLA_COLAR = SDL_SCANCODE_PASTE,
    TECLA_PROCURAR = SDL_SCANCODE_FIND,	//	OBS: eu sei que find = achar, mas (Ctrl + F = procurar)
    TECLA_MUDO = SDL_SCANCODE_MUTE,
    TECLA_MAIS_VOLUME = SDL_SCANCODE_VOLUMEUP,
    TECLA_MENOS_VOLUME = SDL_SCANCODE_VOLUMEDOWN,
/* not sure whether there's a reason to enable these */
/*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    TECLA_KP_VIRGULA = SDL_SCANCODE_KP_COMMA,
    TECLA_KP_IGUAL_AS400 = SDL_SCANCODE_KP_EQUALSAS400,

    TECLA_INTERNACIONAL1 = SDL_SCANCODE_INTERNATIONAL1, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    TECLA_INTERNACIONAL2 = SDL_SCANCODE_INTERNATIONAL2,
    TECLA_INTERNACIONAL3 = SDL_SCANCODE_INTERNATIONAL3, /**< Yen */
    TECLA_INTERNACIONAL4 = SDL_SCANCODE_INTERNATIONAL4,
    TECLA_INTERNACIONAL5 = SDL_SCANCODE_INTERNATIONAL5,
    TECLA_INTERNACIONAL6 = SDL_SCANCODE_INTERNATIONAL6,
    TECLA_INTERNACIONAL7 = SDL_SCANCODE_INTERNATIONAL7,
    TECLA_INTERNACIONAL8 = SDL_SCANCODE_INTERNATIONAL8,
    TECLA_INTERNACIONAL9 = SDL_SCANCODE_INTERNATIONAL9,
    TECLA_LINGUAGEM1 = SDL_SCANCODE_LANG1, /**< Hangul/English toggle */
    TECLA_LINGUAGEM2 = SDL_SCANCODE_LANG2, /**< Hanja conversion */
    TECLA_LINGUAGEM3 = SDL_SCANCODE_LANG3, /**< Katakana */
    TECLA_LINGUAGEM4 = SDL_SCANCODE_LANG4, /**< Hiragana */
    TECLA_LINGUAGEM5 = SDL_SCANCODE_LANG5, /**< Zenkaku/Hankaku */
    TECLA_LINGUAGEM6 = SDL_SCANCODE_LANG6, /**< reserved */
    TECLA_LINGUAGEM7 = SDL_SCANCODE_LANG7, /**< reserved */
    TECLA_LINGUAGEM8 = SDL_SCANCODE_LANG8, /**< reserved */
    TECLA_LINGUAGEM9 = SDL_SCANCODE_LANG9, /**< reserved */

    TECLA_ALTERASE = SDL_SCANCODE_ALTERASE, /**< Erase-Eaze */
    TECLA_SYSREQ = SDL_SCANCODE_SYSREQ,
    TECLA_CANCELAR = SDL_SCANCODE_CANCEL,
    TECLA_LIMPAR = SDL_SCANCODE_CLEAR,
    TECLA_ANTERIOR = SDL_SCANCODE_PRIOR,
    TECLA_ENTER2 = SDL_SCANCODE_RETURN2,
    TECLA_SEPARADOR = SDL_SCANCODE_SEPARATOR,
    TECLA_SAIR = SDL_SCANCODE_OUT,
    TECLA_OPER = SDL_SCANCODE_OPER,
    TECLA_LIMPAR_NOVAMENTE = SDL_SCANCODE_CLEARAGAIN,
    TECLA_CRSEL = SDL_SCANCODE_CRSEL,
    TECLA_EXSEL = SDL_SCANCODE_EXSEL,

    TECLA_KP_00 = SDL_SCANCODE_KP_00,
    TECLA_KP_000 = SDL_SCANCODE_KP_000,
    TECLA_SEPARADOR_MILHAR = SDL_SCANCODE_THOUSANDSSEPARATOR,
    TECLA_SEPARADOR_DECIMAL = SDL_SCANCODE_DECIMALSEPARATOR,
    TECLA_UNIDADE_CORRENTE = SDL_SCANCODE_CURRENCYUNIT,
    TECLA_SUBUNIDADE_CORRENTE = SDL_SCANCODE_CURRENCYSUBUNIT,
    TECLA_KP_PARENTESES_ESQ = SDL_SCANCODE_KP_LEFTPAREN,
    TECLA_KP_PARENTESES_DIR = SDL_SCANCODE_KP_RIGHTPAREN,
    TECLA_KP_COLCHETE_ESQ = SDL_SCANCODE_KP_LEFTBRACE,
    TECLA_KP_COLCHETE_DIR = SDL_SCANCODE_KP_RIGHTBRACE,
    TECLA_KP_TAB = SDL_SCANCODE_KP_TAB,
    TECLA_KP_VOLTAR = SDL_SCANCODE_KP_BACKSPACE,
    TECLA_KP_A = SDL_SCANCODE_KP_A,
    TECLA_KP_B = SDL_SCANCODE_KP_B,
    TECLA_KP_C = SDL_SCANCODE_KP_C,
    TECLA_KP_D = SDL_SCANCODE_KP_D,
    TECLA_KP_E = SDL_SCANCODE_KP_E,
    TECLA_KP_F = SDL_SCANCODE_KP_F,
    TECLA_KP_XOR = SDL_SCANCODE_KP_XOR,
    TECLA_KP_POWER = SDL_SCANCODE_KP_POWER,
    TECLA_KP_PORCENTAGEM = SDL_SCANCODE_KP_PERCENT,
    TECLA_KP_MENOR = SDL_SCANCODE_KP_LESS,
    TECLA_KP_MAIOR = SDL_SCANCODE_KP_GREATER,
    TECLA_KP_E_COMERCIAL = SDL_SCANCODE_KP_AMPERSAND,
    TECLA_KP_E_COMERCIAL_DBL = SDL_SCANCODE_KP_DBLAMPERSAND,
    TECLA_KP_BARRA_VERTICAL = SDL_SCANCODE_KP_VERTICALBAR,
    TECLA_KP_BARRA_HORIONTAL = SDL_SCANCODE_KP_DBLVERTICALBAR,
    TECLA_KP_DOIS_POTOS = SDL_SCANCODE_KP_COLON,
    TECLA_KP_HASH = SDL_SCANCODE_KP_HASH,
    TECLA_KP_ESPACO = SDL_SCANCODE_KP_SPACE,
    TECLA_KP_AT = SDL_SCANCODE_KP_AT,
    TECLA_KP_EXCLAMACAO = SDL_SCANCODE_KP_EXCLAM,
    TECLA_KP_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE,
    TECLA_KP_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL,
    TECLA_KP_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR,
    TECLA_KP_MEMADD = SDL_SCANCODE_KP_MEMADD,
    TECLA_KP_MEMSUBSTRACT = SDL_SCANCODE_KP_MEMSUBTRACT,
    TECLA_KP_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY,
    TECLA_KP_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE,
    TECLA_KP_MAIS_MENOS = SDL_SCANCODE_KP_PLUSMINUS,
    TECLA_KP_LIMPAR = SDL_SCANCODE_KP_CLEAR,
    TECLA_KP_LIMPAR_ENTRADA = SDL_SCANCODE_KP_CLEARENTRY,
    TECLA_KP_BINARIO = SDL_SCANCODE_KP_BINARY,
    TECLA_KP_OCTAL = SDL_SCANCODE_KP_OCTAL,
    TECLA_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL,
    TECLA_KP_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL,

    TECLA_CTRL_ESQ = SDL_SCANCODE_LCTRL,
    TECLA_SHIFT_ESQ = SDL_SCANCODE_LSHIFT,
    TECLA_ALT_ESQ = SDL_SCANCODE_LALT, /**< alt, option */
    TECLA_GUI_ESQ = SDL_SCANCODE_LGUI, /**< windows, command (apple), meta */
    TECLA_CTRL_DIR = SDL_SCANCODE_RCTRL,
    TECLA_SHIFT_DIR = SDL_SCANCODE_RSHIFT,
    TECLA_ALT_DIR = SDL_SCANCODE_RALT, /**< alt gr, option */
    TECLA_GUI_DIR = SDL_SCANCODE_RGUI, /**< windows, command (apple), meta */

    TECLA_MODO_TECLAS = SDL_SCANCODE_MODE,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /*@}*//*Usage page 0x07*/

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /*@{*/

    TECLA_PROXIMO_AUDIO = SDL_SCANCODE_AUDIONEXT,
    TECLA_AUDIO_ANTERIOR = SDL_SCANCODE_AUDIOPREV,
    TECLA_PARAR_AUDIO = SDL_SCANCODE_AUDIOSTOP,
    TECLA_TOCAR_AUDIO = SDL_SCANCODE_AUDIOPLAY,
    TECLA_AUDIO_MUDO = SDL_SCANCODE_AUDIOMUTE,
    TECLA_SELECIONAR_MEDIA = SDL_SCANCODE_MEDIASELECT,
    TECLA_WWW = SDL_SCANCODE_WWW,
    TECLA_MAIL = SDL_SCANCODE_MAIL,
    TECLA_CALCULADORA = SDL_SCANCODE_CALCULATOR,
    TECLA_COMPUTADOR = SDL_SCANCODE_COMPUTER,
    TECLA_AC_PROCURAR = SDL_SCANCODE_AC_SEARCH,
    TECLA_AC_HOME = SDL_SCANCODE_AC_HOME,
    TECLA_AC_VOLTAR = SDL_SCANCODE_AC_BACK,
    TECLA_AC_AVANCAR = SDL_SCANCODE_AC_FORWARD,
    TECLA_AC_PARAR = SDL_SCANCODE_AC_STOP,
    TECLA_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
    TECLA_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,

    /*@}*//*Usage page 0x0C*/

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /*@{*/

    TECLA_MENOS_BRILHO = SDL_SCANCODE_BRIGHTNESSDOWN,
    TECLA_MAIS_BRILHO = SDL_SCANCODE_BRIGHTNESSUP,
    TECLA_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH, /**< display mirroring/dual display
                                           switch, video mode switch */
    TECLA_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE,
    TECLA_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN,
    TECLA_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP,
    TECLA_EJETAR = SDL_SCANCODE_EJECT,
    TECLA_DORMIR = SDL_SCANCODE_SLEEP,

    TECLA_APP1 = SDL_SCANCODE_APP1,
    TECLA_APP2 = SDL_SCANCODE_APP2,

    /*@}*//*Walther keys*/

    /* Add any other keys here. */

    NUMERO_DE_TECLAS = SDL_NUM_SCANCODES /**< not a key, just marks the number of scancodes
                                 for array bounds */
};