// Verlet Read Write Header
#if defined(_INC_STDIO) && !defined(Open) && !defined(For) && !defined(In)
#define _INC_VERLET_READWRITE

#include "vutils.h"

#define _DEF_FILE_STRUCT

#define __fs__save_path_buffer(_path, _size) char uniq(__fs__path_) [_size] = _path
#define __fs__save_path(_path) __fs__save_path_buffer(_path, 1024)

typedef struct __fs__file_struct {
    FILE * file;
    char * path;
} __fs__file_struct;

#define __fs__new_file_struct_ __fs__file_struct uniq(__fs__fs_);
#define __fs__set_path_ uniq(__fs__fs_).path = uniq(__fs__path_);
#define __fs__set_file_(_mode) uniq(__fs__fs_).file = fopen( uniq(__fs__path_), _mode ); __fs__file_struct

#define _DEF_OPEN

#define Open(_path) __fs__save_path(_path); __fs__new_file_struct_ __fs__set_path_

#define For ; uniq(__fs__fs_).file = fopen(uniq(__fs__path_),
#define In(_iden) ); __fs__file_struct _iden = uniq(__fs__fs_)

#define _DEF_WRITER

#define __fs__init_Writer __fs__file_struct __fs__writer_; fpos_t __fs__writer_pos;

extern __fs__file_struct __fs__writer_;
extern fpos_t __fs__writer_pos;

#define Writer __fs__writer_  = uniq(__fs__fs_); __fs__writer_.file = fopen(uniq(__fs__path_), "w"); 

#define WriteChar(_char) fputc(_char, __fs__writer_.file)

#define WriteLine(_line) fputs(_line, __fs__writer_.file)

#define WriteFormat(_format, ...) fprintf(__fs__writer_.file, _format __VA_OPT__(,) __VA_ARGS__)

#define UpdateWriterPos fgetpos(__fs__writer_.file, &__fs__writer_pos)

#define WriterPosType fpos_t

#define WriterPos __fs__writer_pos

#define WriterGoTo(_pos) fsetpos(__fs__writer_.file, &_pos)

#define ResetWriter rewind(__fs__writer_.file)

#define CloseWriter fclose(__fs__writer_.file)

#define _DEF_READER

#define __fs__init_Reader __fs__file_struct __fs__reader_; fpos_t __fs__reader_pos;

extern __fs__file_struct __fs__reader_;
extern fpos_t __fs__reader_pos;

#define Reader __fs__reader_ = uniq(__fs__fs_); __fs__reader_.file = fopen(uniq(__fs__path_), "r");

#define ReadChar(_char) for (int _char = (fgetpos(__fs__reader_.file, &__fs__reader_pos), fgetc(__fs__reader_.file)); _char != EOF; (fgetpos(__fs__reader_.file, &__fs__reader_pos), _char = fgetc(__fs__reader_.file)))

#define ReadLine(_line, _size) for (char _line[_size]; (fgetpos(__fs__reader_.file, &__fs__reader_pos), fgets(_line, sizeof(_line), __fs__reader_.file));)

#define UpdateReaderPos fgetpos(__fs__reader_.file, &__fs__reader_pos)

#define ReaderPosType fpos_t

#define ReaderPos __fs__reader_pos

#define ReaderGoTo(_pos) fsetpos(__fs__reader_.file, &_pos)

#define ResetReader rewind(__fs__reader_.file)

#define Once(_code) {_code; break;}

#define CloseReader fclose(__fs__reader_.file)

__fs__init_Reader

__fs__init_Writer

#endif