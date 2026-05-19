#ifndef __VUTILS__
#define __VUTILS__

#define vfilename(path) ( strrchr(path, '/') ? strrchr(path, '/') + 1 : strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path )

#define __char_to_lower(_char) (_char - ('A' - 'a'))
#define __char_to_upper(_char) (_char - ('a' - 'A'))
#define __char_lower_alpha(_char) ('a' <= _char && _char <= 'z')
#define __char_upper_alpha(_char) ('A' <= _char && _char <= 'Z')
#define __char_alpha(_char) (__char_lower_alpha(_char) || __char_upper_alpha(_char))
#define __char_digit(_char) ('0' <= _char && _char <= '9')
#define __char_alnum(_char) (__char_digit(_char) || __char_alpha(_char))

#define __char_idvalid(_char) (__char_alpha(_char) || (_char == '_'))  // always valid in identifiers
#define __char_nsymbol(_char) (__char_alnum(_char) || (_char == '_'))  // not a symbol (not valid in the start of identifiers)

#define __char_symbol(_char) ((!__char_nsymbol(_char)))  // is a symbol

#define __is_token_at(_str, _strlen, _pos, _len)                    \
    ((_pos == 0 || __char_symbol(_str[_pos - 1])) &&                \
     (_pos + _len >= _strlen || __char_symbol(_str[_pos + _len])))  \
    ? (1 + 2*(_pos + _len >= _strlen) + (_pos == 0))                \
    : 0

#define __mergetoken(a, b) a##b
#define mergetoken(a, b) __mergetoken(a, b)

#define __mergetokens(a, b, c) a##b##c
#define mergetokens(a, b, c) __mergetokens(a, b, c)

#define __mergetokens4(a, b, c, d) a##b##c##d
#define mergetokens4(a, b, c, d) __mergetokens4(a, b, c, d)

#define uniq(_iden) mergetoken(_iden, __LINE__)

#endif